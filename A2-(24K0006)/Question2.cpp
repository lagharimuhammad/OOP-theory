#include <iostream>
#include <string>
using namespace std;

class Ghost 
{
public:
    string name;
    int lvl;
    
    Ghost(string n) : name(n) 
    {
        lvl = (name.length() * 7 + 4) % 10 + 1;
    }
    virtual void haunt() = 0;
    friend ostream& operator<<(ostream& o, const Ghost& g) 
    {
        o << g.name << " (level: " << g.lvl << ")";
        return o;
    }

    virtual ~Ghost() {}
};

class Poltergeist : public virtual Ghost 
{
public:
    Poltergeist(string n) : Ghost(n) {}
    void haunt() override 
    {
        cout << name << " moves objects violently" << endl;
    }
};

class Banshee : public virtual Ghost 
{
public:
    Banshee(string n) : Ghost(n) {}
    void haunt() override 
    {
        cout << name << " screams loudly" << endl;
    }
};

class ShadowGhost : public virtual Ghost 
{
public:
    ShadowGhost(string n) : Ghost(n) {}
    void haunt() override 
    {
        cout << name << " whispers creepily" << endl;
    }
};

class ShadowPoltergeist : public ShadowGhost, public Poltergeist 
{
public:
    ShadowPoltergeist(string n) : Ghost(n), ShadowGhost(n), Poltergeist(n) {}
    void haunt() override 
    {
        ShadowGhost::haunt();
        Poltergeist::haunt();
    }
};

class Visitor 
{
public:
    string name;
    int visitor_lvl;
    Visitor(string n, int b) : name(n), visitor_lvl(b) {}
    
    void react(int lvl) 
    {
        if (lvl > visitor_lvl + 2) 
        {
            cout << name << " screams and runs away" << endl;
        }
        else if (lvl < visitor_lvl - 2) 
        {
            cout << name << " laughs and taunts the ghost" << endl;
        }
        else 
        {
            cout << name << " feels uneasy and gets a shaky voice" << endl;
        }
    }
};

class HauntedHouse 
{
public:
    string name;
    Ghost* ghosts[5];
    int counter;

    HauntedHouse(string n) : name(n), counter(0) {}

    ~HauntedHouse()
    {
        for (int i = 0; i < counter; i++)
        {
            delete ghosts[i];
        }
    }

    void add(Ghost* g) 
    {
        if (counter < 5) 
            ghosts[counter++] = g;
    }
    
    void stimulate(Visitor& v) 
    {
        cout << endl << name << " haunting simulation begins!" << endl;
        for (int i = 0; i < counter; i++) 
        {
            ghosts[i]->haunt();
            v.react(ghosts[i]->lvl);
        }
    }
};

void visit(HauntedHouse& house, Visitor visitors[], int size) 
{
    cout << "Visitors are entering " << house.name << "..." << endl;
    for (int i = 0; i < size; i++) 
    {
        house.stimulate(visitors[i]);
    }
}

int main() 
{
    HauntedHouse house1("spooky kingdom");
    house1.add(new Poltergeist("baqar"));
    house1.add(new Banshee("kashif"));
    house1.add(new ShadowGhost("omer"));
    house1.add(new ShadowPoltergeist("anwer"));
    Visitor visitors[3] = 
    { 
        Visitor("ali", 2),
        Visitor("amir", 6), 
        Visitor("kashan", 9) 
    };
    visit(house1, visitors, 3);
    return 0;
}
