#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// Define token types as constants
// Define token types as constants
const std::string LEFT_PAREN = "LEFT_PAREN";
const std::string RIGHT_PAREN = "RIGHT_PAREN";
const std::string LEFT_BRACE = "LEFT_BRACE";
const std::string RIGHT_BRACE = "RIGHT_BRACE";
const std::string COMMA = "COMMA";
const std::string DOT = "DOT";
const std::string MINUS = "MINUS";
const std::string PLUS = "PLUS";
const std::string SEMICOLON = "SEMICOLON";
const std::string SLASH = "SLASH";
const std::string IDENTIFIER = "IDENTIFIER";
const std::string STRING = "STRING";
const std::string NUMBER = "NUMBER";
const std::string CHAR = "CHAR";
const std::string FALSE = "FALSE";
const std::string EOF_TOKEN = "EOF";
const std::string MODULUS = "MODULUS";
const std::string LIST = "LIST";
const std::string LEFT_BRACKET = "LEFT_BRACKET";
const std::string RIGHT_BRACKET = "RIGHT_BRACKET";
const std::string ARROW = "ARROW";
const std::string COLON = "COLON";
const std::string TILDE = "TILDE";
const std::string DICT = "DICT";
const std::string INT = "INT";
const std::string FLOAT = "FLOAT";
const std::string BINARY = "BINARY";
const std::string LITERAL = "LITERAL";
const std::string VOID = "VOID";

// Register and flag token types
const std::string RAX_VAR = "RAX_VAR";
const std::string RBX_VAR = "RBX_VAR";
const std::string RCX_VAR = "RCX_VAR";
const std::string RDX_VAR = "RDX_VAR";
const std::string RSI_VAR = "RSI_VAR";
const std::string RDI_VAR = "RDI_VAR";
const std::string RBP_VAR = "RBP_VAR";
const std::string RSP_VAR = "RSP_VAR";
const std::string R8_VAR = "R8_VAR";
const std::string R9_VAR = "R9_VAR";
const std::string R10_VAR = "R10_VAR";
const std::string R11_VAR = "R11_VAR";
const std::string R12_VAR = "R12_VAR";
const std::string R13_VAR = "R13_VAR";
const std::string R14_VAR = "R14_VAR";
const std::string R15_VAR = "R15_VAR";
const std::string RFLAGS_VAR = "RFLAGS_VAR";
const std::string RIP_VAR = "RIP_VAR";
const std::string SC_VAR = "SC_VAR";
const std::string DS_VAR = "DS_VAR";
const std::string ES_VAR = "ES_VAR";
const std::string FS_VAR = "FS_VAR";
const std::string GS_VAR = "GS_VAR";
const std::string SS_VAR = "SS_VAR";
const std::string CF = "CF";
const std::string PF = "PF";
const std::string AF = "AF";
const std::string ZF = "ZF";
const std::string SF = "SF";
const std::string TF = "TF";
const std::string IF = "IF";
const std::string DF = "DF";
const std::string OF = "OF";
const std::string ST = "ST";
const std::string MM = "MM";
const std::string XMM = "XMM";
const std::string YMM = "YMM";
const std::string ZMM = "ZMM";

// Instruction token types
const std::string MOV = "MOV";
const std::string MOV_Q = "MOV_Q";
const std::string MOV_D = "MOV_D";
const std::string MOV_ZX = "MOV_ZX";
const std::string MOV_SX = "MOV_SX";
const std::string MOV_SB = "MOV_SB";
const std::string MOV_SW = "MOV_SW";
const std::string MOV_SD = "MOV_SD";
const std::string MOV_SQ = "MOV_SQ";
const std::string XCHG = "XCHG";
const std::string BSWAP = "BSWAP";
const std::string PUSH = "PUSH";
const std::string POP = "POP";
const std::string LEA = "LEA";
const std::string LDS = "LDS";
const std::string LES = "LES";
const std::string LGS = "LGS";
const std::string LSS = "LSS";
const std::string ADD = "ADD";
const std::string ADC = "ADC";
const std::string SUB = "SUB";
const std::string SBB = "SBB";
const std::string MUL = "MUL";
const std::string IMUL = "IMUL";
const std::string DIV = "DIV";
const std::string IDIV = "IDIV";
const std::string INC = "INC";
const std::string DEC = "DEC";
const std::string NEG = "NEG";
const std::string CMP = "CMP";
const std::string TEST = "TEST";
const std::string AND = "AND";
const std::string OR = "OR";
const std::string NOT = "NOT";
const std::string XOR = "XOR";
const std::string SHL = "SHL";
const std::string SHR = "SHR";
const std::string SAR = "SAR";
const std::string ROL = "ROL";
const std::string ROR = "ROR";
const std::string RCL = "RCL";
const std::string RCR = "RCR";
const std::string JMP = "JMP";
const std::string CALL = "CALL";
const std::string RET = "RET";
const std::string LEAVE = "LEAVE";
const std::string NOP = "NOP";
const std::string UD2 = "UD2";
const std::string BREAK = "BREAK";
const std::string CONTINUE = "CONTINUE";
const std::string GOTO = "GOTO";
const std::string LABEL = "LABEL";
const std::string JE = "JE";
const std::string JNE = "JNE";
const std::string JL = "JL";
const std::string JLE = "JLE";
const std::string JG = "JG";
const std::string JGE = "JGE";
const std::string JA = "JA";
const std::string JAE = "JAE";
const std::string JB = "JB";
const std::string JBE = "JBE";
const std::string JO = "JO";
const std::string JNO = "JNO";
const std::string JS = "JS";
const std::string JNS = "JNS";
const std::string JP = "JP";
const std::string JNP = "JNP";
const std::string JCXZ = "JCXZ";
const std::string JECXZ = "JECXZ";
const std::string JRCXZ = "JRCXZ";
const std::string LOOP = "LOOP";
const std::string LOOP_Z = "LOOP_Z";
const std::string LOOP_NZ = "LOOP_NZ";
const std::string LOOP_NE = "LOOP_NE";
const std::string LOOP_E = "LOOP_E";
const std::string REP = "REP";
const std::string REP_E = "REP_E";
const std::string REP_NE = "REP_NE";
const std::string CMP_SB = "CMP_SB";
const std::string CMP_SW = "CMP_SW";
const std::string CMP_SD = "CMP_SD";
const std::string CMP_SQ = "CMP_SQ";
const std::string SCA_SB = "SCA_SB";
const std::string SCA_SW = "SCA_SW";
const std::string SCA_SD = "SCA_SD";
const std::string SCA_SQ = "SCA_SQ";
const std::string STO_SB = "STO_SB";
const std::string STO_SW = "STO_SW";
const std::string STO_SD = "STO_SD";
const std::string STO_SQ = "STO_SQ";
const std::string PUSH_A = "PUSH_A";
const std::string POP_A = "POP_A";
const std::string PUSH_F = "PUSH_F";
const std::string POP_F = "POP_F";
const std::string INT_3 = "INT_3";
const std::string I_RET = "I_RET";
const std::string I_RET_Q = "I_RET_Q";
const std::string SYSCALL = "SYSCALL";
const std::string SYS_RET = "SYS_RET";
const std::string CPUID = "CPUID";
const std::string RDT_SC = "RDT_SC";
const std::string HLT = "HLT";
const std::string CLI = "CLI";
const std::string STI = "STI";
const std::string CLD = "CLD";
const std::string STD = "STD";
const std::string DB = "DB";
const std::string DW = "DW";
const std::string DD = "DD";
const std::string DQ = "DQ";
const std::string DT = "DT";
const std::string DO = "DO";
const std::string DY = "DY";
const std::string DZ = "DZ";
const std::string DSTR = "DSTR";
const std::string EQU = "EQU";
const std::string PERCENT_DEFINE = "PERCENT_DEFINE";
const std::string PERCENT_INCLUDE = "PERCENT_INCLUDE";
const std::string PERCENT_IF = "PERCENT_IF";
const std::string PERCENT_ELSE = "PERCENT_ELSE";
const std::string PERCENT_ENDIF = "PERCENT_ENDIF";
const std::string PERCENT_MACRO = "PERCENT_MACRO";
const std::string PERCENT_END_MACRO = "PERCENT_END_MACRO";
const std::string PERCENT_REP = "PERCENT_REP";
const std::string PERCENT_END_REP = "PERCENT_END_REP";
const std::string ALIGN = "ALIGN";
const std::string ALIGN_B = "ALIGN_B";
const std::string SECTION = "SECTION";
const std::string SEGMENT = "SEGMENT";
const std::string GLOBAL = "GLOBAL";
const std::string EXTERN = "EXTERN";
const std::string COMMON = "COMMON";
const std::string DOT_DATA = "DOT_DATA";
const std::string DOT_BSS = "DOT_BSS";
const std::string DOT_TEXT = "DOT_TEXT";
const std::string DOT_RO_DATA = "DOT_RO_DATA";
const std::string READ = "READ";
const std::string WRITE = "WRITE";
const std::string EXEC = "EXEC";
const std::string READ_WRITE = "READ_WRITE";
const std::string READ_EXEC = "READ_EXEC";
const std::string WRITE_EXEC = "WRITE_EXEC";
const std::string READ_WRITE_EXEC = "READ_WRITE_EXEC";
const std::string OPEN = "OPEN";
const std::string CLOSE = "CLOSE";
const std::string TRUE = "TRUE";


std::vector<std::string> TOKEN_TYPES = {
    RAX_VAR, RBX_VAR, RCX_VAR, RDX_VAR, RSI_VAR, RDI_VAR, RBP_VAR, RSP_VAR, R8_VAR, R9_VAR, 
    R10_VAR, R11_VAR, R12_VAR, R13_VAR, R14_VAR, R15_VAR, RFLAGS_VAR, RIP_VAR,
    SC_VAR, DS_VAR, ES_VAR, FS_VAR, GS_VAR, SS_VAR, CF, PF, AF, ZF, SF, TF, IF, DF, OF, ST, MM, XMM, YMM, ZMM,
    MOV, MOV_Q, MOV_D, MOV_ZX, MOV_SX, MOV_SB, MOV_SW, MOV_SD, MOV_SQ,
    XCHG, BSWAP, PUSH, POP, LEA, LDS, LES, LGS, LSS,
    ADD, ADC, SUB, SBB, MUL, IMUL, DIV, IDIV, INC, DEC, NEG, CMP, TEST,
    AND, OR, NOT, XOR, SHL, SHR, SAR, ROL, ROR, RCL, RCR,
    JMP, CALL, RET, LEAVE, NOP, UD2, BREAK, CONTINUE, GOTO, LABEL,
    JE, JNE, JL, JLE, JG, JGE, JA, JAE, JB, JBE, JO, JNO, JS, JNS, JP, JNP, JCXZ, JECXZ, JRCXZ,
    LOOP, LOOP_Z, LOOP_NZ, LOOP_NE, LOOP_E,
    REP, REP_E, REP_NE, MOV_SB, MOV_SW, MOV_SD, MOV_SQ,
    CMP_SB, CMP_SW, CMP_SD, CMP_SQ,
    SCA_SB, SCA_SW, SCA_SD, SCA_SQ,
    STO_SB, STO_SW, STO_SD, STO_SQ,
    PUSH, POP, PUSH_A, POP_A, PUSH_F, POP_F,
    INT, INT_3, I_RET, I_RET_Q, SYSCALL, SYS_RET,
    CPUID, RDT_SC, HLT, CLI, STI, CLD, STD,
    DB, DW, DD, DQ, DT, DO, DY, DZ, DSTR,
    EQU, PERCENT_DEFINE, PERCENT_INCLUDE, PERCENT_IF, PERCENT_ELSE, PERCENT_ENDIF, 
    PERCENT_MACRO, PERCENT_END_MACRO, PERCENT_REP, PERCENT_END_REP,
    ALIGN, ALIGN_B, SECTION, SEGMENT, GLOBAL, EXTERN, COMMON,
    DOT_DATA, DOT_BSS, DOT_TEXT, DOT_RO_DATA,
    READ, WRITE, EXEC, READ_WRITE, READ_EXEC, WRITE_EXEC, READ_WRITE_EXEC,
    OPEN, CLOSE, TRUE, FALSE, DICT, LIST, STRING, CHAR, INT, FLOAT, VOID,

};

// Keywords map
std::map<std::string, std::string> keywords = {
    {"rax_var", RAX_VAR}, {"rbx_var", RBX_VAR}, {"rcx_var", RCX_VAR}, {"rdx_var", RDX_VAR}, {"rsi_var", RSI_VAR}, {"rdi_var", RDI_VAR}, {"rbp_var", RBP_VAR}, {"rsp_var", RSP_VAR}, {"r8_var", R8_VAR}, {"r9_var", R9_VAR},
    {"r10_var", R10_VAR}, {"r11_var", R11_VAR}, {"r12_var", R12_VAR}, {"r13_var", R13_VAR}, {"r14_var", R14_VAR}, {"r15_var", R15_VAR}, {"rflags_var", RFLAGS_VAR}, {"rip_var", RIP_VAR},
    {"sc_var", SC_VAR}, {"ds_var", DS_VAR}, {"es_var", ES_VAR}, {"fs_var", FS_VAR}, {"gs_var", GS_VAR}, {"ss_var", SS_VAR}, {"cf", CF}, {"pf", PF}, {"af", AF}, {"zf", ZF}, {"sf", SF}, {"tf", TF}, {"if", IF}, {"df", DF}, {"of", OF}, {"st", ST}, {"mm", MM}, {"xmm", XMM}, {"ymm", YMM}, {"zmm", ZMM},
    {"mov", MOV}, {"mov_q", MOV_Q}, {"mov_d", MOV_D}, {"mov_zx", MOV_ZX}, {"mov_sx", MOV_SX}, {"mov_sb", MOV_SB}, {"mov_sw", MOV_SW}, {"mov_sd", MOV_SD}, {"mov_sq", MOV_SQ},
    {"xchg", XCHG}, {"bswap", BSWAP}, {"push", PUSH}, {"pop", POP}, {"lea", LEA}, {"lds", LDS}, {"les", LES}, {"lgs", LGS}, {"lss", LSS},
    {"add", ADD}, {"adc", ADC}, {"sub", SUB}, {"sbb", SBB}, {"mul", MUL}, {"imul", IMUL}, {"div", DIV}, {"idiv", IDIV}, {"inc", INC}, {"dec", DEC}, {"neg", NEG}, {"cmp", CMP}, {"test", TEST},
    {"and", AND}, {"or", OR}, {"not", NOT}, {"xor", XOR}, {"shl", SHL}, {"shr", SHR}, {"sar", SAR}, {"rol", ROL}, {"ror", ROR}, {"rcl", RCL}, {"rcr", RCR},
    {"jmp", JMP}, {"call", CALL}, {"ret", RET}, {"leave", LEAVE}, {"nop", NOP}, {"ud2", UD2}, {"break", BREAK}, {"continue", CONTINUE}, {"goto", GOTO}, {"label", LABEL},
    {"je", JE}, {"jne", JNE}, {"jl", JL}, {"jle", JLE}, {"jg", JG}, {"jge", JGE}, {"ja", JA}, {"jae", JAE}, {"jb", JB}, {"jbe", JBE}, {"jo", JO}, {"jno", JNO}, {"js", JS}, {"jns", JNS}, {"jp", JP}, {"jnp", JNP}, {"jcxz", JCXZ}, {"jecxz", JECXZ}, {"jrcxz", JRCXZ},
    {"loop", LOOP}, {"loop_z", LOOP_Z}, {"loop_nz", LOOP_NZ}, {"loop_ne", LOOP_NE}, {"loop_e", LOOP_E}, {"rep", REP}, {"rep_e", REP_E}, {"rep_ne", REP_NE},
    {"cmp_sb", CMP_SB}, {"cmp_sw", CMP_SW}, {"cmp_sd", CMP_SD}, {"cmp_sq", CMP_SQ}, {"sca_sb", SCA_SB}, {"sca_sw", SCA_SW}, {"sca_sd", SCA_SD}, {"sca_sq", SCA_SQ}, {"sto_sb", STO_SB}, {"sto_sw", STO_SW}, {"sto_sd", STO_SD}, {"sto_sq", STO_SQ},
    {"push_a", PUSH_A}, {"pop_a", POP_A}, {"push_f", PUSH_F}, {"pop_f", POP_F}, {"int_3", INT_3}, {"i_ret", I_RET}, {"i_ret_q", I_RET_Q}, {"syscall", SYSCALL}, {"sys_ret", SYS_RET}, {"cpuid", CPUID}, {"rdt_sc", RDT_SC}, {"hlt", HLT}, {"cli", CLI}, {"sti", STI}, {"cld", CLD}, {"std", STD},
    {"db", DB}, {"dw", DW}, {"dd", DD}, {"dq", DQ}, {"dt", DT}, {"do", DO}, {"dy", DY}, {"dz", DZ}, {"dstr", DSTR}, {"equ", EQU}, {"%define", PERCENT_DEFINE}, {"%include", PERCENT_INCLUDE}, {"%if", PERCENT_IF}, {"%else", PERCENT_ELSE}, {"%endif", PERCENT_ENDIF},
    {"%macro", PERCENT_MACRO}, {"%endmacro", PERCENT_END_MACRO}, {"%rep", PERCENT_REP}, {"%endrep", PERCENT_END_REP}, {"align", ALIGN}, {"align_b", ALIGN_B}, {"section", SECTION}, {"segment", SEGMENT}, {"global", GLOBAL}, {"extern", EXTERN}, {"common", COMMON},
    {"data", DOT_DATA}, {"bss", DOT_BSS}, {"text", DOT_TEXT}, {"rodata", DOT_RO_DATA}, {"read", READ}, {"write", WRITE}, {"exec", EXEC}, {"read_write", READ_WRITE}, {"read_exec", READ_EXEC}, {"write_exec", WRITE_EXEC}, {"read_write_exec", READ_WRITE_EXEC}, {"open", OPEN}, {"close", CLOSE}, {"true", TRUE}, {"false", FALSE}, {"dict", DICT}, {"list", LIST}, {"string", STRING}, {"char", CHAR}, {"int", INT}, {"float", FLOAT}, {"void", VOID}
};

class Token {
public:
    std::string type;
    std::string lexeme;
    int line;
    std::string literal;

    Token(std::string token_type, std::string lexeme, int line, std::string literal = "")
        : type(token_type), lexeme(lexeme), line(line), literal(literal) {}

    std::string repr() const {
        return "Token(type=" + type + ", lexeme=" + lexeme + ", literal=" + literal + ", line=" + std::to_string(line) + ")";
    }
};

class LexerError : public std::exception {
public:
    std::string message;

    LexerError(std::string message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class Lexer {
public:
    std::string code_content;
    std::vector<Token> tokens;
    int start;
    int current;
    int line;

    Lexer(std::string code_content) : code_content(code_content), start(0), current(0), line(1) {}

    Token create_token(std::string token_type, std::string lexeme, int line, std::string literal = "") {
        return Token(token_type, lexeme, line, literal);
    }

    void report_error(int line, std::string message) {
        throw LexerError("lexer except " + message + ".\n\tOn Line=[" + std::to_string(line) + "]");
    }

    std::vector<Token> scan_tokens() {
        while (!is_at_end()) {
            start = current;
            scan_token();
        }
        tokens.push_back(create_token(EOF_TOKEN, "", line, ""));
        return tokens;
    }

    bool is_at_end() {
        return current >= code_content.length();
    }

    char advance() {
        current++;
        return code_content[current - 1];
    }

    void add_token(std::string type, std::string literal = "") {
        std::string text = code_content.substr(start, current - start);
        tokens.push_back(create_token(type, text, line, literal));
    }

    bool match(char expected) {
        if (is_at_end()) return false;
        if (code_content[current] != expected) return false;
        current++;
        return true;
    }

    char peek() {
        if (is_at_end()) return '\0';
        return code_content[current];
    }

    char peek_next(int distance = 1) {
        if (current + distance >= code_content.length()) return '\0';
        return code_content[current + distance];
    }

    void string() {
        while (peek() != '"' && !is_at_end()) {
            if (peek() == '\n') line++;
            advance();
        }
        if (is_at_end()) {
            report_error(line, "Unterminated string.");
            return;
        }
        advance();  // The closing "
        std::string value = code_content.substr(start + 1, current - start - 2);
        add_token(STRING, value);
    }


    bool is_digit(char c) {
        return c >= '0' && c <= '9';
    }

    void number() {
        while (is_digit(peek())) advance();
        if (peek() == '.' && is_digit(peek_next())) {
            advance();
            while (is_digit(peek())) advance();
            double value = std::stod(code_content.substr(start, current - start));
            add_token(FLOAT, std::to_string(value));
        } else {
            int value = std::stoi(code_content.substr(start, current - start));
            add_token(INT, std::to_string(value));
        }
    }

    bool is_alpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool is_alpha_numeric(char c) {
        return is_alpha(c) || is_digit(c);
    }

    void identifier() {
        while (is_alpha_numeric(peek())) advance();
        std::string text = code_content.substr(start, current - start);
        std::string type = keywords.find(text) != keywords.end() ? keywords[text] : IDENTIFIER;
        add_token(type);
    }

    void char_consume() {
        char value = peek();
        add_token(CHAR, std::string(1, value));
        current++;
        if (!match('\'')) {
            report_error(line, "too many char in char literal");
        }
    }

    void scan_token() {
        char c = advance();

        if (c == '(') {
            add_token(LEFT_PAREN);
        } else if (c == ')') {
            add_token(RIGHT_PAREN);
        } else if (c == '{') {
            add_token(LEFT_BRACE);
        } else if (c == '}') {
            add_token(RIGHT_BRACE);
        } else if (c == '[') {
            add_token(LEFT_BRACKET);
        } else if (c == ']') {
            add_token(RIGHT_BRACKET);
        } else if (c == ',') {
            add_token(COMMA);
        } else if (c == '.') {
            add_token(DOT);
        } else if (c == '%') {
            add_token(MODULUS);
        } else if (c == ':') {
            add_token(COLON);
        } else if (c == '/') {
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) advance();
            } else {
                add_token(SLASH);
            }
        } else if (c == ' ' || c == '\r' || c == '\t') {
            // Ignore whitespace
        } else if (c == '\n') {
            line++;
        } else if (c == '"') {
            if (match('"')) {
                if (match('"')) {
                    handle_multiline_comment();
                } else {
                    report_error(line, "Expecting '\"' for multiline comment.");
                }
            } else {
                string();
            }
        } else if (is_digit(c)) {
            number();
        } else if (is_alpha(c)) {
            identifier();
        } else if (c == '\'') {
            char_consume();
        } else {
            report_error(line, "Unexpected character.");
        }
    }

    void handle_multiline_comment() {
        advance();  // Skip the first "
        advance();  // Skip the second "
        advance();  // Skip the third "

        while (!is_at_end()) {
            if (peek() == '"' && peek_next() == '"' && peek_next(2) == '"') {
                advance();  // Skip the first "
                advance();  // Skip the second "
                advance();  // Skip the third "
                return;
            }
            if (peek() == '\n') line++;
            advance();
        }

        report_error(line, "Unterminated multiline comment.");
    }
};
