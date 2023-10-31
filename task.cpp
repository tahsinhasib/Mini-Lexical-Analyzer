#include <iostream>
#include <string.h>
#include <fstream>
#include <cctype>
#include <set>
using namespace std;

// checking functions
bool isInt(string word) {
    if (word.empty()) {
        return false;
    }
    for (char ch : word) {
        if (!isdigit(ch) && ch != '-' && ch != '+') {
            return false;
        }
    }
    return true;
}
bool isCharacter(string word) {
    return word.size() == 3 && word.front() == '\'' && word.back() == '\'';
}
bool isString(string word) {
    return word.size() >= 2 && ((word.front() == '"' && word.back() == '"') || (word.front() == '\'' && word.back() == '\''));
}
bool isDouble(string word) {
    if (word.empty()) {
        return false;
    }
    bool hasDecimal = false;
    for (char ch : word) {
        if (!isdigit(ch) && ch != '-' && ch != '+' && ch != '.') {
            return false;
        }
        if (ch== '.') {
            if (hasDecimal) {
                return false; // More than one decimal point
            }
            hasDecimal = true;
        }
    }
    return hasDecimal;
}
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch== '%' || ch == '=' || ch == '<' || ch == '>');
}
bool isPunctuation(char ch) {
    return (ch == '!' || ch ==  '"' || ch == '#' || ch == '$' ||  
            ch == '%' || ch == '&' || ch == '(' || ch == ')' || 
            ch == '*' || ch == '+' || ch == ',' || ch == '-' || 
            ch == '.' || ch == '/' || ch == ':' || ch == ';' ||
            ch == '<' || ch == '=' || ch == '>' || ch == '?' ||
            ch == '@' || ch == '[' || ch == ']' ||
            ch == '^' || ch == '_' || ch == '`' || ch == '{' ||
            ch == '|' || ch == '}' || ch == '~');
}
bool isWhitespace(char ch) {
    return (ch == ' ' || ch == '\t' || ch == '\n');
}
bool isVariable(string word) {
    return (word == "int" || word == "float" || word == "char" || word == "string" || word == "double" || word == "bool");
}


// function for detecting cpp keywords
void IdentifyKeywords(string cppKeywords[], int cppKeywordsSize) {
    set<string> keywordsset;
    string str; ifstream ReadFile("files/src.txt");

    while (getline(ReadFile, str)) {
        string word;

        for (char ch : str) {
            if (isalnum(ch) || ch == '_') {
                word += ch;
            }
            else if (!word.empty()) {
                for (int i = 0; i < cppKeywordsSize; i++)  {
                    string key = cppKeywords[i];

                    if (word.size() == key.size()) {
                        bool isKeyword = true;

                        for (int j = 0; j < word.size(); j++) {
                            if (tolower(word[j]) != key[j]) {
                                isKeyword = false;
                                break;
                            }
                        }
                        if (isKeyword) {
                            //cout << word << ", ";
                            keywordsset.insert(word);
                            break;
                        }

                    }
                }
                word.clear();
            }
        }
    }
    for (string i : keywordsset) {
        cout << i << ", ";
    }
    ReadFile.close();
}
// function for detecting cpp constants
void IdentifyConstants() {
    set<string> constantsset;
    string str; ifstream ReadFile("files/src.txt"); 

    while (getline(ReadFile, str)) {
        string word;
        bool inString = false; // Track if we are inside a string literal

        for (char ch : str) {
            if (inString) {
                word += ch;

                // Check if we've reached the end of a string literal
                if (ch == '"' || ch == '\'') {
                    inString = false;

                    //cout << word << "(string)" << ", ";
                    constantsset.insert(word);
                    word.clear();
                }
            } 
            else if (isdigit(ch) || ch == '-' || ch == '+' || ch == '.') {
                word += ch;
            } 
            else if (isalnum(ch)) {
                word += ch;
            } 
            else if (ch == '"' || ch == '\'') {
                inString = true;
                word += ch;
            } 
            else if (!word.empty()) {
                if (isInt(word)) {
                    //cout << word << "(integer)" << ", ";
                    constantsset.insert(word);
                } 
                else if (isDouble(word)) {
                    //cout << word << "(double)" << ", ";
                    constantsset.insert(word);
                }
                else if (isCharacter(word)) {
                    //cout << word << "(character)" << ", ";
                    constantsset.insert(word);
                }
                word.clear();
            }
        }
    }
    for (string i : constantsset) {
        cout << i << ", ";
    }
    ReadFile.close();
}
// function for detecting cpp operators
void IdentifyOperators() {
    set<string> operatorsset;
    ifstream ReadFile("files/src.txt"); 

    char ch;
    string currentOperator;
    bool insideString = false;
    
    while (ReadFile.get(ch)) {
        // Check if we are inside a string
        if (ch == '\"') {
            insideString = !insideString;
        }
        // If not inside a string, check for operators
        if (!insideString && isOperator(ch)) {
            currentOperator += ch;
        } 
        else {
            // If we were accumulating an operator, print it
            if (!currentOperator.empty()) {
                //cout << currentOperator << " ";
                operatorsset.insert(currentOperator);
                currentOperator.clear();
            }
        }
    }
    for (string i : operatorsset) {
        cout << i << ", ";
    }
    ReadFile.close();
}
// function for detecting cpp punctuation
void IdentifyPunctuation() {
    set<string> punctuationsset;
    ifstream ReadFile("files/src.txt"); 

    char ch;
    string currentPunctuation;
    bool insideString = false;
    
    while (ReadFile.get(ch)) {
        // Check if we are inside a string
        if (ch == '\"') {
            insideString = !insideString;
        }
        // If not inside a string, check for operators
        if (!insideString && isPunctuation(ch)) {
            currentPunctuation += ch;
        } 
        else {
            // If we were accumulating an operator, print it
            if (!currentPunctuation.empty()) {
                //cout << currentPunctuation << " ";
                punctuationsset.insert(currentPunctuation);
                currentPunctuation.clear();
            }
        }
    }
    for (string i : punctuationsset) {
        cout << i << ", ";
    }
    ReadFile.close();
}
// function for detecting cpp identifiers
void IdentifyIdentifiers() {
    set<string> identifiersset;
    ifstream ReadFile("files/src.txt");

    char ch;
    string word;
    bool foundVariable = false;

    while (ReadFile.get(ch)) {
        if (!isWhitespace(ch)) {
            word += ch;
        } 
        else {
            if (foundVariable && !word.empty()) {
                //cout << word << " ";
                identifiersset.insert(word);
            }
            if (isVariable(word)) {
                foundVariable = true;
            } 
            else {
                foundVariable = false;
            }
            word.clear();
        }
    }
    for (string i : identifiersset) {
        cout << i << ", ";
    }
    ReadFile.close();
}

int main()
{
    string cppKeywords[] = {"alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand", "bitor",
                            "bool", "break", "case", "catch", "char", "char8_t", "char16_t", "char32_t",
                            "class", "compl", "concept", "const", "consteval", "constexpr", "constinit",
                            "const_cast", "continue", "co_await", "co_return", "co_yield", "decltype", "default",
                            "delete", "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
                            "extern", "false", "float", "for", "friend", "goto", "if", "inline", "int", "long",
                            "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator",
                            "or", "or_eq", "private", "protected", "public", "register", "reinterpret_cast",
                            "requires", "return", "short", "signed", "sizeof", "static", "static_assert",
                            "static_cast", "struct", "switch", "template", "this", "thread_local", "throw",
                            "true", "try", "typedef", "typeid", "typename", "union", "unsigned", "using",
                            "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"};
    int cppKeywordsSize = sizeof(cppKeywords)/sizeof(cppKeywords[0]);
    
    cout << "\nKeywords: ";
    IdentifyKeywords(cppKeywords, cppKeywordsSize);
    cout << "\nConstants: ";
    IdentifyConstants();
    cout << "\nOperators: ";
    IdentifyOperators();
    cout << "\nPunctuation: ";
    IdentifyPunctuation();   
    cout << "\nIdentifiers: ";
    IdentifyIdentifiers();

    return 0;
}