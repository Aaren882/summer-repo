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
    Term *termArray = {};
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
    Polynominal(const int cap = 1)
    {
      if (cap < 1)
        throw "invaild capacity.";

      this->capacity = cap;
      termArray = new Term[capacity];
    };

    bool newTerm(float coef, int exp) {
      if (coef == 0)
        throw "coef is 0";

      //- Adjust termArray capacity x2
      if (terms > capacity - 1) {

        capacity *= 2;
        Term *newArray = new Term[capacity];

        //- Copy termArray
        copy(termArray, termArray + terms, newArray);
        /* for (int i = 0; i < capacity; i++)
        {
          newArray[i] = termArray[i];
        } */
        delete[] termArray;
        
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
    Polynominal Add(const Polynominal poly) {
      
      Polynominal result = Polynominal(poly.terms + this->terms); //- de-Ref
      Term *_resultArray = result.termArray;

      //- Copy current props into result
      result.maxExp = this->maxExp;
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
    // Polynominal Mult(Polynominal poly);
    
    int maxExponent() {
      return maxExp;
    }
    double Eval(float x)
    {
      double result;

      for (int i = 0; i < terms; i++)
      {
        Term *term = &termArray[i]; //- pointer
        if (!term) break;
        result += (double)term->coef * pow(x, term->exp);
      }

      return result;
    };
};

int main() {

  Polynominal a; //- Setup capacity

  // (Coef, Exp)
  a.newTerm(1,2);
  a.newTerm(2,0);

  Polynominal b; //- Setup capacity
  b.newTerm(2, 2); //- Return (coef: 3, Exp: 2)

  //- Add two polynominals
  Polynominal c = a.Add(b);

  float x;
  cout << "input X : ";
  cin >> x;
  // x = 0 + x;

  cout << "Result A : " << a.Eval(x) << endl;
  cout << "Result B : " << b.Eval(x) << endl;
  cout << "Result C : " << c.Eval(x) << endl;

  printf("Press Enter to exit...\n");
  cin.ignore().get();

  return 0;
}