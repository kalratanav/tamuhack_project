#include "floor.h"

void floor::change_occupied(){
    //updating the occupied value
    double sum 0;
    for (unsigned int = 0; i < teams.size()){
        sum += teams.at(0).team_number;
    }

    occupied = sum/(static_cast<double>(capacity));
}

void floor::add_team(Team filler){
 teams.push_back(filler);
}

floor::floor(/* args */)
{
}

floor::~floor()
{
}


void floor::change_bool(bool new){
    seventy_five_populated = new;
}


