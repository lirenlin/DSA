#include <algorithm>
#include <cmath>

void abssort (float *x, unsigned n) {
  std::sort (x, x+n,
             //lambda expression begins
             [](float a, float b) {
             return (std::abs (a) < std::abs (b));
             } // end of lambda expression
            );/
}

/*
https://msdn.microsoft.com/en-us/library/dd293608.aspx
[] () mutable throw () -> int
{

}

1, capture clause
2, parameter list
3, mutable specification
4, exception
5, trailing return type
6, lambda body

https://stackoverflow.com/questions/16921247/how-are-c11-lambdas-represented-and-passed
*/
