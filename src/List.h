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
      public:
        const_iterator() : current{nullptr}
          {}
        const Object & operator* {} const
          { return retrieve(); }
        const_iterator & operator++ ()
        { 
          current = current->next;
          return *this;
        }
        // operator++ (int) indicates the operation ++x
        // the operator++ () above indicates operation x++
        const_iterator & operator++ (int)
        {
          const_iterator old = *this;
          ++(*this);
          return old;
        }

        bool operator== (const const_iterator & rhs) const
          { return (current == rhs.current); }
        bool operator!= (const const_iterator & rhs) const 
          { return !(*this == rhs); }
        
      protected:
        Node *current;
        Object & retrieve() const
          { return current->data; }
        const_iterator(Node *p) : current{p}
          {}
        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
      public:
        iterator()
          {}
        
        // Explanation for two operator* methods below:
        // if we want a reference to a non-const object, the signature of 
        // the method operator* () has no const keyword in it. Therefore, 
        // despite using the retrieve() method from const_iterator class, 
        // it will return a mutable reference.
        // If we see the const_iterator::operator*() method, we will see 
        // the signature has a const keyword.
        // It's clear that iterator::operator*() is different from 
        // const_iterator::operator*() 
        Object & operator* ()
          { return const_iterator::retrieve(); }
        const Object & operator* const ()
          { return const_iterator::operator*(); }
        
        iterator & operator++ ()
        {
          this->current = this->current->next;
          return *this;
        }
        iterator & operator++ (int)
        {
          iterator old = *this;
          ++(*this);
          return old;
        }

      protected:
        iterator(Node *p) : const_iterator{p}
          {}
        friend class List<Object>;  
    };

  public:
    // Big-Five
    // Constructor
    List()
    {
      init();
    }
    List(const List & rhs)
    {
      init();
      for (auto & x : rhs)
        push_back(x);
    }
    ~List()
    {
      clear();
      delete head;
      delete tail;
    }
    List & operator= (const List & rhs)
    {
      List copy = *rhs;
      std::swap(*this, copy);
      return *this; 
    }
    // if rhs is a rvalue, we move it instead of creating a new List.
    List(List && rhs)
      : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
      rhs.theSize = 0;
      rhs.head = nullptr;
      rhs.tail = nullptr;
    }
    List & operator= (List && rhs)
    {
      // we do a bunch of swap because the variables of the current List are 
      // default values (usually nullptr), therefore after swapping the values 
      // from rhs, we don't even bother to delete rhs.
      std::swap(theSize, rhs.theSize);
      std::swap(head, rhs.head);
      std::swap(tail, rhs.tail);
      return *this;
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

    void clear()
    {
      while (!empty)
        pop_front();
    }

    // notice that below we seem to return the object itself instead of a reference
    // but since the return type is a reference, C++ will automatically return
    // a reference for us.
    Object & front()
    { return *begin(); } 
    const Object & front() const
    { return *begin(); }
    Object & back() 
    { return *--end(); }
    const Object & back() const 
    { return *--end(); }
    
    void push_front(const Object & x)
    { insert(begin(), x); }
    void push_front(Object && x)
    { insert(begin(), std::move(x)); }
    void push_back(const Object & x)
    { insert(end(), x); }
    void push_back(Object && x)
    { insert(end(), std::move(x)); }
    void pop_front()
    { erase(begin()); }
    void pop_back()
    { erase(--end()); }


    iterator insert(iterator itr, const Object & x)
    {
      Node *p = itr.current;
      theSize++;
      // my own implementation
      // Node *newNode = Node{x, p->prev, p};
      // p->prev->next = newNode;
      // p->prev = newNode;
      // return newNode;
      return { p->prev = p->prev->next = new Node{x, p->prev, p} };
    }
    iterator insert(iterator itr, Object && x)
    {
      Node *p = itr.current;
      theSize++;
      // Node *newNode = Node{std::move(x), p->prev, p};
      return { p->prev = p->prev->next = new Node{std::move(x), p->prev, p} };
    }

    iterator erase(iterator itr)
    {
      Node *p = itr.current;
      theSize--;
      iterator retVal{p->next};
      p->prev->next = p->next;
      p->next->prev = p->prev; 
      delete p;
      return retVal;
    }
    iterator erase(iterator from, iterator to)
    {
      for (iterator itr = from; itr != to; ) 
        //note that itr will automatically increment due to the erase(itr) method
        itr = erase(itr); 
      return to;
    }

  // variables
  private:
    int theSize;
    Node *head;
    Node *tail;

    void init()
    {
      theSize = 0;
      head = new Node;
      tail = new Node;
      head->next = tail;
      tail->prev = head;
    }

};