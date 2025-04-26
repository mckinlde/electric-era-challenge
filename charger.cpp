#include "charger.hpp"
#include <algorithm>

Charger::Charger() : id(-1) {}

Charger::Charger(int id) : id(id) {}

void Charger::addReport(long long startTime, long long endTime, bool isAvailable) {
    reports.emplace_back(startTime, endTime, isAvailable);
}

int Charger::getId() const {
    return id;
}

std::pair<long long, long long> Charger::getAvailableAndMonitoredSeconds(long long windowStart, long long now) const {
    if (reports.empty()) {
        return {0, 0};
    }

    auto sortedReports = reports;
    std::sort(sortedReports.begin(), sortedReports.end());

    long long firstReportStart = std::get<0>(sortedReports.front());
    long long lastReportEnd = std::get<1>(sortedReports.back());

    long long available = 0;
    long long monitored = 0;

    long long curTime = firstReportStart;

    for (const auto& [start, end, isAvailable] : sortedReports) {
        long long overlapStart = start;
        long long overlapEnd = end;

        if (curTime < overlapStart) {
            // downtime between curTime and overlapStart
            monitored += (overlapStart - curTime);
        }

        if (overlapStart < overlapEnd) {
            monitored += (overlapEnd - overlapStart);
            if (isAvailable) {
                available += (overlapEnd - overlapStart);
            }
            curTime = overlapEnd;
        }
    }

    return {available, monitored};
}
