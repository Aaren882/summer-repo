template <class T>
class Chain;

template <class T>
class ChainNode
{
  friend class Chain<T>;

  private:
    ChainNode<T> *plink; //- Pointer of next node

  public:
    T data;
    ChainNode(const T data)
    {
      this->data = data;
    }
    ChainNode(const T data, ChainNode<T> *plink)
    {
      this->data = data;
      this->plink = plink;
    }
};