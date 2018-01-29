#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isOp (char c)
{
  return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool GtPrecedence (char op1, char op2)
{
  if (!isOp (op1))
    cout << "Not an operator: " << op1 << endl;
  if (!isOp (op2))
    cout << "Not an operator: " << op2 << endl;

  if (op1 == op2)
    return false;

  if (op1 == '+' || op1 == '-')
    return false;
  else
    return true;
}

string infixToPrefix (string exp)
{
  string output;
  stack<char> stack;
  for (char &c : exp)
    {
      if (c == '(')
	stack.push (c);
      else if (c == ')')
	{
	  while (!stack.empty ())
	    {
	      char top = stack.top ();
	      stack.pop ();
	      if (top == '(')
		break;
	      output.push_back (top);
	    }
	}
      else if (c <='z' && c >= 'a')
	output.push_back (c);
      else if (isOp (c))
	{
	  if (stack.empty ())
	    {
	      stack.push (c);
	      continue;
	    }

	  char op = stack.top ();
	  if (!isOp (op))
	    stack.push (c);
	  else if (GtPrecedence (c, op))
	      stack.push (c);
	  else
	    {
	      stack.pop ();
	      stack.push (c);
	      output.push_back (op);
	    }
	}
      else
	cout << "unknown charcter: " << c << " in expression: "
	  << exp << endl;
    }

  while (!stack.empty ())
    {
      output.push_back (stack.top ());
      stack.pop ();
    }

  return output;
}

string infixToPostfix (string exp)
{

}

int main ()
{
  string exp = "a*(b+c/d)-e";
  cout << exp << endl;
  cout << infixToPrefix (exp) << endl;
}
