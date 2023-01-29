#include "floor.h"

void floor::set_occupied(){
    //updating the occupied value
    double sum = 0;
    for (unsigned int i = 0; i < teams.size(); i++) {
        sum += teams.get_team_number();
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


void floor::change_bool(bool n){
    seventy_five_populated = n;
}


