#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

using std::vector;

class Team
{
private:
    unsigned int strength; //size
    bool set_on_floor = false;
    int team_number;
    vector <int> preferred;
    vector <int> tolerated;
    vector <int> no_way;
public:
    Team(); //default constructor
    ~Team();

    Team(const Team& other); //constructor, but lowk dont need this

    // void load_team_data(string filename);
    void set_strength(int value);

    void floor_set(bool change); //change the bool value for if set on a floor

    void set_team_number(int number);
    void add_to_vector(string type, int add);


};

#endif