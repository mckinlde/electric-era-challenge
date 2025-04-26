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

// Returns (available seconds, monitored seconds) for a charger in the window [windowStart, now]
// Monitoring only spans from the first report to the last report
// Downtime is assumed between gaps and after the last report
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
            // downtime between last curTime and next report start
            monitored += (overlapStart - curTime);
        }

        if (overlapStart < overlapEnd) {
            long long duration = overlapEnd - overlapStart;
            monitored += duration;
            if (isAvailable) {
                available += duration;
            }
            curTime = overlapEnd;
        }
    }

    return {available, monitored};
}
