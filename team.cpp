#include "team.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using std::string;
using std::cin;
using std::cout;

using namespace std;

Team::Team()
{
  strength = 0;
  set_on_floor = false;
}


Team::Team(int strength, vector <int> preferred, vector <int> tolerated, vector <int> no_way)
{
  this->strength = strength;
  set_on_floor = false;
  this->preferred = preferred;
  this->tolerated = tolerated;
  this->no_way = no_way;
}

// Team::Team(const Team& other)
// {
//   this->strength = other.getStrength();
//   set_on_floor = false;
//   this->preferred = other.getPreferred();
//   this->tolerated = other.getTolerated();
//   this->no_way = other.getNo_Way();
// }

// Team::~Team()
// {
//   delete preferred;
//   delete tolerated;
//   delete no_way;
// }

int Team::get_strength()
{
  return strength;
}

void Team::set_strength(int strength)
{
  this->strength = strength;
}

void Team::set_floor(bool change)
{
  set_on_floor = change;
}

vector <int> Team::getPreferred()
{
  return preferred;
}

vector <int> Team::getTolerated()
{
  return tolerated;
}

vector <int> Team::getNo_Way()
{
  return no_way;
}

void Team::add_to_vector(int type, int add){
  switch (type)
  {
  case 0: //prefered
    preferred.push_back(add);
    break;
  case 1: //tolerated
    tolerated.push_back(add);
    break;

  case 2: // no way
    no_way.push_back(add);
    break;
  }
}

void Team::set_team_number(int val)
{
  team_number = val;
}
