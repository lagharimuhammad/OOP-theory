#include <iostream>
#include <string>
using namespace std;

class User 
{
public:
    int user_id, age;
    string name, license_type, contact;
    User(int id, string n, int a, string license, string c) : user_id(id), name(n), age(a), license_type(license), contact(c) {}
    void update_details(string n, int a, string license, string c) 
    {
        name = n;
        age = a;
        license_type = license;
        contact = c;
    }
};

class Vehicle 
{
public:
    string model;
	string license_required_for_car;
    double rental_price_for_car;
    Vehicle(string m, double price, string license) : model(m), rental_price_for_car(price), license_required_for_car(license) {}
    bool is_valid(string license) 
    {
        return license == license_required_for_car; 
    }
};

class RentalSystem 
{
public:
    User* users[100];
    Vehicle* vehicles[50];
    int counter_for_user, counter_for_vehicle;
    RentalSystem() : counter_for_user(0), counter_for_vehicle(0) {}
    void registering_user(int id, string name, int age, string license, string contact) 
    {
        users[counter_for_user++] = new User(id, name, age, license, contact);
    }

    void adding_new_vehicle(string model, double price, string license) 
    {
        vehicles[counter_for_vehicle++] = new Vehicle(model, price, license);
    }

    void renting_vehicle(int user_id, string model) 
    {
        for (int i = 0; i < counter_for_user; i++) 
        {
            if (users[i]->user_id == user_id) 
            {
                for (int j = 0; j < counter_for_vehicle; j++) 
                {
                    if (vehicles[j]->model == model) 
                    {
                        if (vehicles[j]->is_valid(users[i]->license_type)) 
                        {
                            cout << users[i]->name << " rented " << vehicles[j]->model << " for Rs " << vehicles[j]->rental_price_for_car << " per day." << endl;
                        } else 
                        {
                            cout << "usser is not eligible to rent this vehicle." << endl;
                        }
                        return;
                    }
                }
            }
        }
        cout << "user or vehicle not found." << endl;
    }
};

int main() 
{
    RentalSystem s1;
    s1.registering_user(1, "Baqar", 25, "Learner", "1234567890");
    s1.adding_new_vehicle("Aqua", 6500, "Learner");
    s1.adding_new_vehicle("Jeep", 8000, "Full");
	s1.renting_vehicle(1, "Aqua");  
	s1.renting_vehicle(1, "Jeep");
	s1.renting_vehicle(1, "Corolla");

    return 0;
}

