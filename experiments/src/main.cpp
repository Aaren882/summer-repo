#include "iostream"
using namespace std;
#include "ChainNode.hpp"
#include "Chain.hpp"

//- #NOTE - Cout Print
template <class U>
ostream &operator<<(ostream &os, const Chain<U> &chain)
{
  os << chain.size; //- Print the size of "Chain<>"
  return os;
}

int main() {
  Chain<string> chain1(5);
  chain1.Add("ww");
  chain1.Add("yyy");
  chain1.Add("aaa");

  cout << chain1.get(0).data << endl; //-Print the 0 data from chain1
  cout << chain1 << endl;             //-Print the size of chain1

  // cout << chain1.indexOf("ww") << endl;
  chain1.Delete(1);
  cout << chain1 << endl; //-Print the size of chain1

  return 0;
}