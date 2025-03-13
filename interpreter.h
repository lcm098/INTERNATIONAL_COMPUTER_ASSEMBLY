// interpreter.h
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#include "lexer.h"
#include "expr.h"

// Forward declarations
class Expr;
class Environment;

// Abstract base class for expression visitors
class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;

    virtual std::tuple<int, std::string, std::size_t> visit_int_expr(Expr* expr) = 0;
    virtual std::tuple<float, std::string, std::size_t> visit_float_expr(Expr* expr) = 0;
    virtual std::tuple<bool, std::string, std::size_t> visit_bool_expr(Expr* expr) = 0;
    virtual std::tuple<std::nullptr_t, std::string, std::nullptr_t> visit_nil_expr(Expr* expr) = 0;
    virtual std::tuple<char, std::string, std::size_t> visit_char_expr(Expr* expr) = 0;
    virtual void visit_unknown_block(Expr* expr) = 0;
    virtual std::tuple<float, std::string, std::size_t> visit_binary_expr(Expr* expr) = 0;
    virtual bool visit_logical_expr(Expr* expr) = 0;
    virtual std::tuple<int, std::string, std::size_t> visit_unary_expr(Expr* expr) = 0;
    virtual std::tuple<std::string, std::string, std::size_t> visit_literal_expr(Expr* expr) = 0;
    virtual std::tuple<std::string, std::string, std::size_t> visit_grouping_expr(Expr* expr) = 0;
    virtual std::string visit_using_type_expr(Expr* expr) = 0;
    virtual std::string visit_cmd_activation_expr(Expr* expr) = 0;
};

// Environment class (assuming it exists)
class Environment {
public:
    Environment();
    Environment(Environment* enclosing);

    // Add methods for managing variables, etc.
};

// Interpreter class
class Interpreter : public ExprVisitor {
public:
    Interpreter();

    void visit_unknown_block(Expr* expr) override;
    void execute_block(const std::vector<Expr*>& block, std::unique_ptr<Environment> env);
    void execute(Expr* stmt);
    std::tuple<bool, std::string, std::size_t> visit_bool_expr(Expr* expr) override;
    std::tuple<char, std::string, std::size_t> visit_char_expr(Expr* expr) override;
    std::tuple<std::nullptr_t, std::string, std::nullptr_t> visit_nil_expr(Expr* expr) override;
    std::tuple<int, std::string, std::size_t> visit_int_expr(Expr* expr) override;
    std::tuple<float, std::string, std::size_t> visit_float_expr(Expr* expr) override;
    std::tuple<float, std::string, std::size_t> visit_binary_expr(Expr* expr) override;
    bool visit_logical_expr(Expr* expr) override;
    std::tuple<int, std::string, std::size_t> visit_unary_expr(Expr* expr) override;
    std::tuple<std::string, std::string, std::size_t> visit_literal_expr(Expr* expr) override;
    std::tuple<std::string, std::string, std::size_t> visit_grouping_expr(Expr* expr) override;
    std::string visit_using_type_expr(Expr* expr) override;
    std::string visit_cmd_activation_expr(Expr* expr) override;

    std::vector<std::tuple<std::string, std::string, std::size_t>> interpret(const std::vector<Expr*>& stmts);
    std::tuple<std::string, std::string, std::size_t> evaluate(Expr* expr);

private:
    std::unique_ptr<Environment> environment;
};

// Expr class (assuming it exists)
class Expr {
public:
    virtual ~Expr() = default;
    virtual std::tuple<std::string, std::string, std::size_t> accept(ExprVisitor* visitor) = 0;
};

class InterpreterPipeline {
public:
    InterpreterPipeline();

    // Process a string containing source code
    void process_string(const std::string& source_code);

    // Process a file containing source code
    void process_file(const std::string& file_path);

    // Set debug mode
    void set_debug_mode(bool mode);

private:
    std::unique_ptr<Interpreter> interpreter;
    bool debug_mode;
};

#endif // INTERPRETER_H