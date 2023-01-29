// #include "floor.cpp"
#include "team.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>
using std::unique_ptr;

vector<int> field2vector(string field)
{
    stringstream fieldStream(field);
    vector <int> fieldNums;
    while(!fieldStream.fail())
    {
        string num;
        fieldStream >> num;
        // cout << "num: " << num << endl;
        if(num != "")
        {
            fieldNums.push_back(stoi(num));
        }
    }
    return fieldNums;
}

vector<unique_ptr<Team>> import_teams(string fileName)
{
    vector <unique_ptr<Team>> teams;
    string header, row, field;
    
    ifstream infs(fileName);
    if(!(infs.is_open())){
        throw std::invalid_argument("file cannot be opened");
    }

    getline(infs, header);

    while (getline(infs, row))
    {
        stringstream s(row);
        string teamNumber, strength, preferred, tolerated, no_way;
        getline(s, teamNumber, ',');
        getline(s, strength, ',');
        getline(s, preferred, ',');
        getline(s, tolerated, ',');
        getline(s, no_way, ',');
        // cout << "preferred: " << preferred << endl;
        vector <int> prefNums = field2vector(preferred);
        vector <int> tolNums = field2vector(tolerated);
        vector <int> no_wayNums = field2vector(no_way);
        // cout << "strength: " << strength << endl;
        teams.push_back(unique_ptr<Team>(new Team(stoi(strength), prefNums, tolNums, no_wayNums)));
        // cout << "back: " << &teams.back() << endl;
    }
    return teams;
}

int main()
{
    vector<unique_ptr<Team>> teams = import_teams("data.csv");
    for(unsigned int i = 0; i < teams.at(0)->getPreferred().size(); i++)
    {
        cout << teams.at(0)->getPreferred().at(i) << " ";
    }
    
}