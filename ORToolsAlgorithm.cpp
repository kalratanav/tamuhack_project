#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

#include "absl/strings/str_format.h"
#include "ortools/linear_solver/linear_expr.h"
#include "ortools/linear_solver/linear_solver.h"

void MultipleKnapsackMip() {
  const std::vector<int> weights = {
      {22, 45, 34, 51, 11, 37, 42, 16, 29, 56, 49}};
  // const std::vector<int> values = {
  //     {10, 30, 25, 50, 35, 30, 15, 40, 30, 35, 45, 10, 20, 30, 25}};

  const std::vector<vector<int>> preferred = {
      {2, 4, 6, 11}, {1, 3, 5}, {1, 2, 11}, {10}, {1, 2, 3, 4}, {7, 10}, {1, 2, 3, 4, 5, 6}, {1, 10}, {1, 5}, {2, 6, 7, 11}, {1, 4, 5}
  }
  const std::vector<vector<int>> tolerate = {
      {3, 8, 10}, {6, 7, 11}, {7}, {1, 3}, {9, 10, 11}, {1, 8}, {10, 11}, {2, 4, 11}, {2, 10}, {4, 5, 8}, {2, 3, 6, 7, 9, 10}
  }
  const std::vector<vector<int>> no_way = {
      {5, 7, 9}, {4, 8, 9, 10}, {4, 5, 6, 8, 9, 10}, {2, 5, 6, 7, 8, 9, 11}, {6, 7, 8}, {2, 3, 4, 5, 9, 11}, {8, 9}, {3, 5, 6, 7, 9}, {3, 4, 6, 7, 8, 11}, {1, 3, 9}, {8}
  }
  
  const int num_items = weights.size();
  std::vector<int> all_items(num_items);
  std::iota(all_items.begin(), all_items.end(), 0);
  std::vector<vector<bool>> no_way_bool(all_items);
  for(int i : all_items)
  {
    std::vector<bool> no_way_bool_row(all_items, 0);
    for(int j : no_way[i].size())
    {
        no_way_bool_row.at(no_way.at(i).at(j)-1) = 1;
    }
  }

  std::vector<vector<bool>> pref_bool(all_items);
  for (int i : all_items)
  {
      std::vector<bool> pref_bool_row(all_items, 0);
      for (int j : preferred[i].size())
      {
          prefbool_row.at(preferred.at(i).at(j) - 1) = 1;
      }
  }

  std::vector<vector<bool>> tol_bool(all_items);
  for (int i : all_items)
  {
      std::vector<bool> tol_bool_row(all_items, 0);
      for (int j : tolerate[i].size())
      {
          tolbool_row.at(tolerate.at(i).at(j) - 1) = 1;
      }
  }

  const std::vector<int> bin_capacities = {{43, 81, 73, 54, 97}};
  const int num_bins = bin_capacities.size();
  std::vector<int> all_bins(num_bins);
  std::iota(all_bins.begin(), all_bins.end(), 0);

  // Create the mip solver with the SCIP backend.
  std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("SCIP"));
  if (!solver) {
    LOG(WARNING) << "SCIP solver unavailable.";
    return;
  }

  // Variables.
  // x[i][b] = 1 if item i is packed in bin b.
  std::vector<std::vector<const MPVariable*>> x(
      num_items, std::vector<const MPVariable*>(num_bins));
  for (int i : all_items) {
    for (int b : all_bins) {
      x[i][b] = solver->MakeBoolVar(absl::StrFormat("x_%d_%d", i, b));
    }
  }

  // Constraints.
  // Each item is assigned to at most one bin.
  for (int i : all_items) {
    LinearExpr sum;
    for (int b : all_bins) {
      sum += x[i][b];
    }
    solver->MakeRowConstraint(sum <= 1.0);
  }

  for(int b : all_bins){
    LinearExpr no_way_check;
    for (int i : all_items) {
        for (int i2 : all_items) {
            no_way_check += no_way_bool[i][i2] * LinearExpr(x[i2][b]) * LinearExpr(x[i][b]);
        }
    }
    solver->MakeRowConstraint(no_way_check == 0);
  }
  
  // The amount packed in each bin cannot exceed its capacity.
  for (int b : all_bins) {
    LinearExpr bin_weight;
    for (int i : all_items) {
      bin_weight += LinearExpr(x[i][b]) * weights[i];
    }
    solver->MakeRowConstraint(bin_weight <= bin_capacities[b]);
  }

  // Objective.
  // Maximize total value of packed items.
  MPObjective* const objective = solver->MutableObjective();
  LinearExpr objective_value;
  for (int b : all_bins){
    for(int i : all_items){
      for (int i1 : all_items) {
          objective_value += LinearExpr(x[i][b]) * weights[i] * (2*pref_bool[i][i1] + tol_bool[i][i1]);
        }
    }
  }
  objective->MaximizeLinearExpr(objective_value);

  const MPSolver::ResultStatus result_status = solver->Solve();

  if (result_status == MPSolver::OPTIMAL) {
    LOG(INFO) << "Total packed value: " << objective->Value();
    double total_weight = 0.0;
    for (int b : all_bins) {
      LOG(INFO) << "Bin " << b;
      double bin_weight = 0.0;
      // double bin_value = 0.0;
      for (int i : all_items) {
        if (x[i][b]->solution_value() > 0) {
          LOG(INFO) << "Item " << i << " weight: " << weights[i]
                    // << " value: " << values[i]
                    ;
          bin_weight += weights[i];
          // bin_value += values[i];
        }
      }
      LOG(INFO) << "Packed bin weight: " << bin_weight;
      // LOG(INFO) << "Packed bin value: " << bin_value;
      total_weight += bin_weight;
    }
    LOG(INFO) << "Total packed weight: " << total_weight;
  } else {
    LOG(INFO) << "The problem does not have an optimal solution.";
  }
}

int main(int argc, char** argv) {
  operations_research::MultipleKnapsackMip();
  return EXIT_SUCCESS;
}