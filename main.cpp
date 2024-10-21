#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>
#include <unordered_map>  // For storing variables and their values

using namespace std;

// ---------------------- Base Class: Compiler ----------------------------
class Compiler {
public:
    virtual void process(const string& code) = 0;  // Pure virtual function for polymorphism
    virtual ~Compiler() {}  // Virtual destructor for proper cleanup
};

// ------------------- Derived Class: LexicalAnalyzer ---------------------
class LexicalAnalyzer : public Compiler {
public:
    void process(const string& code) override {
        cout << "Performing Lexical Analysis...\n";
        vector<string> tokens = tokenize(code);
        cout << "Tokens Identified: ";
        for (const string& token : tokens) {
            cout << token << " ";
        }
        cout << endl;
    }

private:
    vector<string> tokenize(const string& code) {
        regex word_regex(R"(print|\(|\)|\".*?\"|[a-zA-Z_][a-zA-Z0-9_]*|[+*/=;])");
        sregex_iterator words_begin = sregex_iterator(code.begin(), code.end(), word_regex);
        sregex_iterator words_end = sregex_iterator();
        vector<string> tokens;

        for (sregex_iterator i = words_begin; i != words_end; ++i) {
            tokens.push_back((*i).str());
        }

        return tokens;
    }
};

// ------------------- Derived Class: SyntaxValidator ---------------------
class SyntaxValidator : public Compiler {
public:
    void process(const string& code) override {
        cout << "Validating Syntax...\n";
        if (validateSyntax(code)) {
            cout << "Syntax is Valid!\n";
        } else {
            throw runtime_error("Syntax Error: Invalid statement detected!");
        }
    }

private:
    bool validateSyntax(const string& code) {
        if (code.find("print") != string::npos) {
            return code.find(';') != string::npos && code.find('(') != string::npos && code.find(')') != string::npos;
        }
        return code.back() == ';';
    }
};

// ------------------------ Symbol Table to Store Variables ----------------------
unordered_map<string, int> symbolTable;

// ------------------------ Function: Code Generation ----------------------
void generateCode(const string& code) {
    cout << "Generating Code...\n";

    // Handle print statements
    if (code.find("print") != string::npos) {
        size_t start = code.find('(') + 1;
        size_t end = code.find(')', start);
        string variableOrString = code.substr(start, end - start);

        // Remove any surrounding whitespace
        variableOrString.erase(remove(variableOrString.begin(), variableOrString.end(), ' '), variableOrString.end());

        // Check if it's a variable or a string literal
        if (variableOrString[0] == '\"' && variableOrString.back() == '\"') {
            // It's a string literal
            cout << "Compiled Output: " << variableOrString.substr(1, variableOrString.size() - 2) << endl;
        } else {
            // It's a variable, check if it exists in the symbol table
            if (symbolTable.find(variableOrString) != symbolTable.end()) {
                cout << "Compiled Output: " << symbolTable[variableOrString] << endl;
            } else {
                cerr << "Runtime Error: Variable '" << variableOrString << "' is not defined.\n";
            }
        }
    } else {
        // Handle variable declarations (e.g., int x = 5;)
        regex varDeclRegex(R"((int|float)\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([0-9]+)\s*;)");
        smatch match;
        if (regex_search(code, match, varDeclRegex)) {
            string varType = match[1];
            string varName = match[2];
            int value = stoi(match[3]);
            
            // Add variable to the symbol table
            symbolTable[varName] = value;
            cout << "Compiled Output: Variable '" << varName << "' assigned value " << value << endl;
        } else {
            cout << "Compiled Output: " << code.substr(0, code.size() - 1) << " executed successfully!\n";
        }
    }
}

// ------------------------ Main Function (Menu Driven) --------------------
int main() {
    LexicalAnalyzer lexicalAnalyzer;
    SyntaxValidator syntaxValidator;

    string code;
    vector<string> codeLines;
    cout << "Enter your code (type 'END' to finish):\n";

    // Input multiple lines of code
    while (true) {
        getline(cin, code);  // Get input code from user
        if (code == "END") break;  // End input on "END"
        codeLines.push_back(code);  // Store the input line
    }

    // Process each line of code
    for (const string& line : codeLines) {
        try {
            // Perform Lexical Analysis
            lexicalAnalyzer.process(line);

            // Perform Syntax Validation
            syntaxValidator.process(line);

            // Generate Code if everything is valid
            generateCode(line);
        } catch (const exception& e) {
            cerr << "Compilation Error: " << e.what() << endl;
        }
    }

    return 0;
}
