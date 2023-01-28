#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

using std::vector;

class Team
{
private:
    unsigned int strength; //size
    bool set_on_floor;
    int team_number;
    vector <int> preferred;
    vector <int> tolerated;
    vector <int> no_way;
public:
    Team(); //default constructor
    Team::Team(int strength, vector <int> preferred, vector <int> tolerated, vector <int> no_way)

    ~Team();

    Team(const Team& other); //constructor, but lowk dont need this

    // void load_team_data(string filename);
    void set_strength(int value);

    void floor_set(bool change); //change the bool value for if set on a floor

    void set_team_number(int number);
    void add_to_vector(string type, int add);

    vector <int> getPreferred();
    vector <int> getTolerated();
    vector <int> getNo_Way();


};

#endif