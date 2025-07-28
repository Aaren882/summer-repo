template <class T>
class Chain;

template <class T>
class ChainNode
{
  friend class Chain<T>;

  private:
    ChainNode<T> *link;

  public:
    T data;
    ChainNode(const T &data, ChainNode<T> *link = nullptr)
    {
      this->data = data;
      this->link = link;
    }
};