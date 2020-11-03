#include <iostream>
#include <utility>

enum class State
{
  START,
  FIRST,
  SECOND,
  END
};

class Object
{
public:
  Object(int first, int second): first_(first), second_(second) {}
  Object(): first_(0), second_(0) {}

  int first_;
  int second_;
};

template <State state>
class ObjectBuilder: public Object
{
public:
  ObjectBuilder<State::FIRST> add_first(int first) &&
    {
      static_assert(state == State::START,
		    "Need to be in START state");
      first_ = first;
      return {std::move(*this)};
    }

  ObjectBuilder<State::SECOND> add_second(int second) &&
    {
      static_assert(state == State::FIRST,
		    "Need to be in FIRST state");
      second_ = second;
      return {std::move(*this)};
    }
  ObjectBuilder<State::END> end() &&
    {
      static_assert(state == State::SECOND,
		    "Need to be in SECOND state");
      return {std::move(*this)};
    }

  ObjectBuilder()
    {
      static_assert(state == State::START,
		    "Need to be in START state");
    }

  template<State old_state>
  ObjectBuilder(ObjectBuilder<old_state>&& obj)
    {
    //Object(obj.first_, obj.second_) {}
    first_ = obj.first_;
    second_ = obj.second_;
    }
};

ObjectBuilder<State::START> getObjectBuilder()
{
  return ObjectBuilder<State::START>();
}

int main()
{
  int i = 20;
  int j = 10;
  auto obj = getObjectBuilder()
    .add_first(i)
    .add_second(j)
    .end();

  std::cout << obj.first_ << std::endl;
  std::cout << obj.second_ << std::endl;
}
