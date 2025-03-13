#include "parser.h"
#include "expr.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


// Expr class and its nested classes
class Expr {
public:
    class Binary {
    public:
        Expr* left;
        Token operator_;
        Expr* right;

        Binary(Expr* left, Token operator_, Expr* right)
            : left(left), operator_(operator_), right(right) {}

        std::string repr() {
            return "Binary(left=" + left->repr() + ", operator=" + operator_.lexeme + ", right=" + right->repr() + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_binary_expr(*this);
        }
    };

    class Logical {
    public:
        Expr* left;
        Token operator_;
        Expr* right;

        Logical(Expr* left, Token operator_, Expr* right)
            : left(left), operator_(operator_), right(right) {}

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_logical_expr(*this);
        }
    };

    class Unary {
    public:
        Token operator_;
        Expr* right;

        Unary(Token operator_, Expr* right)
            : operator_(operator_), right(right) {}

        std::string repr() {
            return "Unary(operator=" + operator_.lexeme + ", right=" + right->repr() + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_unary_expr(*this);
        }
    };

    class Literal {
    public:
        std::string value;

        Literal(std::string value) : value(value) {}

        std::string repr() {
            return "Literal(value=" + value + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_literal_expr(*this);
        }
    };

    class INT {
    public:
        std::string value;

        INT(std::string value) : value(value) {}

        std::string repr() {
            return "Number(value=" + value + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_int_expr(*this);
        }
    };

    class FLOAT {
    public:
        std::string value;

        FLOAT(std::string value) : value(value) {}

        std::string repr() {
            return "Number(value=" + value + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_float_expr(*this);
        }
    };

    class BOOL {
    public:
        std::string value;

        BOOL(std::string value) : value(value) {}

        std::string repr() {
            return "BOOL(value=" + value + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_bool_expr(*this);
        }
    };

    class NIL {
    public:
        std::string value;

        NIL(std::string value) : value(value) {}

        std::string repr() {
            return "Literal(value=None)";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_nil_expr(*this);
        }
    };

    class CHAR {
    public:
        std::string value;

        CHAR(std::string value) : value(value) {}

        std::string repr() {
            return "Literal(value=" + value + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_char_expr(*this);
        }
    };

    class Grouping {
    public:
        Expr* expression;

        Grouping(Expr* expression) : expression(expression) {}

        std::string repr() {
            return "Grouping(expression=" + expression->repr() + ")";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_grouping_expr(*this);
        }
    };

    class EmptyBlock {
    public:
        std::vector<Expr*> block;

        EmptyBlock(std::vector<Expr*> block) : block(block) {}

        std::string repr() {
            return "Unknown_block(block=...)";
        }

        template <typename R>
        R accept(Visitor<R>& visitor) {
            return visitor.visit_unknown_block(*this);
        }
    };
};

// ParseError class
class ParseError : public std::exception {
public:
    std::string message;

    ParseError(std::string message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

// Parser class
class Parser {
public:
    std::vector<Token> tokens;
    int current = 0;

    Parser(std::vector<Token> tokens) : tokens(tokens) {}

    std::vector<Expr*> parse() {
        std::vector<Expr*> statements;
        while (!is_at_end()) {
            statements.push_back(declaration());
        }
        return statements;
    }

    Expr* declaration() {
        if (match({TokenType::LEFT_BRACE})) {
            return handle_unknown_block_statement();
        }
        return expression();
    }

    Expr* expression() {
        return or_expr();
    }

    Expr* or_expr() {
        Expr* expr = and_expr();
        while (match({TokenType::LOGICAL_OR})) {
            Token operator_ = previous();
            Expr* right = and_expr();
            expr = new Expr::Logical(expr, operator_, right);
        }
        return expr;
    }

    Expr* and_expr() {
        Expr* expr = equality();
        while (match({TokenType::LOGICAL_AND})) {
            Token operator_ = previous();
            Expr* right = equality();
            expr = new Expr::Logical(expr, operator_, right);
        }
        return expr;
    }

    Expr* equality() {
        Expr* expr = comparison();
        while (match({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL, TokenType::DATA_EQUAL})) {
            Token operator_ = previous();
            Expr* right = comparison();
            expr = new Expr::Binary(expr, operator_, right);
        }
        return expr;
    }

    Expr* comparison() {
        Expr* expr = term();
        while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
            Token operator_ = previous();
            Expr* right = term();
            expr = new Expr::Binary(expr, operator_, right);
        }
        return expr;
    }

    Expr* term() {
        Expr* expr = factor();
        while (match({TokenType::MINUS, TokenType::PLUS})) {
            Token operator_ = previous();
            Expr* right = factor();
            expr = new Expr::Binary(expr, operator_, right);
        }
        return expr;
    }

    Expr* factor() {
        Expr* expr = unary();
        while (match({TokenType::SLASH, TokenType::STAR, TokenType::MODULUS})) {
            Token operator_ = previous();
            Expr* right = unary();
            expr = new Expr::Binary(expr, operator_, right);
        }
        return expr;
    }

    Expr* unary() {
        if (match({TokenType::BANG, TokenType::MINUS})) {
            Token operator_ = previous();
            Expr* right = unary();
            return new Expr::Unary(operator_, right);
        }
        return primary();
    }

    Expr* primary() {
        if (match({TokenType::INT})) {
            return new Expr::INT(previous().literal);
        }
        if (match({TokenType::FLOAT})) {
            return new Expr::FLOAT(previous().literal);
        }
        if (match({TokenType::FALSE})) {
            return new Expr::BOOL("false");
        }
        if (match({TokenType::TRUE})) {
            return new Expr::BOOL("true");
        }
        if (match({TokenType::NIL})) {
            return new Expr::NIL("nil");
        }
        if (match({TokenType::STRING})) {
            return new Expr::Literal(previous().literal);
        }
        if (match({TokenType::CHAR})) {
            return new Expr::CHAR(previous().literal);
        }
        if (match({TokenType::LEFT_PAREN})) {
            Expr* expr = expression();
            consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
            return new Expr::Grouping(expr);
        }
        if (match({TokenType::LEFT_BRACKET})) {
            Expr* expr = expression();
            consume(TokenType::RIGHT_BRACKET, "Expect ']' after expression.");
            return new Expr::Grouping(expr);
        }

        Token error_token = peek();
        error(error_token, "Expect expression.", current);
        return nullptr;
    }

    Expr* handle_unknown_block_statement() {
        std::vector<Expr*> unknown_block = block();
        consume(TokenType::RIGHT_BRACE, "Expecting '}' after '{' (a unknown block statement)");
        return new Expr::EmptyBlock(unknown_block);
    }

    std::vector<Expr*> block() {
        std::vector<Expr*> statements;
        while (!check(TokenType::RIGHT_BRACE) && !is_at_end()) {
            statements.push_back(declaration());
        }
        return statements;
    }

    bool match(std::initializer_list<TokenType> types) {
        for (TokenType token_type : types) {
            if (check(token_type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool check(TokenType token_type) {
        if (is_at_end()) return false;
        return peek().type == token_type;
    }

    Token advance(int distance = 1) {
        if (!is_at_end()) {
            current += distance;
        }
        return previous();
    }

    void past(int distance = 1) {
        if (!is_at_end()) {
            current -= distance;
        }
    }

    void future(int distance = 1) {
        if (!is_at_end()) {
            current += distance;
        }
    }

    bool is_at_end() {
        return peek().type == TokenType::EOF;
    }

    Token peek() {
        return tokens[current];
    }

    Token previous(int distance = 1) {
        return tokens[current - distance];
    }

    Token consume(TokenType token_type, std::string message) {
        if (check(token_type)) {
            return advance();
        }
        error(peek(), message, peek().line);
        return Token(TokenType::EOF, "", "", -1); // Dummy return to avoid warning
    }

    void error(Token token, std::string message, int line) {
        Token previous_token = previous();
        Token advance_token = advance();
        throw ParseError("Error at = " + previous_token.lexeme + ", near at " + token.lexeme + ", advance= " + advance_token.lexeme + ": " + message + " : ***[line no.=" + std::to_string(line) + "]***");
    }
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