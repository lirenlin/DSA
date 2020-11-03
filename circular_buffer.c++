#include <iostream>
#include <functional>
#include <string>

template <size_t N, typename T, typename CompLT = std::less<T>>
class CircularBufferSortedAccess
{
public:
  class Iterator
  {
  friend CircularBufferSortedAccess;
  protected:
    Iterator(const CircularBufferSortedAccess<N, T, CompLT>& buffer, size_t index):
      buffer(buffer), current_index(index) {}
  public:
    const Iterator& operator++()
      {
        current_index += 1;
        return *this;
      }
    Iterator operator++(int)
      {
        Iterator iterator = *this;
        ++*this;

        return iterator;
      }

    bool operator != (const Iterator& other)
      {
        return other.current_index != current_index;
      }

    const T& operator*()
      {
        auto index = current_index;
        if (current_index == buffer.size())
	 index -= 1;
        size_t data_index = buffer.index_array[index];
        return buffer.data_array[data_index];
      }

  private:
    size_t current_index;
    const CircularBufferSortedAccess<N, T, CompLT>& buffer;
    };


  friend Iterator;
  CircularBufferSortedAccess(): size_(0), head_index(0), tail_index(0) {}

  bool insertItem(const T& item);
  const Iterator cbegin() const;
  const Iterator cend() const;
  T removeTail();

  size_t size() const {return size_;}
  void dumpData() const;
  void dumpDataSorted() const;

private:
  size_t nextIndex(size_t idx) const { return (idx + 1) % N; }

  size_t size_;
  size_t head_index;
  size_t tail_index;

  T data_array[N];
  size_t index_array[N];
};

template <size_t N, typename T, typename CompLT>
bool CircularBufferSortedAccess<N, T, CompLT>::insertItem(const T& item)
{
  if (size_ == N) {
    removeTail();
  }

  size_t curr_index_idx = size_;

  data_array[head_index] = item;
  index_array[size_] = head_index;

  head_index = nextIndex(head_index);
  size_ += 1;

  if (size_ == 0 || size_ == 1)
    return true;

  while(curr_index_idx != 0) {
      size_t curr_data_index = index_array[curr_index_idx];
      size_t prev_data_index = index_array[curr_index_idx - 1];

      if (CompLT()(data_array[curr_data_index], data_array[prev_data_index])) {
	index_array[curr_index_idx] = prev_data_index;
	index_array[curr_index_idx - 1] = curr_data_index;
	curr_index_idx -= 1;
      } else {
	  break;
      }
  }
  return true;
}

template <size_t N, typename T, typename CompLT>
T CircularBufferSortedAccess<N, T, CompLT>::removeTail()
{
  if (size_ == 0)
    return T();


  size_t tail_index_idx = 0;
  for (; tail_index_idx < size_; ++tail_index_idx)
    {
      if (tail_index == index_array[tail_index_idx])
	break;
    }
  for (auto i = tail_index_idx; i < size_ - 1; ++i)
    {
      index_array[i] = index_array[i+1];
    }

  auto val = data_array[tail_index];
  tail_index = nextIndex(tail_index);
  size_--;

  return val;
}

template <size_t N, typename T, typename CompLT>
const typename CircularBufferSortedAccess<N, T, CompLT>::Iterator CircularBufferSortedAccess<N, T, CompLT>::cbegin() const
{
  return Iterator(*this, 0);
}

template <size_t N, typename T, typename CompLT>
const typename CircularBufferSortedAccess<N, T, CompLT>::Iterator CircularBufferSortedAccess<N, T, CompLT>::cend() const
{
  return Iterator(*this, size_);
}

template <size_t N, typename T, typename CompLT>
void CircularBufferSortedAccess<N, T, CompLT>::dumpDataSorted() const
{
  for (size_t i = 0; i < size_; ++i)
    {
      auto data_index = index_array[i];
      std::cout << data_array[data_index] << " ";
    }
  std::cout << std::endl;
}

template <size_t N, typename T, typename CompLT>
void CircularBufferSortedAccess<N, T, CompLT>::dumpData() const
{
  auto size = size_;
  if (size == 0)
    return;

  bool warp = (size > 0 && head_index <= tail_index);
  for (size_t i = 0; i < N; ++i)
    {
      std::cout << i << ": ";

      bool empty_slot = false;
      if (warp && (i < tail_index && i >= head_index))
	empty_slot = true;
      else if (!warp && (i < tail_index || i >= head_index))
	empty_slot = true;

      if (empty_slot)
	std::cout << "(no data) ";
      else
	std::cout << data_array[i] << " ";
    }
  std::cout << std::endl;
}

struct Item
{
  Item(int key = -1, std::string str = "error"): key(key), str(str) {}

  std::string str;
  int key;

  friend std::ostream &operator << (std::ostream &os, const Item&);

};

std::ostream &operator << (std::ostream &os, const Item &item)
{
  os << "(" << item.key << ", " << item.str << ")";
  return os;
}

struct ItemCompLT
{
  bool operator()(const Item& a, const Item&b)
    {
      return a.key < b.key;
    }
};


int main() {
    CircularBufferSortedAccess<6, Item, ItemCompLT> buffer;
    buffer.insertItem(Item(11, "lin"));
    buffer.insertItem(Item(10, "ren"));
    buffer.insertItem(Item(0, "li"));
    buffer.insertItem(Item(1, "Yan"));
    buffer.insertItem(Item(15, "chino"));
    buffer.insertItem(Item(3, "neko"));
    buffer.dumpData();
    buffer.dumpDataSorted();

    auto a = buffer.removeTail();
    std::cout << "remove " << a << std::endl;
    a = buffer.removeTail();
    std::cout << "remove " << a << std::endl;
    buffer.dumpData();
    buffer.dumpDataSorted();

    buffer.insertItem(Item(4, "4"));
    buffer.insertItem(Item(5, "5"));
    buffer.insertItem(Item(2, "2"));
    buffer.insertItem(Item(18, "18"));
    buffer.dumpData();
    buffer.dumpDataSorted();

    /*
    for (auto ite = buffer.cbegin(); ite != buffer.cend(); ++ite)
      {
	std::cout << *ite << " ";
      }
    std::cout << std::endl;
    */

    return 0;
}
