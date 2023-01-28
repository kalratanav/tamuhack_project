#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <string>

using std::vector;
#include "team.h"

class floor
{
private:
    vector <Team> teams; //each floor will contain a vector of teams that are on the floor
    bool seventy_five_populated = false;
    unsigned int capacity; //this value cannot be changed
    unsigned int occupied; // this will be the sizes of the teams divided by the capacity
public:
    floor(); 
    ~floor();
    void change_occupied(); //will be updated
    void add_team(Team filler); // add to the vector
    //change bool...if occupied/capacity > .75, then, we can change the bool val
    void change_bool();
    
    float peek_floor(); //checks current capacity



};

floor::floor(/* args */)
{
}

floor::~floor()
{
}


#include <vector>
#include <string>