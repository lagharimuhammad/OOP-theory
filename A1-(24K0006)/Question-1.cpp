#include <iostream>
#include <string>

using namespace std;

class Skill 
{
public:
    int skill_id;
    string skill_name, description;
    Skill(int id, string name, string desc) : skill_id(id), skill_name(name), description(desc) {}
    void details_about_skills() 
    { 
        cout << "Skill: " << skill_name << " - " << description << endl; 
    }
    void update_skill_description(string newDescription) 
    { 
        description = newDescription; 
    }
};

class Sport 
{
public:
    int sport_id_number;
    string name, description;
    string required_skills[10];
    int skill_counter;
    Sport(int id, string n, string desc) : sport_id_number(id), name(n), description(desc), skill_counter(0) {}
    void add_skill(string skill) 
    { 
        if (skill_counter < 10) required_skills[skill_counter++] = skill; 
    }
    void remove_skill(string skill) 
    {
        for (int i = 0; i < skill_counter; i++) 
        {
            if (required_skills[i] == skill) 
            {
                for (int j = i; j < skill_counter - 1; j++)
                {
                    required_skills[j] = required_skills[j + 1];
                }
                skill_counter--;
                break;
            }
        }
    }
};

class Mentor;

class Student 
{
public:
    int student_id, age;
    string name;
    string interested_sports[5];
    int count_interest;
    Mentor* appointed_mentor;
    Student(int id, string n, int a) : student_id(id), name(n), age(a), appointed_mentor(NULL), count_interest(0) {}
    void apply_for_mentorship(Mentor* m);
    void view_mentor_details();
    void update_sports_interest(string sport) 
    { 
        if (count_interest < 5) 
        {
            interested_sports[count_interest++] = sport; 
        }
    }
};

class Mentor {
public:
    int mentor_id, maximum_learners, counter_learner;
    string name;
    string sports_in_expert[5];
    Student* appointed_learners[3]; // Fixed size for learners
    Mentor(int ID, string NAME, int max_learner) : mentor_id(ID), name(NAME), maximum_learners(max_learner), counter_learner(0) {}
    void assigning_learner(Student* s) 
    {
        if (counter_learner < maximum_learners) 
        {
            appointed_learners[counter_learner++] = s;
        }
    }
    void withdraw_learner(Student* s) 
    {
        for (int i = 0; i < counter_learner; i++) 
        {
            if (appointed_learners[i] == s) 
            {
                for (int j = i; j < counter_learner - 1; j++) 
                {
                    appointed_learners[j] = appointed_learners[j + 1];
                }
                counter_learner--;
                s->appointed_mentor = NULL;
                break;
            }
        }
    }
    void view_learners() 
    {
        for (int i = 0; i < counter_learner; i++) 
        {
            cout << appointed_learners[i]->name << " is assigned to " << name << endl;
        }
    }
    void guidance() 
    { 
        cout << name << " is guiding students." << endl; 
    }
};

void Student::apply_for_mentorship(Mentor* m) 
{
    if (m->counter_learner < m->maximum_learners) 
    {
        appointed_mentor = m;
        m->assigning_learner(this);
    }
}

void Student::view_mentor_details() 
{
    if (appointed_mentor)
        cout << "Mentor: " << appointed_mentor->name << endl;
    else
        cout << "No mentor assigned." << endl;
}

int main() {
    Mentor ali(0006, "Baqar", 4);
    Student saad(2539, "Kashif", 19);
    
    saad.apply_for_mentorship(&ali);
    ali.view_learners();
    
    return 0;
}
