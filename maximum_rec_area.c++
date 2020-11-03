#include <iostream>
#include <vector>

int max_hist_area(const std::vector<int>& hist)
{
  std::vector<int> stack;
  int current_max = 0;

  for (size_t idx = 0; idx < hist.size(); idx++)
    {
      if (stack.empty())
	{
	  stack.push_back(idx);
	  current_max = hist[idx];
	  continue;
	}

      auto top = stack.back();
      if (hist[top] <= hist[idx])
	stack.push_back(idx);
      else
	{
	  while (hist[stack.back()] > hist[idx])
	    {
	      auto top = stack.back();
	      stack.pop_back();
	      if (stack.empty())
		{
		  int area = idx * hist[top];
		  current_max = current_max > area? current_max:area;
		  break;
		}
	      else
		{
		  int left_idx = stack.back();
		  int area = (idx - left_idx - 1)   * hist[top];
		  current_max = current_max > area? current_max:area;
		}
	    }
	  stack.push_back(idx);
	}
    }

  int right_idx = stack.back();
  while (stack.size())
    {
      auto top = stack.back();
      stack.pop_back();
      if (stack.empty())
	{
	  int area = (right_idx + 1) * hist[top];
	  current_max = current_max > area? current_max:area;
	  break;
	}
      else
	{
	  int left_idx = stack.back();
	  int area = (right_idx - left_idx) * hist[top];
	  current_max = current_max > area? current_max:area;
	}
    }
  return current_max;
}

int main(int argc, char *argv[])
{
  //std::vector<int> hist = {6, 2, 5, 4, 5, 1, 6};
  std::vector<int> hist = {2, 3, 4, 5};
  int max_area = max_hist_area(hist);
  std::cout << max_area << std::endl;

  return 0;
}
