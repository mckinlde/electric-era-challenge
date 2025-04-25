#include <iostream>
#include <fstream>
#include <string>

enum class ParseMode {
    None,
    Stations,
    ChargerReports
};

int main() {
    std::ifstream inputFile("./test_data/input_1.txt");

    if (!inputFile.is_open()) {
        std::cerr << "❌ Error: Could not open input_1.txt" << std::endl;
        return 1;
    }

    ParseMode mode = ParseMode::None;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line == "[Stations]") {
            std::cout << "🔵 Found Stations section" << std::endl;
            mode = ParseMode::Stations;
            continue;
        }
        if (line == "[Charger Availability Reports]") {
            std::cout << "🟣 Found Charger Reports section" << std::endl;
            mode = ParseMode::ChargerReports;
            continue;
        }

        switch (mode) {
            case ParseMode::Stations:
                std::cout << "📦 Station Line: " << line << std::endl;
                break;
            case ParseMode::ChargerReports:
                std::cout << "🔧 Charger Report Line: " << line << std::endl;
                break;
            case ParseMode::None:
            default:
                std::cerr << "⚠️  Unexpected line outside sections: " << line << std::endl;
                break;
        }
    }

    inputFile.close();
    return 0;
}

