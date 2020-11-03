class MyClass
{
public:
  MyClass (const MyClass&& other)
    {
      data1_ = std::move(other.data1_);
      data2_ = std::move(other.data2_);
      data3_ = other.data3_;
      data4_ = other.data4_;
    }

  MyClass& operator=(const MyClass&& other)
    {

    }

  MyClass () = delete;
  MyClass (const MyClass& other) = delete;
  MyClass& operator=(const MyClass& other) = delete;

private:

  std::vector<int> data1_;
  std::vector<std::pair<int, int>> data2_;
  int data3_;
  int data4_;
}

int main ()
{
  MyClass obj1;
  MyClass obj2 = std::move (obj1);
}
