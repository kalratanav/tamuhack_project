// #include "floor.cpp"
#include "team.cpp"
#include <iostream>


vector<Team*> import_teams(string fileName)
{
    vector <Team*> teams;
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
        vector <int> prefNums = field2array(preferred);
        vector <int> tolNums = field2array(tolerated);
        vector <int> no_wayNums = field2array(no_way);
        teams.push_back(new Team(stoi(strength), prefNums, tolNums, no_wayNums));
    }

    return teams;

}

vector<int> field2array(string field)
{
    stringstream fieldStream(field);
    vector <int> fieldNums;
    while(!fieldStream.fail())
    {
        string num;
        fieldStream >> num;
        fieldNums.push_back(stoi(num));
    }

    return fieldNums;
}



int main()
{
    import_teams("data.csv");
}