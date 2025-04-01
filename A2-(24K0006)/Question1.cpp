#include <iostream>
using namespace std;
class User 
{
public:
    string name;
    int id;
    User(string n, int i) : name(n), id(i) {}
    virtual void payment() = 0;
    virtual ~User() {}
};

class Student : public User 
{
public:
    double fee;
    Student(string n, int i, double f) : User(n, i), fee(f) {}
    void payment() override 
    {
        cout << name << " pays " << fee << " per semester for transport." << endl;
    }
};

class Teacher : public User 
{
public:
    double fee;
    Teacher(string n, int i, double f) : User(n, i), fee(f) {}
    void payment() override 
    {
        cout << name << " pays " << fee << " per month for transport." << endl;
    }
};

class Staff : public User 
{
public:
    double fee;
    Staff(string n, int i, double f) : User(n, i), fee(f) {}
    void payment() override 
    {
        cout << name << " pays " << fee << " per month for transport." << endl;
    }
};

class Route 
{
public:
    string route_name;
    int route_num;
    string stops[10];
    Route(string n, int num, string stop[10]) : route_name(n), route_num(num) 
    {
        for (int i = 0; i < 10; i++) 
            stops[i] = stop[i];
    }
    bool operator == (const Route &other) 
    {
        return route_num == other.route_num;
    }
    void display() 
    {
        cout << "( " << route_name  << " ) -" << " route number: " << route_num << endl;
    }
};

class Bus 
{
public:
    int bus_id;
    Route* route_number;
    Bus(int id, Route* route) : bus_id(id), route_number(route) {}
    void displayer_for_bus() 
    {
        cout << endl << "bus id: " << bus_id << " assigned to route: "; route_number->display();
    }
};

class TransportSystem 
{
public:
    User* user[100];
    Bus* point[50];
    Route* route[20];
    int u_counter, p_counter, r_counter;
    
    TransportSystem() : u_counter(0), p_counter(0), r_counter(0) {}

    void add_user(User* u) 
    { 
        user[u_counter++] = u; 
    }

    void add_route(Route* r) 
    { 
        route[r_counter++] = r; 
    }

    void add_bus(Bus* b) 
    {
        point[p_counter++] = b; 
    }

    void process_payment() 
    {
        for (int i = 0; i < u_counter; i++) 
            user[i]->payment();
    }
};

int main() 
{
    TransportSystem system;
    string stops1[10] = {"Fast", "Landhi", "Quaidabad", "Malir", "Malir Halt", "Drigh Road", "Millennium", "Johar Mor", "Jauhar Chowrangi", "Mosmiyat"};
    Route r1("Main Campus - City Center", 1, stops1);
    system.add_route(&r1);
    Student s("Baqar", 240006, 38000);
    Teacher t("Prof: Ahmed", 156, 10000);
    Staff st("Mr Anwer", 323, 8000);
    system.add_user(&s);
    system.add_user(&t);
    system.add_user(&st);
    Bus b1(1, &r1);
    system.add_bus(&b1);
    system.process_payment();
    b1.displayer_for_bus();
    return 0;
}