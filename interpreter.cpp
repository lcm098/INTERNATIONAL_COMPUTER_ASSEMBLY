// interpreter.cpp
#include "interpreter.h"
#include "expr.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Implement Interpreter methods here...

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
    Environment() = default;
    Environment(Environment* enclosing) : enclosing(enclosing) {}

    // Add methods for managing variables, etc.
};

// Interpreter class
class Interpreter : public ExprVisitor {
public:
    Interpreter() {
        environment = std::make_unique<Environment>();
        bool debug_mode = false;
    }

    void visit_unknown_block(Expr* expr) override {
        execute_block(expr->block, std::make_unique<Environment>(environment.get()));
    }

    void execute_block(const std::vector<Expr*>& block, std::unique_ptr<Environment> env) {
        auto previous = std::move(environment);
        environment = std::move(env);

        for (auto stmt : block) {
            execute(stmt);
        }

        environment = std::move(previous);
    }

    void execute(Expr* stmt) {
        stmt->accept(this);
    }

    std::tuple<bool, std::string, std::size_t> visit_bool_expr(Expr* expr) override {
        bool value = expr->value == "true";
        return {value, "bool", reinterpret_cast<std::size_t>(&value)};
    }

    std::tuple<char, std::string, std::size_t> visit_char_expr(Expr* expr) override {
        char value = expr->value[0];
        return {value, "char", reinterpret_cast<std::size_t>(&value)};
    }

    std::tuple<std::nullptr_t, std::string, std::nullptr_t> visit_nil_expr(Expr* expr) override {
        return {nullptr, "nil", nullptr};
    }

    std::tuple<int, std::string, std::size_t> visit_int_expr(Expr* expr) override {
        int value = std::stoi(expr->value);
        return {value, "int", reinterpret_cast<std::size_t>(&value)};
    }

    std::tuple<float, std::string, std::size_t> visit_float_expr(Expr* expr) override {
        float value = std::stof(expr->value);
        return {value, "float", reinterpret_cast<std::size_t>(&value)};
    }

    std::tuple<float, std::string, std::size_t> visit_binary_expr(Expr* expr) override {
        auto [left, type1, id1] = evaluate(expr->left);
        auto [right, type2, id2] = evaluate(expr->right);

        if (expr->operator_.lexeme == "+") {
            float _eval_ = left + right;
            return {_eval_, "FLOAT", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "-") {
            float _eval_ = left - right;
            return {_eval_, "FLOAT", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "*") {
            float _eval_ = left * right;
            return {_eval_, "FLOAT", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "/") {
            float _eval_ = left / right;
            return {_eval_, "FLOAT", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == ">") {
            bool _eval_ = left > right;
            return {_eval_, "BOOL", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == ">=") {
            bool _eval_ = left >= right;
            return {_eval_, "BOOL", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "<") {
            bool _eval_ = left < right;
            return {_eval_, "BOOL", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "==") {
            bool _eval_ = left == right;
            return {_eval_, "BOOL", reinterpret_cast<std::size_t>(&_eval_)};
        } else if (expr->operator_.lexeme == "===") {
            bool _eval_ = typeid(left).name() == typeid(right).name();
            return {_eval_, "BOOL", reinterpret_cast<std::size_t>(&_eval_)};
        } else {
            throw std::runtime_error("Unsupported binary operator: " + expr->operator_.lexeme);
        }
    }

    bool visit_logical_expr(Expr* expr) override {
        auto [left, type1, id1] = evaluate(expr->left);
        auto [right, type2, id2] = evaluate(expr->right);

        if (expr->operator_.lexeme == "&&") {
            return left && right;
        } else if (expr->operator_.lexeme == "||") {
            return left || right;
        } else {
            throw std::runtime_error("Unsupported logical operator: " + expr->operator_.lexeme);
        }
    }

    std::tuple<int, std::string, std::size_t> visit_unary_expr(Expr* expr) override {
        auto [right, type, id] = evaluate(expr->right);

        if (expr->operator_.lexeme == "-") {
            return {-right, "int", reinterpret_cast<std::size_t>(&right)};
        } else if (expr->operator_.lexeme == "!") {
            return {!right, "bool", reinterpret_cast<std::size_t>(&right)};
        } else {
            throw std::runtime_error("Unsupported unary operator: " + expr->operator_.lexeme);
        }
    }

    std::tuple<std::string, std::string, std::size_t> visit_literal_expr(Expr* expr) override {
        return {expr->value, "str", reinterpret_cast<std::size_t>(&expr->value)};
    }

    std::tuple<std::string, std::string, std::size_t> visit_grouping_expr(Expr* expr) override {
        return evaluate(expr->expression);
    }

    std::string visit_using_type_expr(Expr* expr) override {
        return "Type Id [" + std::string(typeid(expr->value).name()) + "]";
    }

    std::string visit_cmd_activation_expr(Expr* expr) override {
        // Assuming cmd_inter and shlex.split are implemented in C++
        auto _command_buffer_ = shlex_split(expr->value);
        auto inter = cmd_inter(_command_buffer_);
        auto status = inter.Impl();
        return "ascii says = [" + status[0] + "], with Success Flag=[" + std::to_string(status[1]) + "]";
    }

    std::vector<std::tuple<std::string, std::string, std::size_t>> interpret(const std::vector<Expr*>& stmts) {
        std::vector<std::tuple<std::string, std::string, std::size_t>> results;
        for (auto stmt : stmts) {
            results.push_back(evaluate(stmt));
        }
        return results;
    }

    std::tuple<std::string, std::string, std::size_t> evaluate(Expr* expr) {
        if (!expr) {
            return {nullptr, "nil", 0};
        }
        return expr->accept(this);
    }

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
    InterpreterPipeline() : interpreter(std::make_unique<Interpreter>()) {}

    // Process a string containing source code
    void process_string(const std::string& source_code) {
        try {
            // Step 1: Lexical analysis
            Lexer lexer(source_code);
            std::vector<Token> tokens = lexer.scan_tokens();
            
            // Debug output for tokens (optional)
            if (debug_mode) {
                std::cout << "=== Tokens ===\n";
                for (const auto& token : tokens) {
                    std::cout << token.repr() << "\n";
                }
                std::cout << "==============\n\n";
            }
            
            // Step 2: Parsing
            Parser parser(tokens);
            std::vector<Expr*> ast = parser.parse();
            
            // Debug output for AST (optional)
            if (debug_mode) {
                std::cout << "=== Abstract Syntax Tree ===\n";
                // You might want to implement a pretty printer for your AST
                std::cout << "AST contains " << ast.size() << " top-level expressions\n";
                std::cout << "============================\n\n";
            }
            
            // Step 3: Interpretation/Execution
            std::vector<std::tuple<std::string, std::string, std::size_t>> results = interpreter->interpret(ast);
            
            // Output results
            std::cout << "=== Execution Results ===\n";
            for (const auto& result : results) {
                print_result(result);
            }
            std::cout << "========================\n";
            
            // Clean up AST nodes to prevent memory leaks
            for (auto expr : ast) {
                delete expr;
            }
            
        } catch (const LexerError& e) {
            std::cerr << "Lexer Error: " << e.what() << std::endl;
        } catch (const ParseError& e) {
            std::cerr << "Parser Error: " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cerr << "Runtime Error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    
    // Process a file containing source code
    void process_file(const std::string& file_path) {
        std::ifstream file(file_path);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file '" << file_path << "'" << std::endl;
            return;
        }
        
        std::stringstream buffer;
        buffer << file.rdbuf();
        process_string(buffer.str());
    }
    
    // Set debug mode
    void set_debug_mode(bool mode) {
        debug_mode = mode;
    }
}

int main() {
    // Create an interpreter pipeline
    InterpreterPipeline pipeline;

    // Enable debug output if needed
    pipeline.set_debug_mode(true);

    // Process a file
    pipeline.process_file("example.iasm");
}