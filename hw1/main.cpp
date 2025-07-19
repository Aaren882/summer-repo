#include <iostream>
#include <windows.h> // #NOTE - For Chinese characters in console
#include <stack>

// Recursive implementation of Ackermann's function
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
  return -1; // Should not happen for non-negative m, n
}

// Non-recursive implementation of Ackermann's function
int ackermann_non_recursive(int m, int n)
{
  std::stack<int> s;
  s.push(m);

  while (!s.empty())
  {
    m = s.top();
    s.pop();

    if (m == 0)
    {
      n = n + 1;
    }
    else if (n == 0)
    {
      s.push(m - 1);
      n = 1;
    }
    else
    {
      s.push(m - 1);
      s.push(m);
      n = n - 1;
    }
  }
  return n;
}

int main()
{
  try
  {

    SetConsoleOutputCP(65001); // For Chinese characters in console

    int m, n;
    printf("- 輸入 m 和 n，兩者皆為[非負數整數]。\n");
    printf("- 警告❌: 這個Function的成長速度非常快，請小心使用。\n");
    printf("- (e.g., m < 4)\n");
    printf("輸入 m : ");
    std::cin >> m;
    printf("輸入 n: ");
    std::cin >> n;

    if (m < 0 || n < 0)
    {
      throw std::runtime_error("m 或 n 為負數，請重新輸入。\n");
    }

    printf("\n使用遞迴計算...\n");
    // For larger values, recursive version can cause stack overflow.
    if (m > 3)
    {
      printf("看來 m > 3 遞迴可能會造成 stack overflow。\n");
    }
    else
    {
      int result_recursive = ackermann_recursive(m, n);
      printf("A(%1d,%2d) = %3d\n", m, n, result_recursive);
    }

    printf("\n使用非遞迴計算...\n");
    int result_non_recursive = ackermann_non_recursive(m, n);
    printf("A(%1d,%2d) = %3d\n", m, n, result_non_recursive);
    return 0;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << "Runtime error: " << e.what() << std::endl;
    return 1;
  }
  catch (const std::exception &e)
  {
    std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "An unknown error occurred." << std::endl;
    return 1;
  }
}
