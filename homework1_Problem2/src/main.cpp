#include <iostream>
#include <string>
using namespace std;

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

int main() {
    string S1 = "abc";
    cout << "--- S = \"" << S1 << "\" ---" << endl;
    
    // 從第一個字元（索引 0）
    powerSet(S1, 0, "");

    return 0;
}