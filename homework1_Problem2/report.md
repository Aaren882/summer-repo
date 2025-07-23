# 41141141

作業一 Problem 2

## 解題說明

這題是要寫一個遞迴函式，來找出一個字串所有可能的字元組合 (冪集, powerset)，然後把它們印出來。

### 解題策略

我想到的解法是用遞迴。概念很簡單，就是對字串裡的每個字元，都有兩種可能：**選它**或**不選它**。

1.  **遞迴函式 `powerSet`**
    這個函式需要幾個參數：
    *   `S`：原本的字串。
    *   `index`：現在處理到第幾個字元。
    *   `current`：目前為止選了哪些字元，組成的字串。

2.  **遞迴的終點 (Base Case)**
    當 `index` 走到底，就代表我們已經對所有字元決定要不要選了。這時候 `current` 就是一個完整的組合，把它印出來就對了。

3.  **遞迴下去 (Recursive Step)**
    在還沒到底之前，對於 `S[index]` 這個字元：
    *   **Case 1: 不選**
        直接跳過，去處理下一個字元：`powerSet(S, index + 1, current)`。
    *   **Case 2: 選**
        把 `S[index]` 加到 `current` 後面，然後去處理下一個字元：`powerSet(S, index + 1, current + S[index])`。

4.  **一開始怎麼呼叫**
    從 `main` 函式裡，用 `index = 0` 和一個空字串 `""` 開始，就能跑出所有組合了。

## 程式實作

```cpp
// -- 使用遞迴尋找並印出所有子集（冪集）--
//- S 輸入的字串，代表元素集合
//- index 目前在 S 中考慮的字元位置
//- current 正在建立的目前子集字串
void powerSet(const string &S, int index, string current)
{
  // 基本情況：當索引到達輸入字串 S 的末尾時
  if (index == S.length())
  {
    // 印出結果子集
    cout << "{ ";
    for (char c : current)
    {
      cout << c << " ";
    }
    cout << "}" << endl;
    return;
  }

  // --- 遞迴 ---

  // 情況 1：不包含字元 S[index]
  // 我們為下一個索引呼叫函式，並傳入未修改的 `current` 字串
  powerSet(S, index + 1, current);

  // 情況 2：包含字元 S[index]
  // 我們為下一個索引呼叫函式，並傳遞一個新的 `current` 字串，
  powerSet(S, index + 1, current + S[index]);
}
```

## 效能分析

1.  **時間複雜度 (Time Complexity): $O(2^n \cdot n)$**
    n 是字串長度。因為總共有 $2^n$ 個子集，然後每個子集印出來最長要花 n 的時間，所以總共是 $O(2^n \cdot n)$。

2.  **空間複雜度 (Space Complexity): $O(n)$**
    主要是遞迴的深度，最多就 n 層。還有那個 `current` 字串也最多 n 個字。所以是 $O(n)$。這樣比把所有 $2^n$ 個答案都存起來省空間多了。

## 測試與驗證

### 測試結果

| 測試案例 | 輸入 `S` | 跑出來的結果 (順序可能會不一樣) |
|---|---|---|
| 測試一 | `"abc"` | `{ }`<br>`{ c }`<br>`{ b }`<br>`{ b c }`<br>`{ a }`<br>`{ a c }`<br>`{ a b }`<br>`{ a b c }` |
| 測試二 | `"ab"` | `{ }`<br>`{ b }`<br>`{ a }`<br>`{ a b }` |
| 測試三 | `"a"` | `{ }`<br>`{ a }` |

### 編譯和執行指令

```shell
$ g++ -std=c++17 -o hw1P2 ./homework1_Problem2/src/main.cpp
$ ./hw1P2
```

## 申論及開發報告

* 冪集就是對每個元素「選」或「不選」，這剛好可以很自然地用遞迴來表達，就像樹狀結構一樣。
```