#include "team.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using std::string;
using std::cin;
using std::cout;

using namespace std;

Team::Team(int strength, vector <int> preferred, vector <int> tolerated, vector <int> no_way)
{
  this->strength = strength;
  set_on_floor = false;
  copy(this->preferred.begin(), this->preferred.end(), back_inserter(preferred)); 
  copy(this->tolerated.begin(), this->tolerated.end(), back_inserter(tolerated)); 
  copy(this->no_way.begin(), this->no_way.end(), back_inserter(no_way)); 
}

// Team::Team(const Team& other)
// {
//   this->strength = other.getStrength();
//   set_on_floor = false;
//   this->preferred = other.getPreferred();
//   this->tolerated = other.getTolerated();
//   this->no_way = other.getNo_Way();
// }

Team::~Team()
{
  preferred.clear();
  tolerated.clear();
  no_way.clear();
}

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


// void Team::pop_vector(int type, int val){
//   switch (type)
//   {
//   case 0: //prefered
//     preferred;
//     break;
//   case 1: //tolerated
//     tolerated.push_back(add);
//     break;

//   case 2: // no way
//     no_way.push_back(add);
//     break;
//   }
// }


void Team::update_ranking(){
  pickiness = (preferred.size() + tolerated.size())/no_way.size();
}

void Team::set_team_number(int val)
{
  team_number = val;
}

int Team::get_team_number()
{
  return team_number;
}
