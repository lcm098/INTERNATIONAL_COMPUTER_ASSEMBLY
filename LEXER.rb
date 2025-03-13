# Define token types as constants
MOV = "MOV"
ADD = "ADD"
SUB = "SUB"
MUL = "MUL"
DIV = "DIV"
MOD = "MOD"
CMP = "CMP"
JMP = "JMP"
FPTR = "FPTR"
PUSH = "PUSH"
POP = "POP"
VPTR = "VPTR"
LOAD = "LOAD"
STORE = "STORE"
UNLOAD = "ULOAD"
UNSTORE = "USTORE"
FIPTR = "FIPTR"
RAS_PTR = "RAS_PTR"
RAS = "RAS"
RBS = "RBS"
RBS_PTR = "RBS_PTR"
RCS = "RCS"
RCS_PTR = "RCS_PTR"
RDS = "RDS"
RDS_PTR = "RDS_PTR"
REX = "REX"
REX_PTR = "REX_PTR"
DD = "DD"
DL = "DL"
DR = "DR"
DA = "DA"
COLON = "COLON"
COMMA = "COMMA"
DOT = "DOT"
LEFT_PAREN = "LEFT_PAREN"
RIGHT_PAREN = "RIGHT_PAREN"
LEFT_BRACE = "LEFT_BRACE"
RIGHT_BRACE = "RIGHT_BRACE"
LEFT_BRACKET = "LEFT_BRACKET"
RIGHT_BRACKET = "RIGHT_BRACKET"
SECTION = "SECTION"
GLOBAL = "GLOBAL"
EXTERN = "EXTERN"
PUBLIC = "PUBLIC"
TEXT = "TEXT"
DATA = "DATA"
BSS = "BSS"
DOUBLE_OR = "DOUBLE_OR"
READ = "READ"
WRITE = "WRITE"
RETURN = "RETURN"
EXEC = "EXEC"
CALL = "CALL"
STRING = "STRING"
FLOAT = "FLOAT"
INT = "INT"
CHAR = "CHAR"
IDENTIFIER = "IDENTIFIER"
CMD_ACTIVATION = "CMD_ACTIVATION"
EOF = "EOF"  # Added missing EOF token type

TOKEN_TYPES = [
    MOV, ADD, SUB, MUL, DIV, MOD, CMP, JMP,
    CALL, FPTR, PUSH, POP, VPTR, LOAD, STORE, UNLOAD, UNSTORE,
    RAS_PTR, RAS, RBS, RBS_PTR, RCS, RCS_PTR, RDS, RDS_PTR, REX, REX_PTR,
    DD, DL, DR, DA, COLON, COMMA, DOT, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE,
    RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET, SECTION, GLOBAL, EXTERN, PUBLIC,
    TEXT, DATA, BSS, DOUBLE_OR, READ, WRITE, RETURN, EXEC, FIPTR
]

KEYWORDS = {
    "call" => CALL,
    "mov" => MOV,
    "fiptr" => FIPTR,
    "add" => ADD,
    "sub" => SUB,
    "mul" => MUL,
    "div" => DIV,
    "mod" => MOD,
    "cmp" => CMP,
    "jmp" => JMP,
    "fptr" => FPTR,
    "push" => PUSH,
    "pop" => POP,
    "vptr" => VPTR,
    "load" => LOAD,
    "store" => STORE,
    "unload" => ULOAD,
    "unstore" => USTORE,
    "ras_ptr" => RAS_PTR,
    "ras" => RAS,
    "rbs" => RBS,
    "rbs_ptr" => RBS_PTR,
    "rcs" => RCS,
    "rcs_ptr" => RCS_PTR,
    "rds" => RDS,
    "rds_ptr" => RDS_PTR,
    "rex" => REX,
    "rex_ptr" => REX_PTR,
    "dd" => DD,
    "dl" => DL,
    "dr" => DR,
    "da" => DA,
    "section" => SECTION,
    "global" => GLOBAL,
    "extern" => EXTERN,
    "public" => PUBLIC,
    "text" => TEXT,
    "data" => DATA,
    "bss" => BSS,
    "read" => READ,
    "write" => WRITE,
    "return" => RETURN,
    "exec" => EXEC
}

class Token
    attr_accessor :type, :lexeme, :line, :literal
  
    def initialize(type, lexeme, line, literal = nil)
      @type = type
      @lexeme = lexeme
      @line = line
      @literal = literal
    end
  
    # Override to_s for readable output
    def to_s
      "Token(type=#{@type}, lexeme=#{@lexeme}, literal=#{@literal}, line=#{@line})"
    end
  
    # Override inspect for debugging
    def inspect
      to_s
    end
  end

class LexerError < StandardError
    attr_accessor :message

    def initialize(message)
        super(message)
        @message = message
    end

    def to_s
        @message
    end
end

class Lexer
    attr_accessor :code_content, :tokens, :start, :current, :line

    def initialize(code_content)
        @code_content = code_content
        @tokens = []
        @start = 0
        @current = 0
        @line = 1
    end

    def create_token(token_type, lexeme, line, literal = nil)
        Token.new(token_type, lexeme, line, literal)
    end

    def report_error(line, message)
        raise LexerError.new("lexer except #{message}.\n\tOn Line=[#{line}]")
    end

    def scan_tokens
        while !is_at_end?
            @start = @current
            scan_token
        end
        @tokens << create_token(EOF, "", @line, nil)
        @tokens
    end

    def is_at_end?
        @current >= @code_content.length
    end

    def advance
        @current += 1
        @code_content[@current - 1]
    end

    def add_token(type, literal = nil)
        text = @code_content[@start...@current]
        @tokens << create_token(type, text, @line, literal)
    end

    def match(expected)
        return false if is_at_end?
        return false if @code_content[@current] != expected
        @current += 1
        true
    end

    def peek
        return "\0" if is_at_end?  # Changed '\0' to "\0" for a proper string
        @code_content[@current]
    end

    def peek_next(distance = 1)
        return "\0" if @current + distance >= @code_content.length  # Changed '\0' to "\0"
        @code_content[@current + distance]
    end

    def string
        while peek != '"' && !is_at_end?
            @line += 1 if peek == "\n"  # Changed '\n' to "\n"
            advance
        end
        if is_at_end?
            report_error(@line, "Unterminated string.")
            return
        end
        advance  # The closing "
        value = @code_content[@start + 1...@current - 1]
        add_token(STRING, value)
    end

    def command_activation
        while peek != '\\' && !is_at_end?
            @line += 1 if peek == "\n"  # Changed '\n' to "\n"
            advance
        end
        if is_at_end?
            report_error(@line, "Unterminated command literal.")
            return
        end
        advance  # The closing "
        value = @code_content[@start + 1...@current - 1]
        add_token(CMD_ACTIVATION, value)
    end

    def is_digit(c)
        c.match?(/\d/)
    end

    def number
        while is_digit(peek)
            advance
        end
        if peek == '.' && is_digit(peek_next)
            advance
            while is_digit(peek)
                advance
            end
            value = @code_content[@start...@current].to_f
            add_token(FLOAT, value)
        else
            value = @code_content[@start...@current].to_i
            add_token(INT, value)
        end
    end

    def is_alpha(c)
        c.match?(/[a-zA-Z_]/)
    end

    def is_alpha_numeric(c)
        is_alpha(c) || is_digit(c)
    end

    def identifier
        while is_alpha_numeric(peek)
            advance
        end
        text = @code_content[@start...@current]
        type = KEYWORDS.fetch(text, IDENTIFIER)
        add_token(type)
    end

    def char_consume
        value = peek()
        advance()  # Consume the character
        puts peek()
        unless match("'")  # Ensure the closing quote exists
            report_error(@line, "one letter - (why Too many characters in char literal)")
        end
    
        add_token(CHAR, value)
    end

    def scan_token
        c = advance
        
        case c
        when "|"
            if match("|")
                add_token(DOUBLE_OR)
            else
                add_token("|")  # Handle single pipe case
            end
        
        when '('
            add_token(LEFT_PAREN)
        when ')'
            add_token(RIGHT_PAREN)
        when '{'
            add_token(LEFT_BRACE)
        when '}'
            add_token(RIGHT_BRACE)
        when "["
            add_token(LEFT_BRACKET)
        when "]"
            add_token(RIGHT_BRACKET)
        when ','
            add_token(COMMA)
        when '.'
            add_token(DOT)
        
        when ':'
            add_token(COLON)
        when '/'
            if match('/')
                while peek != "\n" && !is_at_end?  # Changed '\n' to "\n"
                    advance
                end
            else
                add_token('/')  # Handle division operator
            end
        when ' ', "\r", "\t"  # Changed '\r', '\t' to "\r", "\t"
            # Ignore whitespace
        when "\n"  # Changed '\n' to "\n"
            @line += 1
        when '\\'
            command_activation
        when '"'
            if match('"')
                if match('"')
                    handle_multiline_comment
                else
                    report_error(@line, "Expecting '\"' for multiline comment.")
                end
            else
                string
            end
        when "'"
            char_consume
        else
            if is_digit(c)
                number
            elsif is_alpha(c)
                identifier
            else
                report_error(@line, "Unexpected character: #{c}")
            end
        end
    end

    def handle_multiline_comment
        # Skip the opening """
        while !is_at_end?
            if peek == '"' && peek_next == '"' && peek_next(2) == '"'
                advance  # Skip the first "
                advance  # Skip the second "
                advance  # Skip the third "
                return  # Successfully found the end of the comment
            end
            if peek == "\n"  # Changed '\n' to "\n"
                @line += 1  # Increment the line count if a newline is encountered
            end
            advance  # Continue advancing through the comment
        end

        # If the end of the file is reached without finding the end of the comment
        report_error(@line, "Unterminated multiline comment.")
    end
end