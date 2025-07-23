#include <iostream>
using namespace std;

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

int main()
{
  int m, n;
  printf("m : ");
  cin >> m;
  printf("n: ");
  cin >> n;

  //- 對於較大的值，遞迴版本可能會導致 stack overflow
  if (m > 3)
  {
    printf("m > 3 may cause stack overflow.\n");
  }
  else
  {
    printf("\nUse Recursive Function...\n");
    int result_recursive = ackermann_recursive(m, n);
    printf("A(%1d,%2d) = %3d\n", m, n, result_recursive);
  }

  printf("\nUse Non-recursive Function...\n");
  int result_non_recursive = ackermann_non_recursive(m, n);
  printf("A(%1d,%2d) = %3d\n", m, n, result_non_recursive);

  //- 暫停
  printf("Press Enter to exit...");
  cin.ignore().get();

  return 0;
}