//map, vector, operator overload, string
//factory, singleton


#include <iostream>
#include <string>
#include <map>
#include <cassert>
#include <vector>
#include <algorithm>

enum class Associativity {NONE, LTR, RTL};
using OpMap = std::map<std::string, std::pair<int, Associativity>>;

enum class TokenKind {NUM, OP, LP, RP, INVALID};

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

class Context;
class Token
{
  friend class Context;
protected:
  Token (std::string str, TokenKind kind): str (str), tokenKind (kind) {}
  Token (std::string str): str (str), tokenKind (TokenKind::INVALID) {}
  Token () {tokenKind = TokenKind::INVALID;}

public:
  std::string str;
  TokenKind tokenKind;

public:
  virtual bool isNum () {return tokenKind == TokenKind::NUM;}
  virtual bool isOperator () {return tokenKind == TokenKind::OP;}
  virtual bool isLeftBracket () {return tokenKind == TokenKind::LP;}
  virtual bool isRightBracket () {return tokenKind == TokenKind::RP;}
};

class Operator: public Token
{
  friend class Context;
protected:
  Operator (std::string str): Token (str, TokenKind::OP) {
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

public:
  unsigned precedence;
  Associativity associativity;

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
  friend class Context;
private:
  int val;

protected:
  Number (int value): Token (std::to_string (value), TokenKind::NUM), val (value) {}
  Number (std::string str): Token (str, TokenKind::NUM) {
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

public:
  int value () {return val;}
};

class Bracket: public Token
{
  friend class Context;
protected:
  Bracket (std::string str): Token (str) {
     if (str == "(")
       tokenKind = TokenKind::LP;
     else if (str == ")")
       tokenKind = TokenKind::RP;
  }
};

class Context
{
private:
  std::vector<Token *> tokens;
  int size;

public:
  Token * getToken (std::string str, TokenKind kind) {
      std::vector<Token *>::iterator it = std::find_if (tokens.begin (),
							tokens.end (),
							[&](Token *token) { return token->tokenKind == kind && token->str == str;});
      if (it == tokens.end ())
	{
	  ++size;
	  Token *token;
	  if (kind == TokenKind::NUM)
	    token = new Number (str);
	  else if (kind == TokenKind::OP)
	    token = new Operator (str);
	  else if (kind == TokenKind::LP)
	    token = new Bracket (str);
	  else if (kind == TokenKind::RP)
	    token = new Bracket (str);
	  else
	    token = new Token (str, kind);

	  tokens.push_back (token);
	  return token;
	}
      else
	{
	  std::cout << str << " shared" << std::endl;
	  return *it;
	}
  }

  Number *getNumToken (int value)
    {
      std::string str = std::to_string (value);
      Token *token = getToken (str, TokenKind::NUM);
      return dynamic_cast<Number *>(token);
    }

  Number *getNumToken (std::string str)
    {
      Token *token = getToken (str, TokenKind::NUM);
      return dynamic_cast<Number *>(token);
    }

  Operator *getOpToken (std::string str)
    {
      Token *token = getToken (str, TokenKind::OP);
      return dynamic_cast<Operator *>(token);
    }

  Context (): size (0) {}
  ~Context () {
      for (auto *token : tokens)
	{
	  --size;
	  delete token;
	}
      assert (size == 0);
  }
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
  Context ctx;
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

      if (expression[idx] == '(')
	{
	  Token *token = ctx.getToken (expression.substr (idx, 1), TokenKind::LP);
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

	  Number *token = ctx.getNumToken (expression.substr (start, idx-start));
	  output.push_back (token);
	  continue;
	}

      int offset = 0;
      if (isOperator (expression.substr (idx), offset))
	{
	  Operator *op = ctx.getOpToken (expression.substr (idx, offset));
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
		  Operator *top = dynamic_cast<Operator *>(stack.back ());
		  if (top && ((top->precedence < op->precedence)
			      || ((top->precedence == op->precedence)
				  && top->associativity == Associativity::LTR)))
		    {
		      output.push_back (top);
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

  dumpRPN (output);

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

	      int num2 = dynamic_cast<Number *>(op2)->value ();
	      int num1 = dynamic_cast<Number *>(op1)->value ();
	      int value = (*op) (num2, num1);
	      Token *num = ctx.getNumToken (value);
	      stack.push_back (num);
	    }
	}
      Number *result = dynamic_cast <Number *>(stack.back ());
      return (result->value ());
    }
}

int main ()
{
  //std::string expression = "1+3*(4-2)";
  std::string expression;
  std::cout << "enter an expression: ";
  std::cin >> expression;

  int result = parseString (expression);
  std::cout << result << std::endl;
}
