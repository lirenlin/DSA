#include <vector>
#include <iostream>
#include <cmath>

struct Point{
    Point(float x, float y, float cost):x(x), y(y), cost(cost) {}

    float x = 0;
    float y = 0;

    float cost = 100;
};

template <typename T>
float distance (const T& p1, const T& p2)
{
  return 0;
}

template <typename T>
float distance (const Point& point1, const Point& point2)
{
  float delta_x = point1.x - point2.x;
  float delta_y = point1.y - point2.y;

  float dist = std::sqrt(delta_x * delta_x + delta_y * delta_y);
  return dist;
}

template <typename T, int K, typename Enable = void>
class TopK;

template <typename T, int K>
class TopK <T, K, typename std::enable_if<K < 10>::type>
{
public:
  void addItem(const T& item);
  std::vector<T> getData() const {
      return data_;
    }

private:
    std::vector<T> data_;
    float min_distance_ = 1;
};

template <typename T, int K>
void TopK <T, K, typename std::enable_if<K < 10>::type>::addItem(const T& item)
{
#ifdef DEBUG
  std::cout << "insert item: (" << item.x << "," << item.y << "): " << item.cost << std::endl;
  std::cout << "topk Before:" << std::endl;
  for (const auto& i: data_)
    std::cout << "(" << i.x << "," << i.y << "): " << i.cost << std::endl;
#endif

  bool processed = false;

  for (auto i = data_.begin(); i != data_.end(); ++i) {
      T& other = *i;
      float dist = distance<T>(other, item);

      // close to an item which has lower cost, ignore
      if (dist < min_distance_ && item.cost > other.cost) {
	  processed = true;
	  break;
      }
      // close to an item which has higher cost, replace it
      else if (dist < min_distance_ && item.cost < other.cost) {
	  *i = item;
	  processed = true;
	  break;
      }
      // lower cost and far enough to current item.
      // To reach here, item.cost must larger than previous item cost, and far
      // away enought to it. Otherwise, it will be ignored by the first if
      // case.
      else if (dist > min_distance_ && item.cost < other.cost) {
	  if (K == data_.size())
	    data_.pop_back();

	  data_.insert(i, item);
	  processed = true;
	  break;
      }
  }

  if (!processed && data_.size() < K)
    data_.push_back(item);

#ifdef DEBUG
  std::cout << "topk after:" << std::endl;
  for (const auto& i: data_)
    std::cout << "(" << i.x << "," << i.y << "): " << i.cost << std::endl;
#endif
}

int main ()
{
  TopK<Point, 3> vec;
  vec.addItem (Point(1, 5, 2));
  vec.addItem (Point(1, 2, 1));
  vec.addItem (Point(1, 1, 3));
  vec.addItem (Point(1, 3.1, 0.1));
  vec.addItem (Point(1, 0.1, 0.9));
  vec.addItem (Point(1, 7, 1));

  const auto& data = vec.getData();
  std::cout << "result" << std::endl;
  for (const auto& i: data)
    std::cout << "(" << i.x << "," << i.y << "): " << i.cost << std::endl;

  return 0;

}
