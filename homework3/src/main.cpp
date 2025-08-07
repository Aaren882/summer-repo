#include "iostream"
#include "sstream"

using namespace std;

#include "headers\ChainNode.hpp"
#include "headers\Chain.hpp"
#include "headers\Polynomial.hpp"

//- Overloads for input/output
ostream &operator<<(ostream &os, Polynomial &poly)
{
  float x;

  if (!poly.hasValue())
  {
    cout << endl
              << "input X value : ";
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
  cout << "Input format Pairs(n),Exponent,Coefficient,Exponent,Coefficient..." << endl;
  cout << "ex. 2x^3 + 1 = \"2,3,2,0,1\"" << endl
            << "::";

  /* string input;
  getline(is, input); */

  // ex. "2x^3 + 5x - 1"
  // "2 3 5 1 -1 0" (must be pairs)
  // stringstream ss(input);
  
  float coef = 1;
  int n, exp = 0;
  char comma;
  is >> n;
  poly.capacity = n;

  for (int i = 0; i < n; ++i)
  {
    is >> comma >> exp >> comma >> coef;
    poly.newTerm(coef, exp);
  }

  //- OLD input functions
  /* while (ss >> comma >> coef >> comma >> exp)
  {
    poly.newTerm(coef, exp);
  }

  ss.clear();
  ss.str(""); */

  return is;
}

int main()
{
  /* Polynomial a = Polynomial(5); //- Setup A
  a.newTerm(1,2);
  a.newTerm(2,0);
  // a.newTerm(2,0);

  Polynomial b = Polynomial(5); //- Setup A
  b.newTerm(2, 0);

  // Polynomial c = a.Add(b);
  Polynomial c = a.Minus(b);
  // Polynomial c = a.Mult(b);

  cout
    << c.getVisualizer() << "\n"; */

  Polynomial a; //- Setup A
  cin >> a;
  cout << "[" << a.getVisualizer() << "]" << endl;

  float x; //- X value for evaluation
  cout << endl
        << "Enter X value : ";
  cin >> x;
  a.setValue(x);

  cout << endl
        << "Evaluation : " << endl;
  cout << ": " << "x = " << x << endl;
  cout << ": " << a.getVisualizer() << " = " << a << endl
        << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}