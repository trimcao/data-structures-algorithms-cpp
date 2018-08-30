/** 
 * List class by Mark A. Weiss.
 * with comments by me, Tri M. Cao.
 */

template <typename Object>

class List
{
  private:
    // Node struct represents each element in the list.
    // We can see the constructor of Node using initializer list.
    // Notice that we have two versions of constructor, one for lvalue, and one
    // for rvalue. As usual, we use std::move() to move the rvalue instead of 
    // making a copy of that data.
    struct Node
    {
      Object data;
      Node *prev;
      Node *next;
      
      Node(const Object &d = Object{ }, Node *p = nullptr, Node *n = nullptr)
        : data{d}, prev{p}, next{n} 
        {}
      
      Node(Object &&d, Node *p = nullptr, Node *n = nullptr)
        : data{std::move(d)}, prev{p}, next{n}
        {}
    };
  
  public:
    class const_iterator
    {

    };

    class iterator : public const_iterator
    {

    };

  public:
    // Big-Five
    // Constructor
    List()
    {

    }
    List(const List & rhs)
    {

    }
    ~List()
    {

    }
    List & operator= (const List & rhs)
    {

    }
    List(List && rhs)
    {

    }
    List & operator= (List && rhs)
    {

    }

    // get the iterator for the first or last element in the list
    // explain: { head->next } means we construct an iterator object and return it.
    iterator begin()
    { return { head->next }; }
    const_iterator begin() const
    { return { head->next }; }
    iterator end()
    { return { tail }; }
    const_iterator end() const 
    { return { tall }; }

    int size() const 
    { return theSize; }


  // variables
  private:
    int theSize;
    Node *head;
    Node *tail;

    void init()
    {

    }




};