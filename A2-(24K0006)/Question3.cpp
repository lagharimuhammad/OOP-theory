#include <iostream>
#include <string>
using namespace std;

class Vehicle 
{
public:
    string id;
    static int deliveries;
    Vehicle(string i) : id(i) 
    { 
        deliveries++; 
    }
    virtual ~Vehicle() 
    { 
        deliveries--; 
    }
    virtual void calc_route() = 0;
    virtual void est_time() = 0;
    virtual void deliver(string package_num) 
    { 
        cout << "Vehicle " << id << " delivering package " << package_num << endl; 
    }
    virtual bool operator==(const Vehicle &other) = 0;
    friend void solve_issue(Vehicle &v1, Vehicle &v2);
    int static total_del()
    {
        return deliveries;
    }
};
int Vehicle::deliveries = 0;

class Drone : public Vehicle 
{
public:
    Drone(string id) : Vehicle(id) {}
    void calc_route() override 
    { 
        cout << "drone " << id << " calculating aerial route." << endl; 
    }
    void est_time() override 
    { 
        cout << "drone " << id << " estimating fast delivery time." << endl; 
    }
    void deliver(string package_num, string urgentlvl) 
    {
        cout << "drone " << id << " delivering package " << package_num << " with high-speed for " << urgentlvl << " urgency." << endl;
    }
    bool operator==(const Vehicle &other) override 
    {
        return id == other.id;
    }
};

class Timeship : public Vehicle 
{
public:
    Timeship(string id) : Vehicle(id) {}
    void calc_route() override 
    { 
        cout << "timeShip " << id << " calculating time-travel path." << endl; 
    }
    void est_time() override 
    { 
        cout << "timeShip " << id << " estimating historical delivery accuracy." << endl;
    }
    void deliver(string package_num, string urgentlvl) 
    {
        cout << "timeship " << id << " validating historical accuracy for package " << package_num << " with urgency " << urgentlvl << endl;
    }
    bool operator==(const Vehicle &other) override 
    {
        return id == other.id;
    }
};

class Hyperpod : public Vehicle 
{
public:
    Hyperpod(string id) : Vehicle(id) {}
    void calc_route() override 
    { 
        cout << "hyperPod " << id << " calculating underground tunnel route." << endl; 
    }
    void est_time() override 
    { 
        cout << "hyperpod " << id << " estimating bulk delivery time." << endl; 
    }
    bool operator==(const Vehicle &other) override 
    {
        return id == other.id;
    }
};

void solve_issue(Vehicle &v1, Vehicle &v2) 
{
    cout << "resolving conflict between " << v1.id << " and " << v2.id << endl;
    cout << "Choosing the more efficient vehicle based on urgency and capacity." << endl;
}

int main() 
{
    Drone d("K0006");
    Timeship s("K0022");
    Hyperpod p("K2539");
    
    d.deliver("PK233", "Iftar");
    s.deliver("PK234", "Historical");
    p.calc_route();
    cout << endl;
    solve_issue(d, s);
    cout << "Active Deliveries: " << Vehicle::total_del() << endl;
    return 0;
}
