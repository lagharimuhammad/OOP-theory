#include <iostream>

using namespace std;

unsigned long hash_passcode(string password) 
{
    unsigned long hash = 5381;
    for (char c : password) 
    {
        hash = (hash * 33) + c;
    }
    return hash;
}

class User {
public:
    string name;
    int id;
    string email;
    unsigned long hashed_password;
    string permissions[3];

    User(string n, int id, string e, string password, string perm1 = "", string perm2 = "", string perm3 = "") : name(n), id(id), email(e), hashed_password(hash_passcode(password)) 
    {
        permissions[0] = perm1;
        permissions[1] = perm2;
        permissions[2] = perm3;
    }

    virtual void display() 
    {
        cout << "naam: " << name << endl << "id: " << id << endl << "email: " << email << endl;
    }

    bool validate(string p) 
    {
        return hash_passcode(p) == hashed_password;
    }

    bool permisssion(string a) 
    {
        for (int i = 0; i < 3; i++) 
        {
            if (permissions[i] == a) 
                return true;
        }
        return false;
    }

    virtual bool access()
    {
        if (permisssion("full lab access")) 
            {
                cout << name << " has full access to the lab." << endl;
                return true;
            } 
        else 
            {
                cout << name << " does not have lab access." << endl;
                return false;
            }
    }
};

class Student : public User 
{
public:
    int assignments[5];

    Student(string name, int id, string email, string password) : User(name, id, email, password, "submit_assignment") 
    {
        for (int i = 0; i < 5; i++) 
        {
            assignments[i] = 0;
        }
    }

    void submit(int i) 
    {
        if (i >= 0 && i < 5) 
        {
            assignments[i] = 1;
            cout << "Assignment " << i + 1 << " submitted by " << name << "." << endl;
        } 
        else 
        {
            cout << "Invalid assignment index." << endl;
        }
    }

    void display() override 
    {
        User::display();
        cout << "Assignments: ";
        for (int i = 0; i < 5; i++) 
        {
            cout << assignments[i] << " ";
        }
        cout << endl;
    }
};

class TA : public Student 
{
public:
    string assign_student[10];
    int counter;
    string projects[2];
    int p_counter;

    TA(string name, int id, string email, string password) : Student(name, id, email, password) 
    {
        permissions[1] = "view_projects";
        permissions[2] = "manage_students";
        counter = 0;
        p_counter = 0;
    }

    void assign(string s_name) 
    {
        if (counter < 10) 
            {
                assign_student[counter++] = s_name;
                cout << s_name << " assigned to TA " << name << endl;
            } 
        else 
            {
                cout << "TA " << name << " cannot manage more than 10 students." << endl;
            }
    }

    void adding_projects(string p_name) 
    {
        if (p_counter < 2) 
            {
                projects[p_counter++] = p_name;
                cout << "TA " << name << " started working on project: " << p_name << endl;
            } 
        else 
            {
                cout << "TA " << name << " is already working on 2 projects." << endl;
            }
    }

    void display() override 
    {
        Student::display();
        cout << "Assigned Students: ";
        for (int i = 0; i < counter; i++) 
        {
            cout << i+1 << ". " << assign_student[i] << endl;
        }
        cout << "Projects: ";
        for (int i = 0; i < p_counter; i++) 
        {
            cout << projects[i] << " ";
        }
        cout << endl;
    }
};

class Professor : public User 
{
public:
    Professor(string name, int id, string email, string password) : User(name, id, email, password, "assign_projects", "full_lab_access") {}

    void assign_project(TA& ta, string p_name) 
    {
        ta.adding_projects(p_name);
    }

    void display() override 
    {
        User::display();
        cout << "Professor with full lab access." << endl;
    }
};

void validateAndPerformAction(User* user, string password, string action) 
{
    if (user->validate(password)) 
        {
            cout << "aathentication successful for " << user->name << "." << endl;
                if (user->permisssion(action)) 
                {
                    cout << "Action permitted: " << action << "." << endl;
                } 
            else 
                {
                    cout << "Action denied: " << action << "." << endl;
                }
        } 
    else 
        {
            cout << "Authentication failed for " << user->name << "." << endl;
        }
}

int main() 
{
    Student s1("Baqar", 240006, "k240006@nu.edu.pk", "password123");
    TA ta1("Mr TA", 0000, "k200000@nu.edu.pk", "securepass");
    Professor p1("Mr Prof", 23567, "mr.prof@nu.edu.pk", "professorpass");
    s1.display();

    validateAndPerformAction(&s1, "password123", "submit assignment");
    validateAndPerformAction(&ta1, "securepass", "manage students");
    validateAndPerformAction(&p1, "professorpass", "assign projects");
    s1.submit(1);
    s1.display();
    ta1.assign("Baqar");
    ta1.adding_projects("AI Research");
    ta1.display();
    return 0;
}