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

}

void add_to_vector(string type, int add){
  
}

void Team::load_team_data(string filename){

  ifstream infs(filename);
  if(!(infs.is_open())){
    throw std::invalid_argument("file cannot be opened");
  }
  //string buffer

  string buffer = "";

  getline(infs, buffer);

  while (getline(infs, buffer))
  {
    
  }
  

    

    

}

