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
  this.strength = strength;
  set_on_floor = false;
  this->preferred = preferred;
  this->tolerated = tolerated;
  this->no_way = no_way;
}

Team::Team(const Team& other)
{
  this.strength = other.getStrength();
  set_on_floor = false;
  this->preferred = other.getPreferred();
  this->tolerated = other.getTolerated();
  this->no_way = other.getNo_Way();
}

Team::~Team()
{

}

void Team::set_floor(bool change){

}

vector <int> getPreferred()
{
  return preferred;
}

vector <int> getTolerated()
{
  return tolerated;
}

vector <int> getNo_Way()
{
  return no_way;
  }

void add_to_vector(string type, int add){
  switch
  {
    case (type == "preferred"):
      preferred.push_back(add);
      break;
    case (type == "tolerated"):
      tolerated.push_back(add);
      break;
    case(type == "no_way"):
      no_way.push_back(add);
      break;    
  }
}

