//@todo
//1, add operator global object, so that it could be shared.
//2, clean new keyword, there are memory leaks
//3, orgnize the class better, don't put specific information inside token
//
//
//map, vector, operator overload, string
#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <vector>

enum class Associativity {NONE, LTR, RTL};
using OpMap = std::map<std::string, std::pair<int, Associativity>>;

#define OP_ENTRY(STR, PRECEDENCE, ASSOCIATIVITY) \
{STR, {PRECEDENCE, Associativity::ASSOCIATIVITY}}

OpMap opMap = {
    OP_ENTRY ("*", 3, LTR),
    OP_ENTRY ("/", 3, LTR),
    OP_ENTRY ("%", 3, LTR),
    OP_ENTRY ("+", 4, LTR),
    OP_ENTRY ("-", 4, LTR),
    OP_ENTRY ("<<", 5, LTR),
    OP_ENTRY (">>", 5, LTR),
    OP_ENTRY ("&", 8, LTR),
    OP_ENTRY ("^", 8, LTR),
    OP_ENTRY ("|", 8, LTR)};

class Token
{
public:
  std::string str;
  unsigned precedence;
  Associativity associativity;

public:
  Token (std::string str): str (str) {}
  Token () {};
  virtual bool isNum () {return false;}
  virtual bool isOperator () {return false;}
  virtual bool isFunc () {return false;}
  virtual bool isLeftBracket () {return false;}
  virtual bool isRightBracket () {return false;}
  virtual int value () { return 0;}
};

class Operator: public Token
{
public:
  Operator (std::string str): Token (str) {
      OpMap::iterator it;
      it = opMap.find (str);
      if (it != opMap.end ())
	{
	  precedence = it->second.first;
	  associativity = it->second.second;
	}
      else
	assert ("not a valid operator");
  }

  bool isOperator () {return true;}
  bool greaterPrecedence(Operator &op)
    {
      assert (isOperator () && op.isOperator() && "A,B must all be operator");
      return (precedence > op.precedence);
    }

  int operator() (int a, int b) {
      if (str == "*") return a*b;
      if (str == "/") return a/b;
      if (str == "%") return a%b;
      if (str == "+") return a+b;
      if (str == "-") return a-b;
      if (str == "<<") return a<<b;
      if (str == ">>") return a>>b;
      if (str == "&") return a&b;
      if (str == "^") return a^b;
      if (str == "|") return a|b;
      assert ("unsupported op");
  }
};

class Number: public Token
{
private:
  int val;
public:
  Number (int value):  Token (std::to_string (value)), val (value) {}
  Number (std::string str): Token (str) {
      try {
	  val = std::stoi (str);
      }
      catch (std::out_of_range &oor) {
	assert ("value out of range");
      }
      catch (std::invalid_argument &ia) {
	assert ("invalid argument");
      }
  }

  bool isNum () {return true;}
  int value () {return val;}
};

class Bracket: public Token
{
private:
  bool isLeft;
public:
  Bracket (std::string str): Token (str) { isLeft = (str == "("); }
  bool isLeftBracket () {return isLeft;}
  bool isRightBracket () {return !isLeft;}
};

bool isOperator (std::string str, int &offset)
{
  if (std::isdigit (str[0]))
    return false;

  OpMap::iterator it;
  it = opMap.find (str.substr (0, 1));
  if (it != opMap.end ())
    {
      offset = 1;
      return true;
    }

  it = opMap.find (str.substr (0, 2));
  if (it != opMap.end ())
    {
      offset = 2;
      return true;
    }

  return false;
}

// helper function to debug
void dumpRPN (std::vector<Token *> &vector)
{
  for (auto I : vector)
    std::cout << I->str;
  std::cout << std::endl;
}

int parseString (std::string expression)
{
  std::vector<Token *> output;
  std::vector<Token *> stack;
  unsigned idx = 0;
  unsigned idx_end = expression.size ();

  //Shunting-yard algorithShunting-yard algorithmm
  while (idx != idx_end)
    {
      // skip white space
      while (expression[idx] == ' ')
	++idx;

      Token *token;
      if (expression[idx] == '(')
	{
	  token = new Bracket (expression.substr (idx, 1));
	  ++idx;
	  stack.push_back(token);
	  continue;
	}
      else if (expression[idx] == ')')
	{
	  ++idx;
	  Token *top = stack.back ();
	  while (top != nullptr && !top->isLeftBracket ())
	    {
	      output.push_back (top);
	      stack.pop_back ();
	      top = stack.back ();
	    }
	  if (top != nullptr && top->isLeftBracket ())
	    stack.pop_back ();

	  continue;
	}

      if (std::isdigit (expression[idx]))
	{
	  unsigned start = idx;
	  std::string num;
	  ++idx;
	  while (std::isdigit (expression[idx]))
	    {
	      ++idx;
	    }

	  token = new Number (expression.substr (start, idx-start));
	  output.push_back (token);
	  continue;
	}

      int offset = 0;
      if (isOperator (expression.substr (idx), offset))
	{
	  Operator *op = new Operator (expression.substr (idx, offset));
	  idx += offset;
	  if (stack.empty ())
	    {
	      stack.push_back (op);
	      continue;
	    }

	  Token *top = stack.back ();
	  if (top->isOperator ())
	    {
	      Operator *tmp = dynamic_cast <Operator *> (top);
	      if (tmp->precedence > op->precedence)
		{
		  stack.push_back (op);
		  continue;
		}
	    }
	    {
	      while (!stack.empty ())
		{
		  Token *top = stack.back ();
		  if (((top->precedence < op->precedence)
		       || ((top->precedence == op->precedence)
			   && top->associativity == Associativity::LTR))
		      && !(top->isLeftBracket ()))
		    {
		      output.push_back (stack.back ());
		      stack.pop_back ();
		    }
		  else
		    break;
		}
	      stack.push_back (op);
	    }
	}
      else
	assert ("invalid expression");
    }

  while (!stack.empty ())
    {
      output.push_back (stack.back ());
      stack.pop_back ();
    }

  //using stack to evaluate RPN
    {
      std::vector<Token *> stack;
      std::vector<Token *>::iterator it = output.begin ();
      for (it; it != output.end (); ++it)
	{
	  if ((*it)->isNum ())
	    stack.push_back (*it);
	  else if ((*it)->isOperator ())
	    {
	      Operator *op = dynamic_cast <Operator *> (*it);
	      if (stack.size () < 2)
		{
		  std::cout << "invalid expression" << std::endl;
		  return 0;
		}
	      Token *op1 = stack.back ();
	      stack.pop_back ();
	      Token *op2 = stack.back ();
	      stack.pop_back ();
	      assert (op1->isNum () && op2->isNum ());
	      int value = (*op) (op2->value (), op1->value ());
	      Number *num = new Number (value);
	      stack.push_back (num);
	    }
	}
      return (stack.back ())->value ();
    }
}

int main ()
{
  //std::string expression = "1++";
  std::string expression;
  std::cout << "enter an expression: ";
  std::cin >> expression;

  int result = parseString (expression);
  std::cout << result << std::endl;
}
