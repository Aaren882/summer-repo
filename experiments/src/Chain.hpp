template <class T>
class Chain
{
  private:
    int capacity;
    ChainNode<T> *first;
    ChainNode<T> *last;
    
  public:
    int size = 0;

    Chain(int capacity)
    {
      this->capacity = capacity;
    }
    //- Add NewNode
    int Add(const T &input)
    {
      //- de-ref the "newNode"
      ChainNode<T>* newNode = new ChainNode<T>(input);

      if (size == 0) //- #NOTE - Check empty
      {
        this->first = newNode;  //- the first Node
        first->link = newNode; //- Pushback
      }
      else
      {
        last->link = newNode; //- Pushback
      }

      this->last = newNode;

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
      
      ChainNode<T>* result;
      for (int i = 0; i <= index; i++)
      {
        result = first->link;
      }

      return *result;
    }
};