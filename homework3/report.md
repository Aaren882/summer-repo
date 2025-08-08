# 41141141

作業三

## 解題說明

本題要求使用環狀鏈結串列 (Circular Linked List) 搭配可利用空間串列 (Available-Space List) 實作一個多項式計算機，需要支援多項式的加法、減法與乘法。

### 解題策略

1.  **資料結構**：
    *   **`Term`**: 與前次作業類似，用一個 `Term` class 來儲存每一項的係數 (`coef`) 和次方 (`exp`)。
    *   **`Polynomial`**: 使用 `Chain` class (環狀鏈結串列) 來儲存 `Term` 物件。
    *   **`Available`**: 設計一個 `Available` class (可利用空間串列) 來管理不再被使用的 `ChainNode`，以便重複利用。

2.  **核心功能**：
    *   `newTerm(float coef, int exp)`: 新增一個多項式項。此函數會管理鏈結串列的排序，確保高次方的項在前面。如果遇到相同次方的項，會直接合併係數。如果係數變為 0，則會將該節點刪除。
    *   `Add(Polynomial poly)`: 多項式加法。遍歷另一個多項式 `poly` 的所有項，並逐一加入到目前的多項式中。
    *   `Minus(Polynomial poly)`: 多項式減法。與加法類似，但加入的是負係數的項。
    *   `Mult(Polynomial poly)`: 多項式乘法。使用雙層迴圈，將兩個多項式的每一項相乘，並將結果加入一個新的多項式中。
    *   `Eval(float x)`: 計算多項式在給定 x 值下的結果。

3.  **記憶體管理**：
    *   利用一個全域的 `Available` 物件 `globalASL` 來存放所有被刪除的節點。
    *   當 `Polynomial` 物件被解構時，會將其所有的節點回收到 `globalASL` 中。
    *   當需要新的節點時，會先嘗試從 `globalASL` 中取得，如果 `globalASL` 為空，才會動態配置新的記憶體。

## 程式實作

```cpp
#include "iostream"
#include "sstream"
#include "math.h"

//- Term Class
class Term { ... };

//- ChainNode Class
template <class T>
class ChainNode { ... };

//- Chain Class (Circular Linked List)
template <class T>
class Chain { ... };

//- Available-Space List Class
class Available { ... };

//- Polynomial Class
class Polynomial { ... };

//- main function
int main() {
  Polynomial a;
  cin >> a;
  cout << "[" << a << "]" << endl;

  float x;
  cout << endl << "Enter X value : ";
  cin >> x;

  cout << endl << "Evaluation : " << endl;
  cout << ": " << "x = " << x << endl;
  cout << ": " << a << " = " << a.Eval(x) << endl << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}
```

## 效能分析

假設有兩個多項式，分別有 N 項和 M 項。

1.  **時間複雜度**:
    *   **加法 `Add` / 減法 `Minus`**: $O(N \times M)$。因為對於被加多項式的每一個詞條，都插入至目標多項式，而每一次的插入都需要遍歷目標多項式一次。
    *   **乘法 `Mult`**: $O(N \times M \times (N+M))$。雙層迴圈遍歷兩個多項式，且每次 `newTerm` 都可能遍歷新的多項式。
2.  **空間複雜度**:
    *   **加法 `Add` / 減法 `Minus`**: 最差情況下需要 $O(N+M)$ 的額外空間。
    *   **乘法 `Mult`**: 最差情況下需要 $O(N \times M)$ 的額外空間。

## 測試與驗證

透過 `main` 函數進行互動式測試，使用者可以輸入多項式和 x 值，程式會輸出計算結果。

### 測試案例

| 測試案例 | 輸入多項式 (格式: `n,exp,coef,...`) | 輸入 x | 預期輸出 |
|---|---|---|---|
| 測試一 | `2,3,2,0,1` (即 $2x^3 + 1$) | 2 | 17 |
| 測試二 | `3,2,1,1,2,0,1` (即 $x^2 + 2x + 1$) | 3 | 16 |
| 測試三 | `3,4,2,3,2,0,1` (即 $2x^4 + 2x^3 + 1$) | 2 | 49 |

## 編譯與執行指令

```shell
$ g++ -std=c++17 -o hw3 ./homework3/src/main.cpp
$ ./hw3
```

## 申論及開發報告

### 與作業二的比較

本次作業在設計上比作業二有顯著的改進，主要體現在資料結構的選擇與記憶體管理策略上。

|  | Homework 2 | Homework 3 |
|---|---|---|
| **資料結構** | 動態陣列 (Dynamic Array) | 環狀鏈結串列 (Circular Linked List) |
| **記憶體管理** | 當陣列容量不足時，重新配置雙倍大小的記憶體，並複製所有元素。 | 使用全域的可利用空間串列 (Available-Space List) 回收並重複利用節點，減少動態記憶體配置的次數。 |
| **效能** | `newTerm` 和 `Mult` 操作在陣列需要重新配置時，效能較差。 | 透過鏈結串列和 ASL，新增和刪除節點的效能相對穩定，避免了大量資料複製的成本。 |
| **複雜度** | 實作相對簡單直觀。 | 實作較為複雜，需要處理指標操作、鏈結關係以及 ASL 的管理。 |

### 開發心得

在本次作業中，透過實作環狀鏈結串列以及可利用空間串列，我對於 C++ 的指標操作、記憶體管理以及物件導向設計有了更深入的了解。

*   **環狀鏈結串列**: 相較於傳統的線性鏈結串列，環狀鏈結串列在某些操作上提供了便利性，例如可以輕易地從任一節點遍歷整個串列。但在實作上需要特別注意邊界條件，避免無窮迴圈。
*   **可利用空間串列 (ASL)**: ASL 是一個非常有效的記憶體管理策略。透過回收不再使用的節點，可以顯著減少 `new` 和 `delete` 的呼叫次數，不僅提升了效能，也降低了記憶體碎裂的風險。在大型應用程式中，這樣的設計模式尤其重要。

總體而言，雖然作業三的程式碼複雜度較高，但其資料結構的設計更加優雅且效能更好，是從「可行」到「高效」的一個重要實踐。
