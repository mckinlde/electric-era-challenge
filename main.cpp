#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "charger.hpp"

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
    std::unordered_map<int, std::vector<int>> stationToChargers; // station_id ➔ charger_ids
    std::unordered_map<int, Charger> chargersById; // charger_id ➔ Charger object
    std::string line;

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        if (line == "[Stations]") {
            mode = ParseMode::Stations;
            continue;
        }
        if (line == "[Charger Availability Reports]") {
            mode = ParseMode::ChargerReports;
            continue;
        }

        switch (mode) {
            case ParseMode::Stations: {
                std::istringstream iss(line);
                int stationId;
                iss >> stationId;

                int chargerId;
                while (iss >> chargerId) {
                    stationToChargers[stationId].push_back(chargerId);

                    // Create Charger object if it doesn't exist yet
                    if (chargersById.find(chargerId) == chargersById.end()) {
                        chargersById.emplace(chargerId, Charger(chargerId));
                    }
                }
                break;
            }
            case ParseMode::ChargerReports: {
                std::istringstream iss(line);
                int chargerId;
                long long startTime, endTime;
                bool isAvailable;

                iss >> chargerId >> startTime >> endTime >> std::boolalpha >> isAvailable;

                if (chargersById.find(chargerId) != chargersById.end()) {
                    chargersById[chargerId].addReport(startTime, endTime, isAvailable);
                } else {
                    std::cerr << "⚠️  Warning: Report for unknown charger ID " << chargerId << std::endl;
                }
                break;
            }
            case ParseMode::None:
            default:
                std::cerr << "⚠️  Unexpected line outside sections: " << line << std::endl;
                break;
        }
    }

    inputFile.close();

    // Debug output: list chargers and their report counts
    for (const auto& [chargerId, charger] : chargersById) {
        std::cout << "Charger ID: " << charger.getId() << std::endl;
    }

    return 0;
}
