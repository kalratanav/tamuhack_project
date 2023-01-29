#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include "absl/strings/str_format.h"
#include "ortools/linear_solver/linear_expr.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {

    void MultipleKnapsackMip() {
        const std::vector<int> strength = {
            {22, 45, 34, 51, 11, 37, 42, 16, 29, 56, 49} };
        // const std::vector<int> values = {
        //     {10, 30, 25, 50, 35, 30, 15, 40, 30, 35, 45, 10, 20, 30, 25}};

        const std::vector<std::vector<int>> preferred = {
            {2, 4, 6, 11}, {1, 3, 5}, {1, 2, 11}, {10}, {1, 2, 3, 4}, {7, 10}, {1, 2, 3, 4, 5, 6}, {1, 10}, {1, 5}, {2, 6, 7, 11}, {1, 4, 5}
        };
        const std::vector<std::vector<int>> tolerate = {
            {3, 8, 10}, {6, 7, 11}, {7}, {1, 3}, {9, 10, 11}, {1, 8}, {10, 11}, {2, 4, 11}, {2, 10}, {4, 5, 8}, {2, 3, 6, 7, 9, 10}
        };
        const std::vector<std::vector<int>> no_way = {
            {5, 7, 9}, {4, 8, 9, 10}, {4, 5, 6, 8, 9, 10}, {2, 5, 6, 7, 8, 9, 11}, {6, 7, 8}, {2, 3, 4, 5, 9, 11}, {8, 9}, {3, 5, 6, 7, 9}, {3, 4, 6, 7, 8, 11}, {1, 3, 9}, {8}
        };

        const int num_teams = strength.size();
        std::vector<int> all_teams(num_teams);
        std::iota(all_teams.begin(), all_teams.end(), 0);
        std::vector<std::vector<bool>> no_way_bool;
        for (int i : all_teams)
        {
            std::vector<bool> no_way_bool_row(num_teams, 0);
            for (int j : no_way[i])
            {
                no_way_bool_row.at(j - 1) = 1;
            }
            no_way_bool.push_back(no_way_bool_row);
        }

        std::vector<std::vector<bool>> pref_bool;
        for (int i : all_teams)
        {
            std::vector<bool> pref_bool_row(num_teams, 0);
            for (int j : preferred[i])
            {
                pref_bool_row.at(j - 1) = 1;
            }
            pref_bool.push_back(pref_bool_row);
        }

        std::vector<std::vector<bool>> tol_bool;
        for (int i : all_teams)
        {
            std::vector<bool> tol_bool_row(num_teams, 0);
            for (int j : tolerate[i])
            {
                tol_bool_row.at(j - 1) = 1;
            }
            tol_bool.push_back(tol_bool_row);
        }

        

        const std::vector<int> floor_capacities = { {43, 81, 73, 54, 97} };
        const int num_floors = floor_capacities.size();
        std::vector<int> all_floors(num_floors);
        std::iota(all_floors.begin(), all_floors.end(), 0);

        std::vector<std::vector<bool>> test_bool;
        for (int i : all_teams)
        {
            std::vector<bool> test_bool_row(num_teams, 0);
            for (int j : all_floors)
            {
                if (j % 4 == 0)
                {
                    test_bool_row.at(j) = 1;
                }
            }
            test_bool.push_back(test_bool_row);
        }
        // Create the mip solver with the SCIP backend.
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
        if (!solver) {
            LOG(WARNING) << "SCIP solver unavailable.";
            return;
        }

        // Variables.
        // x[i][b] = 1 if team i is packed in floor b.
        std::vector<std::vector<const MPVariable*>> x(
            num_teams, std::vector<const MPVariable*>(num_floors));
        for (int i : all_teams) {
            for (int b : all_floors) {
                x[i][b] = solver->MakeBoolVar(absl::StrFormat("x_%d_%d", i, b));
            }
        }

        // Constraints.
        // Each team is assigned to at most one floor.
        for (int i : all_teams) {
            LinearExpr sum;
            //int sum = 0;
            for (int b : all_floors) {
                sum += x[i][b];
                //sum += test_bool[i][b];
                //std::cout << "one_floor_only: " << sum << std::endl;
            }
            solver->MakeRowConstraint(sum <= 1.0);
        }

        // No teams that are no way get put with each other.
        for (int b : all_floors) {
            LinearExpr no_way_check;
            //int no_way_check = 0;
            for (int i : all_teams) {
                for (int i2 : all_teams) {
                    no_way_check += -(not(no_way_bool[i][i2]) + LinearExpr(not(x[i2][b])) + LinearExpr(not(x[i][b])) - 1);
                    //no_way_check += -(not(no_way_bool[i][i2] * test_bool[i2][b]) + not(test_bool[i][b]) - 1);
                    //std::cout << "boolcheck: " << not(no_way_bool[i][i2] * test_bool[i2][b]) << std::endl;
                    //std::cout << "no_way_check: " << no_way_check << std::endl;
                    
                    
                }
            }
            solver->MakeRowConstraint(no_way_check == 0.0);
        }

        // The amount packed in each floor cannot exceed its capacity.
        for (int b : all_floors) {
            LinearExpr floor_strength;
            for (int i : all_teams) {
                floor_strength += LinearExpr(x[i][b]) * strength[i];
            }
            solver->MakeRowConstraint(floor_strength <= floor_capacities[b]);
        }

        // Objective.
        // Maximize total score of arranged teams.
        MPObjective* const objective = solver->MutableObjective();
        LinearExpr objective_value;
        //int objective_value = 0;
        for (int b : all_floors) {
            for (int i : all_teams) {
                for (int i1 : all_teams) {
                    objective_value += LinearExpr(x[i][b]) * strength[i1] * (2 * pref_bool[i][i1] + tol_bool[i][i1]);
                    //objective_value += test_bool[i][b] * strength[i1] * (2 * pref_bool[i][i1] + tol_bool[i][i1]);
                    //std::cout << "obj: " << objective_value << std::endl;
                }
            }
        }
        objective->MaximizeLinearExpr(objective_value);

        const MPSolver::ResultStatus result_status = solver->Solve();

        if (result_status == MPSolver::OPTIMAL) {
            LOG(INFO) << "Total packed value: " << objective->Value();
            double total_strength = 0.0;
            for (int b : all_floors) {
                LOG(INFO) << "Floor " << b;
                double floor_strength = 0.0;
                // double floor_value = 0.0;
                for (int i : all_teams) {
                    if (x[i][b]->solution_value() > 0) {
                        LOG(INFO) << "Team " << i << " strength: " << strength[i]
                            // << " value: " << values[i]
                            ;
                        floor_strength += strength[i];
                        // floor_value += values[i];
                    }
                }
                LOG(INFO) << "Packed floor strength: " << floor_strength;
                // LOG(INFO) << "Packed floor value: " << floor_value;
                total_strength += floor_strength;
            }
            LOG(INFO) << "Total packed strength: " << total_strength;
        }
        else {
            LOG(INFO) << "The problem does not have an optimal solution.";
        }
    }

}
int main(int argc, char** argv) {
  operations_research::MultipleKnapsackMip();
  return EXIT_SUCCESS;
}