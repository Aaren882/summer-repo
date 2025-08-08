template <class T>
class Chain;

template <class T>
class ChainNode
{
  friend class Chain<T>;
  friend class Available;
  friend class Polynomial;

  private:
    T data;
    ChainNode<T> *plink = nullptr; //- Pointer of next node

  public:
    ChainNode(){}
    ChainNode(const T& dta)
    {
      this->data = dta;
    }
    ChainNode(const T& dta, ChainNode<T> *link)
    {
      this->data = dta;
      this->plink = link;
    }
    T& getData() {
      return this->data;
    }
};