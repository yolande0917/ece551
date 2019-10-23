#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 protected:
  long number;

 public:
  virtual ~NumExpression() {}
  explicit NumExpression(long num) : number(num) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << number;
    std::string s = ss.str();
    return s;
  }
};

class OpExpression : public Expression {
 protected:
  Expression * left;
  Expression * right;
  char op;

 public:
  virtual ~OpExpression() {
    delete left;
    delete right;
  }
  OpExpression(Expression * lhs, Expression * rhs, char o) :
      left(lhs),
      right(rhs),
      op(o) {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << "(";
    ss << left->toString();
    ss << " " << op << " ";
    ss << right->toString();
    ss << ")";
    std::string s = ss.str();
    return s;
  }
};

class PlusExpression : public OpExpression {
 public:
  virtual ~PlusExpression() {}
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression(lhs, rhs, '+') {}
  // virtual std::string toString() const {}
};
