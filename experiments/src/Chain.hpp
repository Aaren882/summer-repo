template <class T>
class Chain
{
private:
  int capacity;
  ChainNode<T> *pfirst;
  ChainNode<T> *plast;

public:
  int size = 0;

  Chain(int capacity)
  {
    this->capacity = capacity;
  }
  //- Add NewNode
  int Add(const T input)
  {
    
    //- de-ref the "newNode"
    ChainNode<T> *pNewNode = new ChainNode<T>(input);

    //-#NOTE - Pointer is C++ nature, must get use to it

    if (size == 0) //- #NOTE - Check empty
    {
      this->pfirst = pNewNode; //- the first Node
      pfirst->plink = pNewNode; //- Push back
    }
    else
    {
      plast->plink = pNewNode; //- Push back
    }

    this->plast = pNewNode;

    size++; //- increase size
    return size;
  }
  int Delete(int index)
  {
    ChainNode<T>* first = this->pfirst;
    
    if (!first) throw "This Chain is empty.";
    if (index > size - 1) throw "Index out of range.";

    if (index == 0) {
      this->pfirst = first->plink;
      delete first;
    } else {
      ChainNode<T>* before = this->pfirst;
      ChainNode<T>* current = before;

      for (int i = 0; i < index; i++) {
        before = current;
        current = current->plink;
      }

      //- rewire the links
      before->plink = current->plink;
      delete current;
    }

    size--; //- decrease size
    return size;
  }
  int Insert(int index,const T data)
  {
    ChainNode<T>* first = this->pfirst;
    
    if (!first) throw "This Chain is empty.";
    if (index > size - 1) throw "Index out of range.";

    
    if (index == 0) {
      new ChainNode(data, first);
    } else {
      ChainNode<T>* before = this->pfirst;
      ChainNode<T>* current = before;

      for (int i = 0; i < index; i++) {
        before = current;
        current = current->plink;
      }

      //- rewire the links
      ChainNode<T>* newNode = new ChainNode(data, current); //- Point to the pointer from the origin index
      before->plink = newNode; //- point to newNode
    }

    size++; //- increase size
    return size;
  }
  //- Get
  ChainNode<T> get(int index)
  {
    if (index >= size)
    {
      throw "Out of Chain Range.";
    }

    ChainNode<T> *result;
    for (int i = 0; i <= index; i++)
    {
      result = pfirst->plink;
    }

    return *result; //- de-Ref
  }
  //- Find the index of given data
  int indexOf (T theElem) {
    int index = 0;
    ChainNode<T>* current = this->pfirst;
    while (current && current->data != theElem) {
      current = current->plink;
      index++;
    }

    if (!current) return -1; //- check current exist

    return index;
  }
};