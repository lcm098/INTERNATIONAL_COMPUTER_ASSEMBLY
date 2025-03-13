// parser.h
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "lexer.h"
#include "expr.h"


// Expr nested class definitions
class Expr::Binary {
public:
    Expr* left;
    Token operator_;
    Expr* right;

    Binary(Expr* left, Token operator_, Expr* right);
    std::string repr();
    template <typename R> R accept(Visitor<R>& visitor);
};

// ... (other nested classes)

// ParseError class
class ParseError : public std::exception {
public:
    std::string message;

    ParseError(std::string message);
    const char* what() const noexcept override;
};

// Parser class
class Parser {
public:
    std::vector<Token> tokens;
    int current = 0;

    Parser(std::vector<Token> tokens);
    std::vector<Expr*> parse();
    Expr* declaration();
    Expr* expression();
    Expr* or_expr();
    Expr* and_expr();
    Expr* equality();
    Expr* comparison();
    Expr* term();
    Expr* factor();
    Expr* unary();
    Expr* primary();
    Expr* handle_unknown_block_statement();
    std::vector<Expr*> block();
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType token_type);
    Token advance(int distance = 1);
    void past(int distance = 1);
    void future(int distance = 1);
    bool is_at_end();
    Token peek();
    Token previous(int distance = 1);
    Token consume(TokenType token_type, std::string message);
    void error(Token token, std::string message, int line);
};

// Visitor template (assuming it exists)
template <typename R>
class Visitor {
public:
    virtual R visit_binary_expr(Expr::Binary& expr) = 0;
    virtual R visit_logical_expr(Expr::Logical& expr) = 0;
    virtual R visit_unary_expr(Expr::Unary& expr) = 0;
    virtual R visit_literal_expr(Expr::Literal& expr) = 0;
    virtual R visit_int_expr(Expr::INT& expr) = 0;
    virtual R visit_float_expr(Expr::FLOAT& expr) = 0;
    virtual R visit_bool_expr(Expr::BOOL& expr) = 0;
    virtual R visit_nil_expr(Expr::NIL& expr) = 0;
    virtual R visit_char_expr(Expr::CHAR& expr) = 0;
    virtual R visit_grouping_expr(Expr::Grouping& expr) = 0;
    virtual R visit_unknown_block(Expr::EmptyBlock& expr) = 0;
};

#endif // PARSER_H