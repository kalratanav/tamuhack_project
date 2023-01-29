
#include <iostream>

using namespace std;

struct Team
{
    int strength;
    int floor_id;
};

struct Floor
{
    int minCapacity;
    int maxCapacity;
    int occupied;
};

int main()
{
    int i, j, k, l;

    int numFloors;
    cin >> numFloors;

    Floor floors[numFloors];

    int capacity;
    for( i = 0; i < numFloors; i++ )
    {
        cin >> capacity;
        floors[i] = { capacity / 4 + 1, capacity, 0 };
    }

    int numTeams;
    cin >> numTeams;

    Team teams[numTeams];
    bool prefers[numTeams][numTeams];
    bool tolerates[numTeams][numTeams];
    bool noWay[numTeams][numTeams];
    int bestArrangement[numTeams];
    int bestScore = -2147483648;

    for( i = 0; i < numTeams; i++ )
    {
        bestArrangement[i] = -1;
        for( j = 0; j < numTeams; j++ )
        {
            prefers[i][j]   = false;
            tolerates[i][j] = false;
            noWay[i][j]     = false;
        }
    }

    int strength, numPrefers, numTolerates, numNoWay, num;
    for( i = 0; i < numTeams; i++ )
    {
        cin >> strength;
        teams[i] = { strength, -1 };

        cin >> numPrefers;
        for( j = 0; j < numPrefers; j++ )
        {
            cin >> num;
            prefers[i][num - 1] = true;
        }

        cin >> numTolerates;
        for( j = 0; j < numTolerates; j++ )
        {
            cin >> num;
            tolerates[i][num - 1] = true;
        }

        cin >> numNoWay;
        for( j = 0; j < numNoWay; j++ )
        {
            cin >> num;
            noWay[i][num - 1] = true;
        }
    }

    bool carry, valid;
    bool done = false;
    int score;
    int numValid = 0;
    while( !done )
    {
        valid = true;
        // Calculate occupancies
        for( i = 0; i < numTeams; i++ )
        {
            j = teams[i].floor_id;
            if( teams[i].floor_id == -1 )
                continue;
            floors[j].occupied += teams[i].strength;
            if( floors[j].occupied > floors[j].maxCapacity ) // Floor overfilled, bail out
            {
                valid = false;
                break;
            }
        }

        if( valid )
            for( i = 0; i < numFloors; i++ )
                if( floors[i].occupied < floors[i].minCapacity ) // Floor underfilled, bail out
                {
                    valid = false;
                    break;
                }

//        for( i = 0; i < numTeams; i++ )
//            cout << teams[i].floor_id << " ";
//        cout << endl;

        if( valid )
        {
            numValid++;
            score = 0;
            for( i = 0; i < numTeams; i++ )
                for( j = 0; j < numTeams; j++ )
                    if( teams[i].floor_id == -1 )
                        score -= 2 * teams[i].strength;
                    else
                        if( teams[i].floor_id == teams[j].floor_id )
                            score += ( prefers[i][j] - noWay[i][j] ) * ( teams[i].strength );
            if( score > bestScore )
            {
                bestScore = score;
                for( i = 0; i < numTeams; i++ )
                    bestArrangement[i] = teams[i].floor_id;
            }
        }

        // Generate next permutation
        i = 0;
        do {
            teams[i].floor_id++;
            carry = teams[i].floor_id == numFloors;
            if( carry )
            {
                teams[i].floor_id = -1;
                i++;
                if( i == numTeams )
                    done = true;
            }
        } while( carry );

        for( i = 0; i < numFloors; i++ )
            floors[i].occupied = 0;
    }

    for( i = 0; i < numTeams; i++ )
    {
        cout << bestArrangement[i];
        if( i < numTeams - 1 )
            cout << " ";
    }
    cout << endl;

//    cout << "Assignments: ";
//    for( i = 0; i < numTeams; i++ )
//        cout << bestArrangement[i] << " ";
//    cout << endl;
//    cout << "Valid: " << numValid << endl;
//    cout << "Floor Capacities:" << endl;
//    for( i = 0; i < numTeams; i++ )
//    {
//        cout << "Floor " << ( bestArrangement[i] + 1 ) << " +" << teams[i].strength << " from Team " << i << endl;
//        floors[bestArrangement[i]].occupied += teams[i].strength;
//    }
//    int totalOccupied = 0, totalCapacity = 0;
//    for( i = 0; i < numFloors; i++ )
//    {
//        totalOccupied += floors[i].occupied;
//        totalCapacity += floors[i].maxCapacity;
//        cout << "Floor " << ( i + 1 ) << ": " << floors[i].occupied << "/" << floors[i].maxCapacity << endl;
//    }
//    cout << "TOTAL: " << totalOccupied << "/" << totalCapacity
//         << " (" << ( static_cast<double>( totalOccupied ) / static_cast<double>( totalCapacity ) * 100 ) << ")" << endl;
    
    return 0;
}
