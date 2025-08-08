class Available
{
private:
  ChainNode<Term> *avaList = nullptr; //- the first node

public:
  Available(){
    avaList = nullptr;
  }
  ~Available(){
    cout << "Destructing available list." << std::endl;
    while (avaList) {
      ChainNode<Term>* temp = avaList;
      avaList = avaList->plink;
      delete temp;
    }
  }
  
  //- Add NewNodes
  /*
    it pushes "node" ChainNode ONTO available list
    ("node...LAST") → avaList<ChainNode<Term>>
  */
  void getBack(ChainNode<Term>* node) 
  {
    ChainNode<Term>* current = node;
    
    cout << endl;
    int i = 1;
    cout << "Constructing available list." << endl;
    while (true) {

      //- Display the result
      Term t = current->getData();
      cout << i << "th: " << t.coef << "x^" << t.exp << endl;
      i++;

      if (!current->plink) break;
      current = current->plink;
    }
    current->plink = avaList;
    avaList = node;
  }
  //- Pop First element (avaList)
  ChainNode<Term>* getOneNode()
  {
    if (avaList == nullptr) return new ChainNode<Term>(); //- if list empty
    ChainNode<Term>* node = avaList;
    avaList = avaList->plink;
    node->plink = nullptr;

    return node; 
  }
};