#include <iostream>

struct struct_tag_non_ptr {};
struct struct_tag_ptr {};

// template and template specialization
template< typename T >
struct is_pointer
{
    enum {value = false};
    typedef struct_tag_non_ptr type_category;
};

template< typename T >
struct is_pointer< T* >
{
    enum {value = true};
    typedef struct_tag_ptr type_category;
};

template< typename T, bool choice >
struct do_something
{
  static void print () { std::cout << "false" << std::endl;}
};

// here, don't define the second non-type arguments
template< typename T >
struct do_something< T, true>
{
  static void print () { std::cout << "true" << std::endl;}
};


//function overload implemenation
template < typename T>
void print (struct_tag_non_ptr)
{
  std::cout << "not pointer" << std::endl;
}

//function overload implemenation
template < typename T>
void print (struct_tag_ptr)
{
  std::cout << "ptr" << std::endl;
}

int main ()
{
  typedef int * int_ptr;
  std::cout << is_pointer<int_ptr>::value << std::endl;
  std::cout << is_pointer<int>::value << std::endl;;


  do_something<int_ptr, is_pointer<int_ptr>::value>::print ();
  do_something<int, is_pointer<int>::value>::print ();

  print <int_ptr> (is_pointer<int_ptr>::type_category ());
  print <int> (is_pointer<int>::type_category ());
}
