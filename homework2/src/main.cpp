#include "iostream"
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
    int capacity;
    int maxExp = 0; //- maximum of exponent number
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
    int terms = 0; //- how many "Term" in "termArray"
    Term *termArray = {};
    Polynominal(int cap = 1)
    {
      if (cap < 1)
        throw "invaild capacity.";

      this->capacity = cap;
      termArray = new Term[capacity];
    };

    bool newPoly(float coef, int exp) {
      if (coef == 0)
        throw "coef is 0";

      //- Adjust termArray capacity x2
      if (terms > capacity - 1) {

        Term* newArray = new Term[2 * capacity];

        //- Copy termArray
        for (int i = 0; i < capacity; i++)
        {
          newArray[i] = termArray[i];
        }
        delete[] termArray;
        
        capacity *= 2;
        termArray = newArray;
      }

      //- Check max exponent
      if (exp > maxExponent())
        maxExp = exp;

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
    Polynominal Add(Polynominal poly) {
      
      Polynominal result = Polynominal(poly.terms + this->terms); //- de-Ref
      
      int maxTerms = max(terms, poly.terms);
      Term *addArray = poly.termArray;
      
      for (int i = 0; i < maxTerms; i++)
      {
        Term term = this->termArray[i];
        if (term.exp)
          result.newPoly(term.coef, term.exp);

        Term addterm = addArray[i];
        if (addterm.exp)
          result.newPoly(addterm.coef, addterm.exp);
      }

      return result;
    }
    // Polynominal Mult(Polynominal poly);
    
    int maxExponent() {
      return maxExp;
    }
    /* string getVisualize() {
      string result;
      string _prefix = "";

      
      for (int i = 0; i < terms; i++)
      {
        Term term = termArray[i];
        
        // string _str = "";
        char _coef[1000];
        char _exp[1000];
        // string _exp = "";

        if (i != 0)
          if (term.coef > 0){_prefix = "+";} else { _prefix = "-";}

        sprintf(_coef, "%d", term.coef);
        sprintf(_exp, "^%f", term.exp);
        if (_coef == "0")      //- Check coef Exist
          _coef[0] = '\0';
        if (term.exp)         //- Check Exponent Exist
          _exp[0] = '\0';

          result += _prefix + _coef + "x" + _exp;

        // result += _str;
      }
      return result;
    } */
    double Eval(float x)
    {
      double result = 0.0;

      for (int i = 0; i < terms; i++)
      {
        Term *term = &termArray[i]; //- pointer
        if (!term) break;
        result += term->coef * pow(x, term->exp);
      }

      return result;
    };
};

int main() {

  Polynominal a; //- Setup capacity

  // (Coef, Exp)
  a.newPoly(1,2);
  a.newPoly(2,0);

  Polynominal b; //- Setup capacity
  b.newPoly(2, 2); //- Return (coef: 3, Exp: 2)

  Polynominal c; //- Setup capacity
  c.newPoly(1, 2);
  c.newPoly(2, 0);
  c.newPoly(2, 2); //- Return (coef: 3, Exp: 2)
  // Polynominal c = c.Add(b);

  float x;
  cout << "input X : ";
  cin >> x;
  x = 0 + x;

  cout << "Result A : " << a.Eval(x) << endl;
  cout << "Result B : " << b.Eval(x) << endl;
  cout << "Result C : " << c.Eval(x) << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}