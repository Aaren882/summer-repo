#include "iostream"
#include "sstream"
#include "math.h"
using namespace std;

class Polynominal;
class Term
{
  friend Polynominal;
  private:
    float coef = 0; //- Coefficient
    int exp = 0;    //- Exponent
};

class Polynominal
{
  private:
    Term *termArray = {};
    int terms = 0; //- how many "Term" in "termArray"
    bool valueRegistered;
    float theValue;
    int capacity;
    /* void sort() { //- Arrange Polynominal
      Term *newArray = new Term[capacity];
      for (int i = 0; i < terms; i++)
      {
        Term term = termArray[i];
        if (term.exp)
          break;
        newArray[term.exp] = term;
      }
      delete[] termArray;
      termArray = newArray;
    } */

  public:
    Polynominal(const int &cap = 1)
    {
      if (cap < 1)
        throw "invaild capacity.";

      this->capacity = cap;
      termArray = new Term[capacity];
    };
    /* Polynominal(const int &cap = 1, const float &x)
    {
      if (cap < 1)
        throw "invaild capacity.";
      
      setValue(x); //- Set X value for this polynomial
      this->capacity = cap;
      termArray = new Term[capacity];
    }; */

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

    Polynominal Add(const Polynominal poly)
    {
      
      Polynominal result = Polynominal(poly.terms + this->terms);
      Term *_resultArray = result.termArray;

      //- Copy current props into result
      result.terms = this->terms;
      copy(this->termArray, this->termArray + this->terms, _resultArray);
      
      //- Add poly's terms into result.termArray
      for (int i = 0; i < poly.terms; i++)
      {
        Term addterm = poly.termArray[i];
        result.newTerm(addterm.coef, addterm.exp);
      }

      return result;
    }

    Polynominal Mult(Polynominal poly)
    {

      Polynominal result = Polynominal();

      // (x^2 + 2) * (2x^2) = x^4 + 2
      //- Add poly's terms into result.termArray
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
    Polynominal operator+(const Polynominal &b)
    {
      return this->Add(b);
    }
    Polynominal operator*(const Polynominal &b)
    {
      return this->Mult(b);
    }
};

//- Overloads for input/output
ostream &operator<<(ostream &os, Polynominal &poly)
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

istream &operator>>(istream &is, Polynominal &poly)
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

  /* Polynominal a; //- Setup A

  // (Coef, Exp)
  a.newTerm(2,1);
  a.newTerm(2,0);

  Polynominal b; //- Setup B
  b.newTerm(4, 1); //- Return (coef: 3, Exp: 2)
  b.setValue(2);
  a.setValue(2);

  //- Add two polynominals
  Polynominal c = a + b; //- (2x + 2) + (4x) = 6x + 2
  Polynominal d = a * b; //- (2x + 2) * (4x) = 8x^2 + 8x

  cout << "Result A : " << a << endl;
  cout << "Result B : " << b << endl;
  cout << "Result A + B : " << c << endl;
  cout << "Result A * B : " << d << endl; */

  Polynominal a; //- Setup A
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