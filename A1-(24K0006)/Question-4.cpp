#include <iostream>
#include <string>

using namespace std;

class Route 
{
private:
    int route_id;
    string point_stops[10];
public:
    Route(int id, string (&list_of_stops)[10]) : route_id(id) 
    {
        for (int i = 0; i < 10; i++)
        { 
            point_stops[i] = list_of_stops[i];
        }
    }
    string getter_stop(int mark) 
    { 
        return point_stops[mark]; 
    }
};

class Student 
{
private:
    int id;
    string name;
    bool card_activated;
    string stop;
public:
    Student(int ID, string NAME, string STOP) : id(ID), name(NAME), stop(STOP), card_activated(false) {}
    void pay_challan() 
    { 
        card_activated = true;
    }

    bool getter_card() 
    { 
        return card_activated; 
    }
    string getter_stop() 
    { 
        return stop; 
    }
    string get_name() 
    {
        return name;
    }
};

class Bus 
{
private:
    int point_id;
    Route *route_for_point;
public:
    Bus(int id, Route *r) : point_id(id), route_for_point(r) {}
    Route* get_route() 
    { 
        return route_for_point;
    }
};

class TransportSystem 
{
public:
    Student *students[1000];
    Bus *buses[50];
    Route *routes[20];
    int counter_for_students, bus_count, route_count;

    TransportSystem() : counter_for_students(0), bus_count(0), route_count(0) {}

    void add_student(int id, string name, string stop) 
    {
        students[counter_for_students++] = new Student(id, name, stop);
    }
    void add_route(int id, string (&point_stops)[10]) {
        routes[route_count++] = new Route(id, point_stops);
    }
    void add_bus(int id, Route *route) {
        buses[bus_count++] = new Bus(id, route);
    }
    void processTaps() 
    {
        for (int i = 0; i < counter_for_students; i++) 
        {
            if (students[i]->getter_card()) 
            {
                cout << "Student " << students[i]->get_name() << " checked in and will be dropped at " << students[i]->getter_stop() << ".\n";
            }
        }
    }
};

int main() 
{
    TransportSystem transport_process;
    string point_stops1[10] = {"Fast", "Landhi" , "Quaidabad", "Malir", "Malir halt", "Drigh Road", "Millenium", "Johar Mor", "Jauhar chowrangi", "Mosmiyat"};
    transport_process.add_route(1, point_stops1);
    transport_process.add_student(2539, "Kashif", "Millenium");
    transport_process.add_student(0006, "Baqar", "Mosmiyat");

    transport_process.students[0]->pay_challan();
    transport_process.students[1]->pay_challan();

    transport_process.processTaps();
    return 0;
}

