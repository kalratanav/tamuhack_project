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
}

Team::~Team()
{
}

void Team::floor_set(bool change){
  set_on_floor = change;
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
  
  default:
    break;
  }
}

void Team::set_team_number(int val){
  team_number = val;

}

// void Team::load_team_data(string filename){

//   ifstream infs(filename);
//   if(!(infs.is_open())){
//     throw std::invalid_argument("file cannot be opened");
//   }
//   //string buffer

//   string buffer = "";

//   getline(infs, buffer);

//   while (getline(infs, buffer))
//   {
    
//   }
  

    

    

// }

