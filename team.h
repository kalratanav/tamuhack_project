#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>

using std::vector;

class Team
{
    private:
        unsigned int strength; //size
        bool set_on_floor;
        int team_number;
        double pickiness;
        vector <int> preferred;
        vector <int> tolerated;
        vector <int> no_way;
    public:
        Team():strength(0), set_on_floor(false){} //default constructor
        Team(int strength, vector <int> preferred, vector <int> tolerated, vector <int> no_way);

        ~Team();

        // Team(const Team& other); //constructor, but lowk dont need this

        // void load_team_data(string filename);
        int get_strength();
        void set_strength(int value);

        void set_floor(bool change); //change the bool value for if set on a floor

        void set_team_number(int number);
        int get_team_number();

        void add_to_vector(int type, int add);

        vector <int> getPreferred();
        vector <int> getTolerated();
        vector <int> getNo_Way();

        void update_ranking();
        // void pop_vector(int type, int add);
};

#endif