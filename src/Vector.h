/** 
 * Vector class by Mark A. Weiss.
 * with comments by me, Tri M. Cao.
 */

#include <algorithm>

template <typename Object>
class Vector
{
  public: 
    // the code below is initializer list
    // we initialize the variables theSize and theCapacity
    // note that the variable *objects is a reference
    // for some reason, we initialize objects inside the brackets of 
    // Vector constructor.
    explicit Vector( int initSize = 0 ) : theSize{ initSize },
      theCapacity{ initSize + SPARE_CAPACITY }
    { objects = new Object[ theCapacity ]; }

    // Q: can we access rhs.theCapacity?
    // A: Probably yes, since this is the definition of the class,
    // so the code inside this definition can use these variables.
    Vector( const Vector &rhs ) : theSize(rhs.size()), 
      theCapacity{ rhs.theCapacity }, objects { nullptr }
    {
      objects = new Object[ theCapacity ];
      for (int k = 0; k < theSize; ++k) {
        objects[k] = rhs.objects[k];
      }
    }  

    // The operator= method below does copy from another vector
    // rhs here is a lvalue reference, and it's a const, that means
    // we just copy and don't modify it.
    Vector & operator= ( const Vector & rhs)
    {
      Vector copy = rhs;
      std::swap( *this, copy);
      return *this;
    }

    // Destructor
    ~Vector( )
    {
      delete [] objects;
    }

    // This is a constructor, works when rhs is a rvalue.
    // We destroy rhs after we move it to be the new vector.
    Vector( Vector && rhs) : theSize{ rhs.theSize }, 
      theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
      rhs.objects = nullptr;
      rhs.theSize = 0;
      rhs.theCapacity = 0;
    }

    // Operator= for rvalue reference. 
    // We want to do a move operation here. We swap the variables. 
    Vector & operator= ( Vector && rhs)
    {
      std::swap(theSize, rhs.theSize);
      std::swap(theCapacity, rhs.theCapacity);
      std::swap(objects, rhs.objects);
      return *this; // 'this' is a pointer, '*this' is an object.
    }

  void resize( int newSize ) 
  {
    if( newSize > theCapacity )
      reserve( newSize * 2 );
    theSize = newSize;
  }

  void reserve( int newCapacity )
  {
    if( newCapacity < theSize )
      return;
    
    Object *newArray = new Object[ newCapacity ];
    for (int k = 0; k < theSize; ++k)
      newArray[ k ] = std::move( objects[k] );
    
    theCapacity = newCapacity;
    std::swap(objects, newArray);
    delete [] newArray;
  }

  Object & operator[]( int index ) 
  { return objects[ index ]; }
  const Object & operator[]( int index ) const
  { return objects[ index ]; }

  bool empty() const
  { return size() == 0;}
  int size() const
  { return theSize; }
  int capacity() const
  { return theCapacity; }

  void push_back ( const Object & x )
  {
    if (theSize == theCapacity)
      reserve(theCapacity * 2 + 1);
    objects[ theSize++ ] = x;
  }

  void push_back ( const Object && x )
  {
    if (theSize == theCapacity)
      reserve(theCapacity * 2 + 1);
    objects[ theSize++ ] = std::move(x);
  }

  void pop_back () 
  {
    --theSize;
  }

  const Object & back () const 
  {
    return objects[theSize - 1];
  }

  // define 'iterator' type as a pointer of Object.
  // note that for a pointer in the array, when we increment it,
  // using ++, it will point to the next object.
  typedef Object * iterator;
  typedef const Object * const_iterator;

  iterator begin()
  { return &objects[0]; }
  const_iterator begin()
  { return &objects[0]; }
  iterator end()
  { return &objects[1]; }
  const_iterator end()
  { return &objects[1]; }

  static const int SPARE_CAPACITY = 16;

  private:
    int theSize;
    int theCapacity;
    Object * objects;
};