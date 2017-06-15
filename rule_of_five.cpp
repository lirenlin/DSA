#include <cstring>
#include <iostream>

class Foo
{
public:
  /* default constructor  */
  Foo (): data (new char[14])
  {
    std::cout << "default constructor" << std::endl;
    std::strcpy (data, "hello world!");
  }

  Foo (const char *ptr): data (new char[std::strlen (ptr) + 1])
  {
    std::cout << "constructor with argument" << std::endl;
    std::strcpy (data, ptr);
  }

  /* copy constructor  */
  Foo (const Foo &other): data (new char[std::strlen (other.data) + 1])
  {
    std::cout << "copy constructor" << std::endl;
    std::strcpy (data, other.data);
  }

  /* move constructor */
  Foo (Foo &&other) noexcept: data (other.data)
  {
    std::cout << "move constructor" << std::endl;
    other.data = nullptr;
  }

  /* destructor */
  ~Foo () noexcept
  {
    std::cout << "Destructor called" << std::endl;
    delete [] data;
  }

  /* copy assignment operator */
  Foo &operator= (const Foo& other)
    {
      std::cout << "copy assignment constructor" << std::endl;
      Foo tmp (other); // reuse copy constructor
      *this = std::move(tmp); // move assignment constructor
      return *this;
    }

  /* move assignment operator */
  Foo &operator= (Foo&& other)
    {
      std::cout << "move assignment constructor" << std::endl;
      delete [] data;
      data = other.data;
      other.data = nullptr;
      return *this;
    }

private:
    friend std::ostream& operator<< (std::ostream& os, const Foo& foo)
    {
      if (foo.data != nullptr)
	os << foo.data;
      else
	os << "NULL";
      return os;
    }

    char *data;
};

int main ()
{
  Foo foo;
  std::cout << foo << std::endl;
  std::cout << "############" << std::endl;
  const Foo test1 ("const new instance copyed");
  // This is const object, move assignment operator doesn't apply here.
  foo = std::move (test1);
  std::cout << foo << std::endl;
  std::cout << test1 << std::endl;


  std::cout << "############" << std::endl;
  // this is a rvalue, so move semantics
  foo = Foo ("new instance moved");
  std::cout << foo << std::endl;

  std::cout << "############" << std::endl;
  Foo test2 ("new instance");
  // std::move could create a rvalue.
  foo = std::move (test2);
  std::cout << foo << std::endl;
  std::cout << test2 << std::endl;

  return 0;
}
