#include <vector>
#include <string>
#include <sstream>
#include <iostream>

int main()
{
  std::string str = "10: 24.1,3,4,5,6";
  std::vector<float> vect;

  std::stringstream ss(str);

  float i;

  while (ss >> i)
    {
      vect.push_back(i);

      if (!isdigit (ss.peek()))
	ss.ignore();
    }

  for (i=0; i< vect.size(); i++)
    std::cout << vect[i]<<std::endl;
}
