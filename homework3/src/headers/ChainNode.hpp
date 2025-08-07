template <class T>
class Chain;

template <class T>
class ChainNode
{
  friend class Chain<T>;

  private:
    ChainNode<T> *plink = nullptr; //- Pointer of next node

  public:
    T data;
    ChainNode(const T& dta)
    {
      this->data = dta;
    }
    ChainNode(const T& dta, ChainNode<T> *link)
    {
      this->data = dta;
      this->plink = link;
    }
};