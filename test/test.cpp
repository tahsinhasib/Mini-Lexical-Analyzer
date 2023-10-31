#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {
    std::string filename = "textfile.txt"; // Replace with the name of your input file
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Error opening the file." << std::endl;
        return 1;
    }

    char c;
    std::string word;
    bool insideParentheses = false;

    while (file.get(c)) {
        if (insideParentheses) {
            if (c == ')') {
                insideParentheses = false;
                if (!word.empty()) {
                    std::cout << word << std::endl;
                    word.clear();
                }
            } else {
                word += c;
            }
        } else if (c == '(') {
            insideParentheses = true;
            if (!word.empty()) {
                std::cout << word << " ";
                word.clear();
            }
        }
    }

    file.close();

    return 0;
}
