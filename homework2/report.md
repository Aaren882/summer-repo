# 41141141

作業二

## 解題說明

這次作業是做一個多項式計算機，要可以加、可以乘，還要可以代入 x 算出答案。

### 解題策略

1.  **使用 Class**：
    *   我弄了一個 `Term` 的 class，專門用來存每一項的係數 (`coef`) 和次方 (`exp`)。
    *   然後再一個 `Polynomial` 的 class，裡面包一個 `termArray` 陣列，把所有的 `Term` 都丟進去。
2.  **陣列不夠大時**：
    *   `Polynomial` 一開始會先開一個陣列，但可能不夠用。
    *   所以當我用 `newTerm` 加新的項進去，如果發現陣列滿了，我就會直接把陣列容量變兩倍大，然後把舊的東西全部複製過去。
3.  **主要功能**：
    *   `newTerm(float coef, int exp)`：加一個新的項。如果那個次方的項已經有了，就把係數加起來；如果沒有，就新增一個。
    *   `Add(Polynomial poly)`：多項式加法。把另一個多項式 `poly` 裡面的每一項，都用 `newTerm` 加到我自己的多項式裡。
    *   `Mult(Polynomial poly)`：多項式乘法。這個比較暴力，我用了兩層 for 迴圈，把兩個多項式的每一項都互相乘起來，然後把結果用 `newTerm` 加到一個新的多項式裡。
    *   `Eval()`：算答案。就代入 x 啊，把每一項的 `coef * x^exp` 都算出來，然後全部加起來。
4.  **讓 code 變好看**：
    *   我用了運算子重載 (Operator Overloading)，把 `+` 和 `*` 都重載了，這樣就可以直接用 `p1 + p2` 這種方式來算，看起來很直觀。
    *   `<<` 和 `>>` 也重載了，這樣輸入和輸出就方便多了。

## 程式實作
```cpp
#include "iostream"
#include "sstream"
#include "math.h"
using namespace std;

class Polynomial;
class Term
{
  friend Polynomial;
  private:
    float coef = 0; //- Coefficient
    int exp = 0;    //- Exponent
};

class Polynomial
{
  private:
    Term *termArray = {};
    int terms = 0; //- how many "Term" in "termArray"
    bool valueRegistered;
    float theValue;
    int capacity;

  public:
    Polynomial(const int &cap = 1)
    {
      if (cap < 1)
        throw "invaild capacity.";

      this->capacity = cap;
      termArray = new Term[capacity];
    };

    bool newTerm(float coef, int exp)
    {
      if (coef == 0)
        throw "coef is 0";

      //- Adjust termArray capacity x2
      if (terms > capacity - 1) {

        capacity *= 2;
        Term *newArray = new Term[capacity];

        //- Copy termArray
        copy(termArray, termArray + terms, newArray);
        delete[] termArray;
        
        termArray = newArray;
      }

      for (int i = 0; i < capacity; i++)
      {
        Term *currnent = &termArray[i];
        if (!currnent) break;

        if (currnent->exp == exp)
        {
          currnent->coef = currnent->coef + coef; //- update the exist coefficient
          break;
        } else {
          Term *t = &termArray[terms];
          terms++;
          t->coef = coef;
          t->exp = exp;
          break;
        }
      }

      return true;
    };

    Polynomial Add(const Polynomial poly)
    {
      
      Polynomial result = Polynomial(poly.terms + this->terms);
      Term *_resultArray = result.termArray;

      //- Copy current props into result
      result.terms = this->terms;
      copy(this->termArray, this->termArray + this->terms, _resultArray);
      
      //- Add poly\'s terms into result.termArray
      for (int i = 0; i < poly.terms; i++)
      {
        Term addterm = poly.termArray[i];
        result.newTerm(addterm.coef, addterm.exp);
      }

      return result;
    }

    Polynomial Mult(Polynomial poly)
    {

      Polynomial result = Polynomial();

      // (x^2 + 2) * (2x^2) = x^4 + 2
      //- Add poly\'s terms into result.termArray
      for (int i = 0; i < poly.terms; i++)
      {
        Term addterm = poly.termArray[i];
        for (int j = 0; j < this->terms; j++)
        {
          Term term = this->termArray[j];
          if (!term.coef || !addterm.coef) //- if coef is 0, skip
            break;
          result.newTerm(term.coef * addterm.coef, term.exp + addterm.exp);
        }
      }

      return result;
    };

    void setValue(const float &x)
    {
      theValue = x;
      valueRegistered = true;
    }
    bool hasValue()
    {
      return valueRegistered;
    }
    double Eval()
    {
      double result = 0;

      for (int i = 0; i < terms; i++)
      {
        Term *term = &termArray[i]; //- pointer
        if (!term) break;
        result += (double)term->coef * pow(this->theValue, term->exp);
      }

      return result;
    };

    string getVisualizer()
    {
      stringstream ss;
      
      for (int i = 0; i < terms; i++)
      {
        Term *term = &this->termArray[i];
        if (!term) break;

        if (i > 0 && term->coef >= 0)
          ss << " + ";

        ss << term->coef;

        if (term->exp != 0)
          ss << "x^" << term->exp;
      }

      return ss.str();
    }

    //- overloads
    Polynomial operator+(const Polynomial &b)
    {
      return this->Add(b);
    }
    Polynomial operator*(const Polynomial &b)
    {
      return this->Mult(b);
    }
};

//- Overloads for input/output
ostream &operator<<(ostream &os, Polynomial &poly)
{
  float x;

  if (!poly.hasValue())
  {
    cout << endl << "input X value : ";
    cin >> x;
    poly.setValue(x);
  }

  os << poly.Eval();
  return os;
}

istream &operator>>(istream &is, Polynomial &poly)
{
  
  //- Ex. 2x^3 + 1 = "2 3 1 0"
  cout << "Enter the Polynomial :" << endl;
  cout << "ex. " << "2x^3 + 1 = \"2 3 1 0\"" << endl << "::";

  string input;
  getline(is, input);

  // ex. "2x^3 + 5x - 1"
  // "2 3 5 1 -1 0" (must be pairs)
  stringstream ss(input);

  float coef = 1;
  int exp = 0;
  while (ss >> coef >> exp)
  {
    poly.newTerm(coef, exp);
  }

  ss.clear();
  ss.str("");

  return is;
}

int main() {
  Polynomial a; //- Setup A
  cin >> a;
  cout << "[" << a.getVisualizer() << "]" << endl;

  float x; //- X value for evaluation
  cout << endl << "Enter X value : ";
  cin >> x;
  a.setValue(x);

  cout << endl << "Evaluation : " << endl;
  cout << ": " << "x = " << x << endl;
  cout << ": " << a.getVisualizer() << " = " << a << endl << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}
```

## 效能分析

如果我有兩個多項式，一個有 N 項，一個有 M 項。

1.  **時間複雜度**：
    *   **加法 `Add`**: 做的有點慢，大概是 $O(N \times M)$。
    *   **乘法 `Mult`**: 這個更慢，大概是 $O(N \times M \times (N+M))$，因為我一直呼叫 `newTerm`。
2.  **空間複雜度**：
    *   **加法 `Add`**: 需要 $O(N+M)$ 的空間。
    *   **乘法 `Mult`**: 需要 $O(N \times M)$ 的空間。

## 測試與驗證

就直接跑 `main` 就好，它會叫你輸入多項式和 x 的值。

### 測試案例

1.  **跑程式**
2.  **輸入多項式**: `Enter the Polynomial :`
    *   格式是 `係數 次方 係數 次方 ...`
    *   比如 $3x^2 + 5x^1 - 4$ 就要打 `3 2 5 1 -4 0`。
3.  **輸入 x**: `Enter X value :`
    *   打一個數字，比如 `2`。
4.  **看結果**: 程式會印出多項式長怎樣，還有算出來的答案。
    *   以上面的例子，x=2 的話，答案就是 18。

| 測試案例 | 輸入多項式 | 輸入 x | 預期輸出 |
|----------|--------------|----------|----------|
| 測試一   | `2 3 1 0`    | 2        | 17       |
| 測試二   | `1 2 2 1 1 0`| 3        | 16       |
| 測試三   | `2 3 2 4 1 0`| 2        | 49       |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o hw2 ./homework2/src/main.cpp
$ ./hw2
```

### 結論

1.  用 Class 來寫多項式還蠻酷的，程式看起來比較有條理。
2.  運算子重載超好用，寫起來很爽。
3.  我的 `newTerm` 和 `Mult` 寫得有點爛，如果項數很多的話，應該會跑很慢。有空再來改進。

## 申論及開發報告

這次作業用了物件導向 (OOP) 的方法，把多項式包成一個 `Polynomial` class，我覺得有幾個好處：

### 物件導向程式設計 (OOP) 的應用

1.  **封裝**：
    把資料 (`termArray`) 和功能 (`Add`, `Mult`) 包在一起，要用的時候直接呼叫就好。

2.  **抽象化**：
    `+` 和 `*` 寫起來就跟數學一樣，`>>` 和 `<<` 也很方便。

3.  **可重用性**：
    這個 `Polynomial` class 以後有其他作業要用到多項式，也能直接拿來用。

### 資料結構的選擇

我用了一個動態陣列來存多項式的每一項，空間不夠的時候會自動變大（兩倍）。

*   **優點**：寫起來很簡單。
*   **缺點**：
    *   每次陣列要變大，都要把全部的東西複製一次，很花時間。
    *   `newTerm` 找次方的時候，是一個一個找，如果資料很多會很慢。如果我先把陣列排好序，就可以用二分搜尋，會快很多，但就要一直排序，有點麻煩。

這次作業算是成功了，但效能感覺還有很多可以改進的地方。
