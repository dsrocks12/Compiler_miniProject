This project is a simple compiler built using C++. The program simulates the behavior of a basic compiler that can:

Perform lexical analysis by tokenizing input code.
Validate syntax for basic statements such as variable declarations and print statements.
Generate code and execute print statements, including printing variable values and string literals.
The program allows multiple lines of input, and each line is processed separately to analyze, validate, and generate the desired output.

Features
-Lexical Analysis: Tokenizes each line of code to identify variables, operators, keywords (int, print), and literals.
-Syntax Validation: Checks for correct syntax, such as valid variable declarations and proper formatting of print statements.
-Code Generation:
    a.Print Statements: Supports printing both string literals and the values of declared variables.
    b.Variable Declarations: Supports simple variable declarations like int x = 10;, and stores variable values for later use.
-Multiple Line Support: Users can input multiple lines of code, and each line will be processed and executed in sequence.

How to Use
1. Input Format:
    a.Variable declarations: int <variable_name> = <value>;
    b.Print statements: print(<variable_name>); or print("Some String");
    c.End input by typing END.
