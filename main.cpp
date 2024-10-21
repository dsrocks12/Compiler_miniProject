#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <stdexcept>  // For exceptions
using namespace std;

// ---------------------- Base Class: Compiler ----------------------------
class Compiler {
public:
    // Virtual function for polymorphism
    virtual void process(const string& code) = 0;
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
        // Splitting code into tokens using regex (keywords, operators, identifiers)
        regex word_regex("[a-zA-Z_][a-zA-Z0-9_]*|[+*/=;]");
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
        // Basic validation: Check for missing semicolons
        return code.back() == ';';
    }
};

// ------------------------ Function: Code Generation ----------------------
void generateCode(const string& code) {
    cout << "Generating Code...\n";
    cout << "Compiled Output: " << code.substr(0, code.size() - 1) << " executed successfully!\n";
}

// ------------------------ Main Function (Menu Driven) --------------------
int main() {
    LexicalAnalyzer lexicalAnalyzer;
    SyntaxValidator syntaxValidator;

    string code;
    cout << "Enter your code (end with ';'): ";
    getline(cin, code);  // Get input code from user

    try {
        // Perform Lexical Analysis
        lexicalAnalyzer.process(code);

        // Perform Syntax Validation
        syntaxValidator.process(code);

        // Generate Code if everything is valid
        generateCode(code);
    } catch (const exception& e) {
        cerr << "Compilation Error: " << e.what() << endl;
    }

    return 0;
}
