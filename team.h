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
    vector <int> preferred;
    vector <int> tolerated;
    vector <int> no_way;
public:
    Team(); //default constructor
    ~Team();

    Team(const Team& other); //constructor

    void clear();

    unsigned int peek_floor(); //looks at current capacity of floor

};


#endif
