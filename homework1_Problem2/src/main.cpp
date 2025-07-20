#include <iostream>
#include <vector>

// Recursive helper function to generate the powerset.
// It explores subsets by including or not including each element.
template<typename T>
void generate_powerset_recursive(
  const std::vector<T>& original_set,       // original set of elements
  int index,                                // current index in the original_set to consider
  std::vector<T>& current_subset,           // subset being built in the current recursion path
  std::vector<std::vector<T>>& all_subsets  // final list of all subsets
) {
  // Add the current subset that was built to our list of all subsets.
  all_subsets.push_back(current_subset);

  // Explore further options by including more elements.
  for (int i = index; i < original_set.size(); ++i) {
    // Include the element at index 'i'
    current_subset.push_back(original_set[i]);

    // Recurse: find all subsets that can be formed with this new element
    generate_powerset_recursive(original_set, i + 1, current_subset, all_subsets);

    // Backtrack: remove the element to explore subsets that don't include it
    current_subset.pop_back();
  }
}

// Main function to compute the powerset of a set S.
template<typename T>
std::vector<std::vector<T>> powerset(const std::vector<T>& S) {
  std::vector<std::vector<T>> all_subsets;
  std::vector<T> current_subset;
  generate_powerset_recursive(S, 0, current_subset, all_subsets);
  return all_subsets;
}

// Helper function to print a vector of characters (representing a subset)
void print_vector(const std::vector<char>& vec) {
  printf("{");
  for (size_t i = 0; i < vec.size(); ++i) {
    printf("%c", vec[i]);
    if (i < vec.size() - 1) {
      printf(", ");
    }
  }
  printf("}");
}

// Main function to demonstrate the powerset function
int main() {
  //- #SECTION - Example with a set of characters
    std::vector<char> s = {'a', 'b', 'c'};
    // std::vector<char> s = {'a', 'b'};
    // std::vector<char> s = {'a'};
  //- #!SECTION

  printf("The powerset of ");
  print_vector(s);
  printf(" is:\n");

  std::vector<std::vector<char>> result = powerset(s);

  printf("{\n");
  for (const auto& subset : result) {
    printf("  ");
    print_vector(subset);
    printf("\n");
  }
  printf("}\n");

  system("pause");
  return 0;
}