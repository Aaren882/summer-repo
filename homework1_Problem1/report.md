# 41141141

作業一 Problem 1

## 解題說明

本題要求實作阿克曼函式 (Ackermann's function) $A(m, n)$，其定義如下：
$
A(m, n) =
\begin{cases}
n+1 & \text{if } m = 0 \\
A(m-1, 1) & \text{if } m > 0 \text{ and } n = 0 \\
A(m-1, A(m, n-1)) & \text{if } m > 0 \text{ and } n > 0
\end{cases}
$
此函式以其對於小的輸入值卻有極大的增長率。
要求使用遞迴（Recursive）與非遞迴（Non-Recursive）兩種方式來實現。

### 解題策略

1. **遞迴版本**：
    直接根據數學定義將 $A(m, n)$ 轉換為 C++ 函式。此方法程式碼簡潔，與原始定義高度對應。

2. **非遞迴版本**：
    為避免遞迴深度過深導致堆疊溢位（Stack Overflow），使用一個手動管理的動態陣列來模擬堆疊行為。透過手動管理此堆疊，將計算狀態（$m$ 的值）存入其中，並在迴圈中處理，直到計算完成。此方法還包含動態擴展堆疊容量的機制，以應對計算過程中可能出現的堆疊需求增長。

## 程式實作

```cpp
// 遞迴
int ackermann_recursive(int m, int n)
{

  if (m == 0)
  {
    return n + 1;
  }
  else if (m > 0 && n == 0)
  {
    return ackermann_recursive(m - 1, 1);
  }
  else if (m > 0 && n > 0)
  {
    return ackermann_recursive(m - 1, ackermann_recursive(m, n - 1));
  }
  return -1; //- 如果無效輸入
}

// 非遞迴
int ackermann_non_recursive(int m, int n)
{
  int stack_capacity = 1000;
  int *stack = new int[stack_capacity]; //- 因為內建的Array不是STL東西 所以拿來用了
  int stack_top = -1;

  // 從初始的 'm' 值開始。
  stack[++stack_top] = m;

  while (stack_top != -1)
  {
    //- 當 stack 不是空的
    int current_m = stack[stack_top];
    stack_top--; // 彈出

    if (current_m == 0)
    {
      n = n + 1;
    }
    else if (n == 0)
    {
      //- 函數 => A(m-1, 1)
      stack_top++;
      stack[stack_top] = current_m - 1;
      n = 1;
    }
    else
    {
      //- 函數 => A(m-1, A(m, n-1))
      // 檢查堆疊是否溢位
      if (stack_top + 2 >= stack_capacity)
      {
        int new_capacity = stack_capacity * 2;
        int *new_stack = new int[new_capacity];

        //- 複製舊的值
        for (int i = 0; i <= stack_top; ++i)
        {
          new_stack[i] = stack[i];
        }
        delete[] stack; // 釋放舊記憶體
        stack = new_stack;
        stack_capacity = new_capacity;
      }

      // 推入 m-1
      stack_top++;
      stack[stack_top] = current_m - 1;

      // 推入 m (用於內部的 A(m, n-1))
      stack_top++;
      stack[stack_top] = current_m;

      // 為內部呼叫設定 n
      n = n - 1;
    }
  }

  delete[] stack; // 釋放分配的記憶體
  return n;
}
```

## 效能分析

1. **時間複雜度**：阿克曼函式的時間複雜度增長速度極快，無法用標準的多項式或指數時間 $O(n^k)$ 或 $O(k^n)$ 來有效描述。
2. **空間複雜度**：
    * **遞迴版本**：空間複雜度與最大遞迴深度成正比，約為 $O(m + A(m, n))$，對於稍大的 $m$ 和 $n$ 就會輕易導致堆疊溢位。
    * **非遞迴版本**：空間複雜度取決於堆疊的最大尺寸，與遞迴版本的最大深度類似，但由於使用堆（Heap）空間並可動態擴展，較不容易發生溢位。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 (m, n) | 預期輸出 | 實際輸出 |
|----------|-----------------|----------|----------|
| 測試一   | (0, 0)          | 1        | 1        |
| 測試二   | (1, 2)          | 4        | 4        |
| 測試三   | (2, 1)          | 5        | 5        |
| 測試四   | (3, 0)          | 5        | 5        |
| 測試五   | (3, 1)          | 13       | 13       |

### 編譯與執行指令

```shell
$ g++ -std=c++11 -o hw1P1 ./homework1_Problem1/src/main.cpp
$ ./hw1P1
```

### 結論

1. 程式成功實作了阿克曼函式的遞迴與非遞迴版本。
2. 對於小的輸入值，兩種版本的計算結果皆符合預期。
3. 程式包含引導使用者輸入的提示，並對遞迴版本可能發生的堆疊溢位問題提出警告。

## 申論及開發報告

### 遞迴與非遞迴的比較

1. **遞迴版本：直觀且易於理解**
    遞迴的寫法直接翻譯了阿克曼函式的數學定義，程式碼結構清晰，邏輯與原始問題高度一致。這使得程式碼非常容易閱讀和驗證其正確性。然而，其缺點也非常明顯：
    * **堆疊溢位風險**：每次函式呼叫都會在呼叫堆疊 (Call Stack) 中產生一個新的堆疊幀 (Stack Frame)。當 $m$ 和 $n$ 稍大時，遞迴深度會急遽增加，快速耗盡堆疊空間，導致程式崩潰 *(ex. **A(3, 18)**)*。

2. **非遞迴版本：效能與穩定性的考量**
    非遞迴版本透過手動維護一個位於堆（Heap）上的動態陣列來模擬堆疊行為。這種方式的優點是：
    * **避免堆疊溢位**：堆的空間遠大於堆疊，因此可以計算更大範圍的 $m$ 和 $n$ 值，程式穩定性更高。此外，當堆疊空間不足時，程式會自動擴展容量，進一步增強其穩健性。
    * **效能可能更佳**：雖然演算法的根本複雜度不變，但避免了函式呼叫的額外開銷 (overhead)，在某些情況下執行效率可能略高。
    其缺點是程式碼的複雜度較高，不如遞迴版本直觀，需要更仔細地追蹤狀態（如堆疊頂端、m 和 n 的變化）來理解其運作原理，且需要手動管理記憶體。