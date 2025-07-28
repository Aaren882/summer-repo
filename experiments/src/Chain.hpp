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
};