require 'set' # Add this line to import the Set class

class ThrowError < StandardError
  attr_accessor :message

  def initialize(message)
    super(message)
    @message = message
  end

  def to_s
    @message
  end
end

class Environment
  attr_accessor :values, :constants, :enclosing

  def initialize(enclosing = nil)
    @values = {}
    @constants = Set.new # To store names of constant variables
    @enclosing = enclosing
  end

  # Define method to store a variable
  def define(name, value, is_constant = false)
    if is_constant
      @constants.add(name)
    end
    @values[name] = value
  end

  # Get method to retrieve a variable's value
  def get(name)
    if @values.key?(name)
      return @values[name]
    end
    if @enclosing
      return @enclosing.get(name)
    end
    raise ThrowError.new("Undefined variable '#{name}'.")
  end

  # Check if a variable is defined
  def is_defined(name)
    if @values.key?(name)
      return true
    end
    if @enclosing
      return @enclosing.is_defined(name)
    end
    false
  end

  # Assign method to update a variable's value
  def assign(name, value)
    if @constants.include?(name)
      raise ThrowError.new("Cannot modify constant variable '#{name}'.")
    end

    if @values.key?(name)
      @values[name] = value
    elsif @enclosing
      @enclosing.assign(name, value)
    else
      raise ThrowError.new("Undefined variable '#{name}'.")
    end
  end
end