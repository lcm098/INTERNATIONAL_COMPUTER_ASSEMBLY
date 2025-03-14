class ExprVisitor
    # Abstract visitor class for visiting expressions in the abstract syntax tree.
    # Each visit method corresponds to a specific type of expression.
  
    def visit_number_expr(expr)
      raise NotImplementedError, "visit_number_expr must be implemented by a subclass."
    end
  
    def visit_bool_expr(expr)
      raise NotImplementedError, "visit_bool_expr must be implemented by a subclass."
    end
  
    def visit_nil_expr(expr)
      raise NotImplementedError, "visit_nil_expr must be implemented by a subclass."
    end
  
    def visit_char_expr(expr)
      raise NotImplementedError, "visit_char_expr must be implemented by a subclass."
    end
  
    def visit_binary_expr(expr)
      raise NotImplementedError, "visit_binary_expr must be implemented by a subclass."
    end
  
    def visit_logical_expr(expr)
      raise NotImplementedError, "visit_logical_expr must be implemented by a subclass."
    end
  
    def visit_unary_expr(expr)
      raise NotImplementedError, "visit_unary_expr must be implemented by a subclass."
    end
  
    def visit_literal_expr(expr)
      raise NotImplementedError, "visit_literal_expr must be implemented by a subclass."
    end
  
    def visit_grouping_expr(expr)
      raise NotImplementedError, "visit_grouping_expr must be implemented by a subclass."
    end
  
    def visit_cmd_activation_expr(expr)
      raise NotImplementedError, "visit_cmd_activation_expr must be implemented by a subclass."
    end
  
    def accept(visitor)
      raise NotImplementedError, "Subclasses must implement accept method."
    end
  
    def visit_unknown_block(stmt)
      raise NotImplementedError, "visit_unknown_block must be implemented by a subclass."
    end
  
    def visit_float_expr(expr)
      raise NotImplementedError, "visit_float_expr must be implemented by a subclass."
    end

    def visit_data_seek(inst)
      raise NotImplementedError, "visit_data_seek must be implemented by a subclass."
    end

    def visit_identifier(inst)
      raise NotImplementedError, "visit_identifier must be implemented by a subclass."
    end

    def visit_hidden_array_grouping(inst)
      raise NotImplementedError, "visit_hidden_array_grouping must be implemented by a subclass."
    end
  end
  
  class Interpreter < ExprVisitor
    attr_accessor :environment
  
    def initialize
      @environment = Environment.new()
      @data_buff_type = SpecialVariablesAndPointers.new()
      SpecialVariablesAndPointers.data_buffer_type.each do |item|
        @environment.define(item, 0, false)
      end
    end
  
    # Interpreter for evaluating expressions. Implements the visitor methods.
    
    def visit_identifier(identifier)

      begin
        if environment.is_defined(identifier)
          return environment.get(identifier)
        else
          return evaluate(identifier)
        end
      rescue => e
        raise "undeclared identifier named '#{identifier}'. \n\t On Line =[#{line}]"
      end
    end

    def visit_hidden_array_grouping(inst)
      line = inst.line
      elements = inst.elements
      buffer = []

      for index in 0 ... elements.length
        buffer << visit_identifier(elements[index])
      end

      return buffer
    end

    def visit_load_instruction(inst)
      line = inst.line
      pointer_type = inst.pointer_type.lexeme
      value = visit_identifier(inst.value)

      if SpecialVariablesAndPointers.data_buffer_type.include?(pointer_type)
        if pointer_type == FPTR
          @environment.assign(RDO_VAR, {FPTR => value})
          @environment.assign(FPTR, value)
        elsif pointer_type == VPTR
          @environment.assign(RDO_VAR, {VPTR => value})
          @environment.assign(VPTR, value)
      else
        "Using unregistered special pointer named '#{special_var}' why?\n\t On Line =[#{line}]"
      end
    end

    def visit_data_seek(inst)
      @data_buff_type = SpecialVariablesAndPointers.new()
      special_var = inst.special_variable_type.lexeme
      special_val = inst.value

      if SpecialVariablesAndPointers.data_buffer_type.include?(special_var)
        @environment.assign(special_var, special_val)
        @environment.assign(RDO_VAR, special_val)
      else
        raise "Using unregistered special variable named '#{special_var}' why?\n\t On Line =[#{inst.line}]"
      end
    end

    def visit_unknown_block(expr)
      execute_block(expr.block, Environment.new(@environment))
    end
  
    def execute_block(block, environment = nil)
      previous = @environment
      environment ||= Environment.new(previous) # Lexical scoping
      @environment = environment
  
      block.each do |statement|
        execute(statement)
      end
      @environment = previous
    end
  
    def execute(stmt)
      stmt.accept(self)
    end
  
    def visit_bool_expr(expr)
      [expr.value == "true", "bool", expr.value.object_id]
    end
  
    def visit_char_expr(expr)
      [expr.value, "char", expr.value.object_id]
    end
  
    def visit_nil_expr(expr)
      [nil, "nil", nil]
    end
  
    def visit_int_expr(expr)
      [expr.value.to_i, "int", expr.value.object_id]
    end
  
    def visit_float_expr(expr)
      [expr.value.to_f, "float", expr.value.object_id]
    end
  
    def visit_binary_expr(expr)
      left = evaluate(expr.left)[0]
      right = evaluate(expr.right)[0]
  
      case expr.operator.lexeme
      when '+'
        _eval_ = left + right
        [_eval_.to_f, "FLOAT", _eval_.object_id]
      when '-'
        _eval_ = left - right
        [_eval_.to_f, "FLOAT", _eval_.object_id]
      when '*'
        _eval_ = left * right
        [_eval_.to_f, "FLOAT", _eval_.object_id]
      when '/'
        _eval_ = left / right
        [_eval_.to_f, "FLOAT", _eval_.object_id]
      when '>'
        _eval_ = left > right
        [_eval_, "BOOL", _eval_.object_id]
      when '>='
        _eval_ = left >= right
        [_eval_, "BOOL", _eval_.object_id]
      when '<'
        _eval_ = left < right
        [_eval_, "BOOL", _eval_.object_id]
      when '=='
        _eval_ = left == right
        [_eval_, "BOOL", _eval_.object_id]
      when '==='
        _eval_ = left.class == right.class
        [_eval_, "BOOL", _eval_.object_id]
      else
        raise "Unsupported binary operator: #{expr.operator}"
      end
    end
  
    def visit_logical_expr(expr)
      left = evaluate(expr.left)[0]
      right = evaluate(expr.right)[0]
  
      case expr.operator.lexeme
      when '&&'
        left && right
      when '||'
        left || right
      else
        raise "Unsupported logical operator: #{expr.operator} \n\t On Line =[#{expr.operator.line}]"
      end
    end
  
    def visit_unary_expr(expr)
      right = evaluate(expr.right)[0]
  
      case expr.operator.lexeme
      when '-'
        -right
      when '!'
        !right
      else
        raise "Unsupported unary operator: #{expr.operator} \n\t On Line =[#{expr.operator.line}]"
      end
    end
  
    def visit_literal_expr(expr)
      [expr.value.to_s, "str", expr.value.object_id]
    end
  
    def visit_grouping_expr(expr)
      evaluate(expr.expression)
    end
  
    def visit_cmd_activation_expr(expr)
      _command_buffer_ = Shellwords.split(expr.value)
      inter = CmdInter.new(_command_buffer_)
      status = inter.impl
      "ascii says = [#{status[0]}], with Success Flag=[#{status[1]}] \n\t On Line =[#{status[1].line}]"
    end
  
    def interpret(stmt)
      @stmt = stmt
      if @stmt.is_a?(Array) # Handle multiple statements
        results = []
        @stmt.each do |expr|
          result = evaluate(expr)
          results << result
        end
        results
      else # Handle a single statement
        evaluate(@stmt)
      end
    end
  
    def evaluate(expr)
      return nil if expr.nil?
      expr.accept(self)
    end
  end
end