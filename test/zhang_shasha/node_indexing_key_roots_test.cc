#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "unit_cost_model.h"
#include "string_label.h"
#include "node.h"
#include "bracket_notation_parser.h"
#include "zhang_shasha.h"

/// Convert vector of int values to is string representation.
///
/// \param v Vector of int values.
/// \return String representation of v.
const std::string& vector_to_string(const std::vector<int>& v) {
  std::string s("{");
  for (auto e : v) {
    s += std::to_string(e) + ",";
  }
  s.pop_back();
  s += "}";
  return std::move(s);
}

int main() {

  using Label = label::StringLabel;
  using CostModel = cost_model::UnitCostModel<Label>;

  CostModel cost_model;

  // TODO: Add test cases for node indexing.
  //       - Standard tree.
  //       - key-root nodes
  //       - leftmost leaf descendands
  //       - postorder -> node (node's label)

  // Parse test cases from file.
  std::ifstream test_cases_file("key_roots_test_data.txt");
  for (std::string line; std::getline( test_cases_file, line);) {
    if (line[0] == '#') {
      std::getline(test_cases_file, line);
      std::string input_tree = line;
      std::getline(test_cases_file, line);
      std::string correct_result = line;

      // Parse test tree.
      parser::BracketNotationParser bnp;
      node::Node<Label> t1 = bnp.parse_string(input_tree);

      // Initialise ZS algorithm.
      zhang_shasha::Algorithm<Label, CostModel> zs_ted(t1, t1, cost_model);
      // Execute the algorithm to perform node indexing.
      zs_ted.zhang_shasha_ted();

      std::string computed_results = vector_to_string(zs_ted.get_t1_kr_());

      if (correct_result != computed_results) {
        // TODO: Print test case input.
        std::cerr << "Incorrect key roots result: " << computed_results << " instead of " << correct_result << std::endl;
        return -1;
      }
    }
  }

  return 0;
}