# 41141141

作業一 Problem 2

## 解題說明

本題要求實現一個遞迴函式，計算一個集合的 powerset。

### 解題策略

1.  使用遞迴函式，將問題拆解為更小的子問題。對於集合中的每個元素，我們有兩種選擇：包含它或不包含它。
2.  遞迴地為集合的其餘部分生成子集。
3.  主程式呼叫遞迴函式，並輸出計算結果。

## 程式實作

以下為主要程式碼：

```cpp
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
  // std::vector<char> s = {'a', 'b', 'c'}; //- #NOTE - Can be changed to test other cases
  std::vector<char> s = {'a', 'b'};

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

  return 0;
}
```

## 效能分析

1.  時間複雜度：程式的時間複雜度為 $O(2^n)$，其中 n 是集合的大小。
2.  空間複雜度：空間複雜度為 $O(2^n)$，因為需要存儲所有子集。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 `s` | 預期輸出 |
|---|---|---|
| 測試一 | `{'a', 'b', 'c'}` | `{{}, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}}` |
| 測試二 | `{'a', 'b'}` | `{{}, {a}, {a, b}, {b}}` |
| 測試二 | `{'a'}` | `{{}, {a}}` |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o hw1P2 ./homework1_Problem2/src/main.cpp
$ ./hw1P2
```

### 結論

1.  程式能正確計算給定集合的冪集。
2.  測試案例驗證了程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算冪集的主要原因如下：

1.  **程式邏輯簡單直觀**
    遞迴的寫法能夠表達「對於每個元素，包含或不包含」的概念。

2.  **易於理解與實現**
    遞迴的程式碼更接近數學邏輯，適合學習遞迴的基本概念。

```