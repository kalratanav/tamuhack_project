#include "team.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "floor.h"
#include "team.h"

using std::string;
using std::cin;
using std::cout;

using namespace std;


// loading functions

void load_team_data(string filename){

    ifstream infs(filename);
    if(!(infs.is_open())){
    throw std::invalid_argument("file cannot be opened");
    }
    //string buffer
    int team_no = 1;

    string buffer = ""; //whole string

    string strength = "";
    string preferred = "";
    string tolerated = "";
    string no_way = "";

    getline(infs, buffer); //skip first string

    while (getline(infs, buffer))
    {
        // Team obj;
        // obj.set_team_number(static_cast<int>(buffer.at(0)));

        // strength = buffer.substr(1,buffer.find("'", 1));

        // tolerated = buffer.substr(buffer.find_first_of("'"),buffer.find_last_of("'"));

        // no_way = buffer.substr(buffer.find_last_of("'"));


    }
}

void load_floor_data(string filename){
    
}

