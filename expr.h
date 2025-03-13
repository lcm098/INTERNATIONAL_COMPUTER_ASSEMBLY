// expr.h
#ifndef EXPR_H
#define EXPR_H

#include "lexer.h"

// Forward declaration of Visitor template
template <typename R>
class Visitor;

class Expr {
public:
    class Binary;
    class Logical;
    class Unary;
    class Literal;
    class INT;
    class FLOAT;
    class BOOL;
    class NIL;
    class CHAR;
    class Grouping;
    class EmptyBlock;
};

#endif // EXPR_H