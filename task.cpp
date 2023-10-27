#include <iostream>
#include <string.h>
#include <fstream>
#include <cctype>
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
    char operators[] = "+-*/%=<>&|^";
    for (char op : operators) {
        if (ch == op) {
            return true;
        }
    }
    return false;
}



void IdentifyKeywords(string cppKeywords[], int cppKeywordsSize) {
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
                            cout << word << ", ";
                            break;
                        }

                    }
                }
                word.clear();
            }
        }
    }
    ReadFile.close();
}



void IdentifyConstants() {
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

                    cout << word << "(string)" << ", ";
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
                    cout << word << "(integer)" << ", ";
                } 
                else if (isDouble(word)) {
                    cout << word << "(double)" << ", ";
                }
                else if (isCharacter(word)) {
                    cout << word << "(character)" << ", ";
                }
                word.clear();
            }
        }
    }
    ReadFile.close();
}


void IdentuifyOperators() {
    
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
    cout << "\n";
    IdentuifyOperators();
    

    return 0;
}