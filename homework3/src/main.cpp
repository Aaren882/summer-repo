#include "iostream"
#include "sstream"

using namespace std;

class Term
{
  friend class Polynomial;
  friend class Available;

private:
  float coef = 0; //- Coefficient
  int exp = 0;    //- Exponent

  //- #NOTE - if exponents are equal, it will modify "this->coef"
  bool Add(const Term &addterm)
  {
    //- Check exponent equallty
    if (this->exp == addterm.exp)
    {
      this->coef += addterm.coef;
      return true;
    }
    return false;
  }

public:
  Term() {};
  Term(float c, int e)
  {
    this->coef = c;
    this->exp = e;
  };

  //- overloads
  int operator==(Term &other)
  {
    return this->coef == other.coef &&
           this->exp == other.exp;
  }
  int operator+(const Term & other)
  {
    return Add(other);
  }
};

#include "headers\ChainNode.hpp"
#include "headers\Chain.hpp"
#include "headers\Available.hpp"
#include "headers\Polynomial.hpp"

//- Overloads for input/output
ostream &operator<<(ostream &os, Polynomial &poly)
{
  os << poly.getVisualizer();
  return os;
}

istream &operator>>(istream &is, Polynomial &poly)
{

  //- Ex. 2x^3 + 1 = "2 3 1 0"
  cout << "Enter the Polynomial :" << endl;
  cout << "Input format Pairs(n),Exponent,Coefficient,Exponent,Coefficient..." << endl;
  cout << "ex. 2x^3 + 1 = \"2,3,2,0,1\"" << endl
            << "::";

  // ex. "2x^3 + 5x - 1"
  // "2 3 5 1 -1 0" (must be pairs)
  
  float coef = 1;
  int n, exp = 0;
  char comma;
  is >> n;

  for (int i = 0; i < n; ++i)
  {
    is >> comma >> exp >> comma >> coef;
    poly.newTerm(coef, exp);
  }

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
  cout << "[" << a << "]" << endl;

  float x; //- X value for evaluation
  cout << endl
        << "Enter X value : ";
  cin >> x;

  cout << endl
        << "Evaluation : " << endl;
  cout << ": " << "x = " << x << endl;
  cout << ": " << a << " = " << a.Eval(x) << endl
       << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}