#include "iostream"
#include "sstream"
#include "math.h"

template <class T>
class Chain;
class Term
{
  friend class Polynomial;

private:
  float coef = 0; //- Coefficient
  int exp = 0;    //- Exponent
  
  //- #NOTE - if exponents are equal, it will modify "this->coef"
  bool Add(const Term& addterm)
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
  operator==(Term &other) {
    return this->coef == other.coef &&
      this->exp == other.exp;
  }
  operator+(const Term& other) {
    return Add(other);
  }
};

class Polynomial
{
  friend ostream &operator<<(ostream& os, const Polynomial& poly);
  friend istream &operator>>(istream &is, Polynomial &poly);

private:
  Chain<Term> *termArray = nullptr;
  int terms = 0; //- how many "Term" in "termArray"
  bool valueRegistered = false;
  float theValue = 0;
  int capacity = 0;

public:
  Polynomial(const int &cap = 50)
  {
    if (cap < 1)
      throw "invaild capacity.";

    this->capacity = cap;
    this->termArray = new Chain<Term>(5);
  }
  Polynomial(const Polynomial& Poly) //- Clone contructor
  {
    this->terms = Poly.terms;
    this->capacity = Poly.capacity;
    this->termArray = Poly.termArray;
  }

  bool newTerm(float coef, int exp)
  {
    if (coef == 0)
      return false; //- coef is 0

    //- Capacity Check 
    if (terms > capacity - 1)
      throw "Reached Polynomial Capacity !!";
    
    //- New a term object
    Term* newTerm = new Term(coef,exp);
    for (int i = 0; i < terms; i++)
    {
      Term& term = GetTerm(i);

      //- if they're able to be add up
      if (term.Add(*newTerm)) //- #NOTE - "term->coef" will be modified
      {
        if (term.coef == 0) //- if coef == 0 then Delete that node
        {
          termArray->Delete(i);
          terms--;
        }
        return true; //- Just exit and return
      }
    }
    termArray->Add(*newTerm);
    terms++;
 
    return true;
  };
  //- #TODO - Available-Space List
  void RemoveTerm(Term& element)
  {
    int index = termArray->indexOf(element);
    termArray->Delete(index);
  }
  Term& GetTerm(int index) //- #NOTE - This returns ref-value (dangerous? 🤔 IDK)
  {
    ChainNode<Term>* returnNode = this->termArray->get(index);
    return returnNode->data;
  }
  
  //- Operators
  Polynomial Add(const Polynomial& poly)
  {
    //- Clone the given Polynomial 
    Polynomial* result = new Polynomial(*this);

    //- Add poly's terms into result.termArray
    for (int i = 0; i < poly.terms; i++)
    {
      ChainNode<Term>* addNode = poly.termArray->get(i);
      Term term = addNode->data;

      result->newTerm(term.coef,term.exp);
    }

    return *result; 
  }
  Polynomial Minus(const Polynomial& poly)
  {
    //- Clone the given Polynomial 
    Polynomial* result = new Polynomial(*this);

    //- Add poly's terms into result.termArray
    for (int i = 0; i < poly.terms; i++)
    {
      ChainNode<Term>* addNode = poly.termArray->get(i);
      Term term = addNode->data;

      result->newTerm(-term.coef,term.exp); //- Same as Add() but with "-term.coef"
    }

    return *result;
  }
  Polynomial Mult(const Polynomial& poly)
  {
    //- Clone the given Polynomial 
    Polynomial* result = new Polynomial(poly.terms + terms);

    // (x^2 + 2) * (2x^2) = x^4 + 4x^2
    //- Add poly's terms into result.termArray
    for (int i = 0; i < poly.terms; i++)
    {
      ChainNode<Term>* addNode = poly.termArray->get(i);
      Term addterm = addNode->data;
      
      for (int j = 0; j < this->terms; j++)
      {
        Term term = this->GetTerm(j);
        if (!term.coef || !addterm.coef) //- if coef is 0, skip
          break;
        result->newTerm(term.coef * addterm.coef, term.exp + addterm.exp);
      }
    }

    return *result;
  };

  //- Evaluation
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
      Term *term = &GetTerm(i); //- pointer
      if (!term)
        break;
      result += (double)term->coef * pow(this->theValue, term->exp);
    }

    return result;
  };

  string getVisualizer()
  {
    stringstream ss;

    for (int i = 0; i < terms; i++)
    {
      Term term = this->GetTerm(i);
      
      if (i > 0 && term.coef >= 0)
        ss << " + ";

      ss << term.coef;

      if (term.exp != 0)
        ss << "x^" << term.exp;
    }

    return ss.str();
  }

  //- overloads
  Polynomial operator+(const Polynomial &b)
  {
    return this->Add(b);
  }
  Polynomial operator-(const Polynomial &b)
  {
    return this->Minus(b);
  }
  Polynomial operator*(const Polynomial &b)
  {
    return this->Mult(b);
  }
};
