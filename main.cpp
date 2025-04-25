#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream inputFile("test_data/input_1.txt");

    if (!inputFile.is_open()) {
        std::cerr << "❌ Error: Could not open input_1.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }

    inputFile.close();
    return 0;
}

