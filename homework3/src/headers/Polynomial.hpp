#include "iostream"
#include "sstream"
#include "math.h"

template <class T>
class Chain;
Available globalASL;

class Polynomial
{
  friend ostream &operator<<(ostream& os, const Polynomial& poly);
  friend istream &operator>>(istream &is, Polynomial &poly);

private:
  Chain<Term> *termArray = nullptr;
  int terms = 0; //- how many "Term" in "termArray"
  int capacity = 0;

public:
  Polynomial(const int &cap = 50)
  {
    if (cap < 1)
      throw "invaild capacity.";

    this->capacity = cap;
    this->termArray = new Chain<Term>;
  }
  Polynomial(const Polynomial& Poly) //- Clone contructor
  {
    this->terms = Poly.terms;
    this->capacity = Poly.capacity;
    this->termArray = Poly.termArray;
  }
  ~Polynomial() //- destructor
  {
    ChainNode<Term> *header = termArray->pfirst;
    ChainNode<Term> *last = termArray->plast;

    last->plink = nullptr;
    globalASL.getBack(header);
    header = last = nullptr;
    delete header;
    delete last;
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
    
    if (terms > 0) {
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

      //- Arrange List by exponent descending
      for (int i = 0; i < terms; i++) {
        Term& term = GetTerm(i);
        if (newTerm->exp > term.exp) { //- if "newTerm->exp" greater than "term.exp"
          termArray->Insert(i, *newTerm);
          terms++;
          return true;
        }
      }
    }
    
    //- when termArray empty
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
  Term& GetTerm(int index)const //- #NOTE - This returns ref-value (dangerous? 🤔 IDK)
  {
    return this->termArray->get(index)->getData();
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
      Term term = addNode->getData();

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
      Term term = addNode->getData();

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
      Term addterm = addNode->getData();
      
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
  double Eval(const float &x)
  {
    double result = 0;

    for (int i = 0; i < terms; i++)
    {
      Term *term = &GetTerm(i); //- pointer
      if (!term)
        break;
      result += (double)term->coef * pow(x, term->exp);
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
