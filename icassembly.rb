# Require all necessary files
require_relative 'LEXER'
require_relative 'PARSER'
require_relative 'INTERPRETER'
require_relative 'ENVIRONMENT'

class Main
  def initialize
    
    # Initialize the interpreter with the environment
    @interpreter = Interpreter.new()
  end

  # Method to run the pipeline
  def run(code)
    begin
      # Step 1: Lexical Analysis (Tokenization)
      lexer = Lexer.new(code)
      tokens = lexer.scan_tokens

      puts "Tokens : #{tokens}"
    #   # Step 2: Parsing (Abstract Syntax Tree Construction)
    #   parser = Parser.new(tokens)
    #   statements = parser.parse

    #   # Step 3: Interpretation (Execution)
    #   result = @interpreter.interpret(statements)

      # Output the result
      puts "Debug Interpreter Result"
    #   puts "Result: #{result}"
    rescue ThrowError => e
      puts "Error: #{e.message}"
    rescue StandardError => e
      puts "Unexpected error: #{e.message}"
    end
  end
end

# Entry point of the program
if __FILE__ == $0
  # Check if a file is provided as an argument
  if ARGV.empty?
    puts "Usage: ruby icassembly.rb <source_file>"
    exit(1)
  end

  # Read the source file
  source_file = ARGV[0]
  unless File.exist?(source_file)
    puts "Error: File '#{source_file}' not found."
    exit(1)
  end

  # Read the content of the file
  code = File.read(source_file)

  # Create and run the main pipeline
  main = Main.new
  main.run(code)
end