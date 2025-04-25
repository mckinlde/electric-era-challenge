#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "charger.hpp"

enum class ParseMode {
    None,
    Stations,
    ChargerReports
};

void errorAndExit(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    std::cout << "ERROR" << std::endl;
    std::exit(1);
}

int main() {
    std::ifstream inputFile("./test_data/input_1.txt");

    if (!inputFile.is_open()) {
        errorAndExit("Could not open input file");
    }

    ParseMode mode = ParseMode::None;
    std::unordered_map<int, std::vector<int>> stationToChargers;
    std::unordered_map<int, Charger> chargersById;
    std::string line;
    long long latestTime = 0;

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
                if (!(iss >> stationId)) {
                    errorAndExit("Invalid station line: " + line);
                }

                int chargerId;
                bool hasCharger = false;
                while (iss >> chargerId) {
                    hasCharger = true;
                    stationToChargers[stationId].push_back(chargerId);
                    if (chargersById.find(chargerId) == chargersById.end()) {
                        chargersById.emplace(chargerId, Charger(chargerId));
                    }
                }
                if (!hasCharger) {
                    errorAndExit("Station without chargers: " + line);
                }
                break;
            }
            case ParseMode::ChargerReports: {
                std::istringstream iss(line);
                int chargerId;
                long long startTime, endTime;
                bool isAvailable;

                if (!(iss >> chargerId >> startTime >> endTime >> std::boolalpha >> isAvailable)) {
                    errorAndExit("Invalid charger report line: " + line);
                }

                if (startTime >= endTime) {
                    errorAndExit("Start time must be before end time: " + line);
                }

                if (chargersById.find(chargerId) != chargersById.end()) {
                    chargersById[chargerId].addReport(startTime, endTime, isAvailable);
                    latestTime = std::max(latestTime, endTime);
                } else {
                    errorAndExit("Report for unknown charger ID: " + std::to_string(chargerId));
                }
                break;
            }
            case ParseMode::None:
            default:
                errorAndExit("Unexpected line outside sections: " + line);
                break;
        }
    }
    inputFile.close();

    // (Station rollup and output will come next, this just parses and validates)
    return 0;
}
