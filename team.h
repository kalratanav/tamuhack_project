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
    vector <int> preferred;
    vector <int> tolerated;
    vector <int> no_way;
public:
    Team(); //default constructor
    Team::Team(int strength, vector <int> preferred, vector <int> tolerated, vector <int> no_way)

    ~Team();

    Team(const Team& other); //constructor, but lowk dont need this

    void set_floor(bool set); //change the bool value for if set on a floor

    void add_to_vector(string type, int add);

    vector <int> getPreferred();
    vector <int> getTolerated();
    vector <int> getNo_Way();


};

#endif