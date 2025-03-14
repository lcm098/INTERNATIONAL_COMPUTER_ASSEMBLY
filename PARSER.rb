class Expr
  class Binary
    attr_accessor :left, :operator, :right

    def initialize(left, operator, right)
      @left = left
      @operator = operator
      @right = right
    end

    def to_s
      "Binary(left=#{@left}, operator=#{@operator}, right=#{@right})"
    end

    def accept(visitor)
      visitor.visit_binary_expr(self)
    end
  end

  class Logical
    attr_accessor :left, :operator, :right

    def initialize(left, operator, right)
      @left = left
      @operator = operator
      @right = right
    end

    def accept(visitor)
      visitor.visit_logical_expr(self)
    end
  end

  class Unary
    attr_accessor :operator, :right

    def initialize(operator, right)
      @operator = operator
      @right = right
    end

    def to_s
      "Unary(operator=#{@operator}, right=#{@right})"
    end

    def accept(visitor)
      visitor.visit_unary_expr(self)
    end
  end

  class Literal
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Literal(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_literal_expr(self)
    end
  end

  class INT
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Number(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_int_expr(self)
    end
  end

  class FLOAT
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Number(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_float_expr(self)
    end
  end

  class BOOL
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "BOOL(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_bool_expr(self)
    end
  end

  class NIL
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Literal(value=#{nil})"
    end

    def accept(visitor)
      visitor.visit_nil_expr(self)
    end
  end

  class CHAR
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Literal(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_char_expr(self)
    end
  end

  class Grouping
    attr_accessor :expression

    def initialize(expression)
      @expression = expression
    end

    def to_s
      "Grouping(expression=#{@expression})"
    end

    def accept(visitor)
      visitor.visit_grouping_expr(self)
    end
  end

  class CmdActivation
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Command(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_cmd_activation_expr(self)
    end
  end

  class UsingType
    attr_accessor :value

    def initialize(value)
      @value = value
    end

    def to_s
      "Using(value=#{@value})"
    end

    def accept(visitor)
      visitor.visit_using_type_expr(self)
    end
  end

  class EmptyBlock
    attr_accessor :block

    def initialize(block)
      @block = block
    end

    def to_s
      "Unknown_block(block=#{@block})"
    end

    def accept(visitor)
      visitor.visit_unknown_block(self)
    end
  end

  class DataSeek
    attr_accessor :line, :special_variable_type, :value

    def initialize(line, special_variable_type, value)
      @line = line
      @special_variable_type = special_variable_type
      @value = value
    end

    def to_s
      "mov variable-type=#{@special_variable_type.lexeme}, value=#{@value}"
    end

    def accept(visitor)
      visitor.visit_data_seek(self)
    end
  end
end

class ParseError < StandardError
  attr_accessor :message

  def initialize(message)
    super(message)
    @message = message
  end

  def to_s
    @message
  end
end

class Parser
  attr_accessor :tokens, :current

  def initialize(tokens)
    @tokens = tokens
    @current = 0
  end

  def parse
    statements = []
    while !is_at_end?
      statements << declaration_entry
    end
    statements
  end

  def declaration_entry
    # Ensure the entry point is present
  
    if match(SECTION)
      # Parse the entry point
      consume(DOT, "Expected '.' in the entry-point of text-code")
      consume(TEXT, "Expected 'text' as the entry-point of code")
      consume(DOUBLE_OR, "Expected '||' environment-encloser of main-text code")
    
      # Parse the instructions inside the entry point
      instructions = []
      while !check(DOUBLE_OR) && !is_at_end?
        instructions << text_statements_instructions
      end
    
      # Consume the closing '||'
      consume(DOUBLE_OR, "Expected '||' to close the main-text code")
    
      instructions
    else
      raise ParseError.new("Missing entry point: 'section .text ||'")
    end
  end

  def text_statements_instructions
    if match(LEFT_BRACKET)
      return handle_unknown_block_statement
    end
    if match(MOV)
      return handle_data_to_special_variable
    end
    expression
  end

  def handle_data_to_special_variable
    line = peek.line
    special_variable_type = consume(IDENTIFIER, "Expected 'special-variable' after mov")
    consume(COMMA, "Expected ',' after 'mov something, something'")
    value = expression
    Expr::DataSeek.new(line, special_variable_type, value)
  end

  def expression
    or_expr
  end

  def or_expr
    expr = and_expr
    while match(CONDITIONAL_OR)
      operator = previous
      right = and_expr
      expr = Expr::Logical.new(expr, operator, right)
    end
    expr
  end

  def and_expr
    expr = equality
    while match(CONDITIONAL_AND)
      operator = previous
      right = equality
      expr = Expr::Logical.new(expr, operator, right)
    end
    expr
  end

  def equality
    expr = comparison
    while match(BANG_EQUAL, EQUAL_EQUAL, DATA_EQUAL)
      operator = previous
      right = comparison
      expr = Expr::Binary.new(expr, operator, right)
    end
    expr
  end

  def comparison
    expr = unary
    while match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL)
      operator = previous
      right = unary
      expr = Expr::Binary.new(expr, operator, right)
    end
    expr
  end

  def unary
    if match(BANG)
      operator = previous
      right = unary
      return Expr::Unary.new(operator, right)
    end
    primary
  end

  def primary
    if match(INT)
      return Expr::INT.new(previous.literal)
    end
    if match(FLOAT)
      return Expr::FLOAT.new(previous.literal)
    end
    if match(FALSE)
      return Expr::BOOL.new('false')
    end
    if match(TRUE)
      return Expr::BOOL.new('true')
    end
    if match(NIL)
      return Expr::NIL.new('nil')
    end
    if match(STRING)
      return Expr::Literal.new(previous.literal)
    end
    if match(CHAR)
      return Expr::CHAR.new(previous.literal)
    end
    if match(LEFT_PAREN)
      expr = expression
      consume(RIGHT_PAREN, "Expect ')' after expression.")
      return Expr::Grouping.new(expr)
    end
    if match(LEFT_BRACKET)
      expr = expression
      consume(RIGHT_BRACKET, "Expect ']' after expression.")
      return Expr::Grouping.new(expr)
    end
    if match(USING)
      expr = expression
      return Expr::UsingType.new(expr)
    end
    if match(CMD_ACTIVATION)
      return Expr::CmdActivation.new(previous.literal)
    end
    error_token = peek
    error(error_token, "Expect expression.", @current)
  end

  def handle_unknown_block_statement
    unknown_block = block
    consume(RIGHT_BRACKET, "Expecting ']' after '[' (a unknown block statement)")
    Expr::EmptyBlock.new(unknown_block)
  end

  def block
    statements = []
    while !check(RIGHT_BRACKET) && !is_at_end?
      statements << declaration_entry
    end
    statements
  end

  def match(*types)
    types.each do |token_type|
      current_type = peek.type
      if current_type == token_type
        advance
        return true
      end
    end
    false
  end

  def check(token_type)
    if is_at_end?
      return false
    end
    peek.type == token_type
  end

  def advance(distance = 1)
    if !is_at_end?
      @current += distance
    end
    previous
  end

  def past(distance = 1)
    if !is_at_end?
      @current -= distance
    end
  end

  def future(distance = 1)
    if !is_at_end?
      @current += distance
    end
  end

  def is_at_end?
    peek.type == EOF
  end

  def peek
    @tokens[@current]
  end

  def previous(distance = 1)
    @tokens[@current - distance]
  end

  def consume(token_type, message)
    if check(token_type)
      return advance
    end
    error(peek, message, peek.line)
  end

  def error(token, message, line)
    previous_token = previous
    advance_token = advance
    raise ParseError.new("Error at = #{previous_token.lexeme}, near at #{token.lexeme}, advance= #{advance_token.lexeme}: #{message} : ***[line no.=#{line}]***")
  end
end