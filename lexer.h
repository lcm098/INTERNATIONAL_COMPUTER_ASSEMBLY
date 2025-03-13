#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// Define token types as constants
extern const std::string LEFT_PAREN;
extern const std::string RIGHT_PAREN;
extern const std::string LEFT_BRACE;
extern const std::string RIGHT_BRACE;
extern const std::string COMMA;
extern const std::string DOT;
extern const std::string MINUS;
extern const std::string PLUS;
extern const std::string SEMICOLON;
extern const std::string SLASH;
extern const std::string IDENTIFIER;
extern const std::string STRING;
extern const std::string NUMBER;
extern const std::string CHAR;
extern const std::string FALSE;
extern const std::string EOF_TOKEN;
extern const std::string MODULUS;
extern const std::string LIST;
extern const std::string LEFT_BRACKET;
extern const std::string RIGHT_BRACKET;
extern const std::string ARROW;
extern const std::string COLON;
extern const std::string TILDE;
extern const std::string DICT;
extern const std::string INT;
extern const std::string FLOAT;
extern const std::string BINARY;
extern const std::string LITERAL;
extern const std::string VOID;

// Register and flag token types
extern const std::string RAX_VAR;
extern const std::string RBX_VAR;
extern const std::string RCX_VAR;
extern const std::string RDX_VAR;
extern const std::string RSI_VAR;
extern const std::string RDI_VAR;
extern const std::string RBP_VAR;
extern const std::string RSP_VAR;
extern const std::string R8_VAR;
extern const std::string R9_VAR;
extern const std::string R10_VAR;
extern const std::string R11_VAR;
extern const std::string R12_VAR;
extern const std::string R13_VAR;
extern const std::string R14_VAR;
extern const std::string R15_VAR;
extern const std::string RFLAGS_VAR;
extern const std::string RIP_VAR;
extern const std::string SC_VAR;
extern const std::string DS_VAR;
extern const std::string ES_VAR;
extern const std::string FS_VAR;
extern const std::string GS_VAR;
extern const std::string SS_VAR;
extern const std::string CF;
extern const std::string PF;
extern const std::string AF;
extern const std::string ZF;
extern const std::string SF;
extern const std::string TF;
extern const std::string IF;
extern const std::string DF;
extern const std::string OF;
extern const std::string ST;
extern const std::string MM;
extern const std::string XMM;
extern const std::string YMM;
extern const std::string ZMM;

// Instruction token types
extern const std::string MOV;
extern const std::string MOV_Q;
extern const std::string MOV_D;
extern const std::string MOV_ZX;
extern const std::string MOV_SX;
extern const std::string MOV_SB;
extern const std::string MOV_SW;
extern const std::string MOV_SD;
extern const std::string MOV_SQ;
extern const std::string XCHG;
extern const std::string BSWAP;
extern const std::string PUSH;
extern const std::string POP;
extern const std::string LEA;
extern const std::string LDS;
extern const std::string LES;
extern const std::string LGS;
extern const std::string LSS;
extern const std::string ADD;
extern const std::string ADC;
extern const std::string SUB;
extern const std::string SBB;
extern const std::string MUL;
extern const std::string IMUL;
extern const std::string DIV;
extern const std::string IDIV;
extern const std::string INC;
extern const std::string DEC;
extern const std::string NEG;
extern const std::string CMP;
extern const std::string TEST;
extern const std::string AND;
extern const std::string OR;
extern const std::string NOT;
extern const std::string XOR;
extern const std::string SHL;
extern const std::string SHR;
extern const std::string SAR;
extern const std::string ROL;
extern const std::string ROR;
extern const std::string RCL;
extern const std::string RCR;
extern const std::string JMP;
extern const std::string CALL;
extern const std::string RET;
extern const std::string LEAVE;
extern const std::string NOP;
extern const std::string UD2;
extern const std::string BREAK;
extern const std::string CONTINUE;
extern const std::string GOTO;
extern const std::string LABEL;
extern const std::string JE;
extern const std::string JNE;
extern const std::string JL;
extern const std::string JLE;
extern const std::string JG;
extern const std::string JGE;
extern const std::string JA;
extern const std::string JAE;
extern const std::string JB;
extern const std::string JBE;
extern const std::string JO;
extern const std::string JNO;
extern const std::string JS;
extern const std::string JNS;
extern const std::string JP;
extern const std::string JNP;
extern const std::string JCXZ;
extern const std::string JECXZ;
extern const std::string JRCXZ;
extern const std::string LOOP;
extern const std::string LOOP_Z;
extern const std::string LOOP_NZ;
extern const std::string LOOP_NE;
extern const std::string LOOP_E;
extern const std::string REP;
extern const std::string REP_E;
extern const std::string REP_NE;
extern const std::string CMP_SB;
extern const std::string CMP_SW;
extern const std::string CMP_SD;
extern const std::string CMP_SQ;
extern const std::string SCA_SB;
extern const std::string SCA_SW;
extern const std::string SCA_SD;
extern const std::string SCA_SQ;
extern const std::string STO_SB;
extern const std::string STO_SW;
extern const std::string STO_SD;
extern const std::string STO_SQ;
extern const std::string PUSH_A;
extern const std::string POP_A;
extern const std::string PUSH_F;
extern const std::string POP_F;
extern const std::string INT_3;
extern const std::string I_RET;
extern const std::string I_RET_Q;
extern const std::string SYSCALL;
extern const std::string SYS_RET;
extern const std::string CPUID;
extern const std::string RDT_SC;
extern const std::string HLT;
extern const std::string CLI;
extern const std::string STI;
extern const std::string CLD;
extern const std::string STD;
extern const std::string DB;
extern const std::string DW;
extern const std::string DD;
extern const std::string DQ;
extern const std::string DT;
extern const std::string DO;
extern const std::string DY;
extern const std::string DZ;
extern const std::string DSTR;
extern const std::string EQU;
extern const std::string PERCENT_DEFINE;
extern const std::string PERCENT_INCLUDE;
extern const std::string PERCENT_IF;
extern const std::string PERCENT_ELSE;
extern const std::string PERCENT_ENDIF;
extern const std::string PERCENT_MACRO;
extern const std::string PERCENT_END_MACRO;
extern const std::string PERCENT_REP;
extern const std::string PERCENT_END_REP;
extern const std::string ALIGN;
extern const std::string ALIGN_B;
extern const std::string SECTION;
extern const std::string SEGMENT;
extern const std::string GLOBAL;
extern const std::string EXTERN;
extern const std::string COMMON;
extern const std::string DOT_DATA;
extern const std::string DOT_BSS;
extern const std::string DOT_TEXT;
extern const std::string DOT_RO_DATA;
extern const std::string READ;
extern const std::string WRITE;
extern const std::string EXEC;
extern const std::string READ_WRITE;
extern const std::string READ_EXEC;
extern const std::string WRITE_EXEC;
extern const std::string READ_WRITE_EXEC;
extern const std::string OPEN;
extern const std::string CLOSE;
extern const std::string TRUE;

// Keywords map
extern std::map<std::string, std::string> keywords;

class Token {
public:
    std::string type;
    std::string lexeme;
    int line;
    std::string literal;

    Token(std::string token_type, std::string lexeme, int line, std::string literal = "");
    std::string repr() const;
};

class LexerError : public std::exception {
public:
    std::string message;

    LexerError(std::string message);
    const char* what() const noexcept override;
};

class Lexer {
public:
    std::string code_content;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;

    Lexer(std::string code_content);
    Token create_token(std::string token_type, std::string lexeme, int line, std::string literal = "");
    void report_error(int line, std::string message);
    std::vector<Token> scan_tokens();
    bool is_at_end();
    char advance();
    void add_token(std::string type, std::string literal = "");
    bool match(char expected);
    char peek();
    char peek_next(int distance = 1);
    void string();
    bool is_digit(char c);
    void number();
    bool is_alpha(char c);
    bool is_alpha_numeric(char c);
    void identifier();
    void char_consume();
    void scan_token();
    void handle_multiline_comment();
};

#endif // LEXER_H