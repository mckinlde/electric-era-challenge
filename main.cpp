#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "charger.hpp"

// Parsing states for input sections
enum class ParseMode {
    None,
    Stations,
    ChargerReports
};

// Print an error, output "ERROR" to stdout, and exit
void errorAndExit(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    std::cout << "ERROR" << std::endl;
    std::exit(1);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path-to-input-file>" << std::endl;
        std::cout << "ERROR" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "❌ Error: Could not open input file: " << argv[1] << std::endl;
        std::cout << "ERROR" << std::endl;
        return 1;
    }

    ParseMode mode = ParseMode::None;
    std::unordered_map<int, std::vector<int>> stationToChargers;
    std::unordered_map<int, Charger> chargersById;
    std::string line;
    long long latestTime = 0;

    // Parse the input file
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

    std::vector<std::pair<int, int>> stationUptimes;

    // Calculate uptime for each station
    for (const auto& [stationId, chargerIds] : stationToChargers) {
        long long stationAvailable = 0;
        long long stationMonitored = 0;

        for (int chargerId : chargerIds) {
    if (chargersById.find(chargerId) != chargersById.end()) {
        auto [available, monitored] = chargersById[chargerId].getAvailableAndMonitoredSeconds(latestTime - 7 * 86400, latestTime);
        if (monitored > 0) { // only include chargers that actually had events
            stationAvailable += available;
            stationMonitored += monitored;
        }
    }
}


        if (stationMonitored > 0) {
            int uptimeInt = static_cast<int>((stationAvailable * 100) / stationMonitored);
            stationUptimes.push_back({stationId, uptimeInt});
        } else {
            stationUptimes.push_back({stationId, 0});
        }
    }

    std::sort(stationUptimes.begin(), stationUptimes.end());

    // Output the final sorted results
    for (const auto& [stationId, uptime] : stationUptimes) {
        std::cout << stationId << " " << uptime << std::endl;
    }

    return 0;
}
