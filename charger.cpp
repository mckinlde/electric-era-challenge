#include "charger.hpp"

Charger::Charger() : id(-1) {}

Charger::Charger(int id) : id(id) {}

void Charger::addReport(long long startTime, long long endTime, bool isAvailable) {
    reports.emplace_back(startTime, endTime, isAvailable);
}

int Charger::getId() const {
    return id;
}

std::pair<long long, long long> Charger::getAvailableAndMonitoredSeconds(long long windowStart, long long now) const {
    long long available = 0;
    long long monitored = 0;

    for (const auto& [start, end, isAvailable] : reports) {
        if (end < windowStart || start > now) continue;

        long long overlapStart = std::max(start, windowStart);
        long long overlapEnd = std::min(end, now);

        if (overlapStart < overlapEnd) {
            long long duration = overlapEnd - overlapStart;
            monitored += duration;
            if (isAvailable) {
                available += duration;
            }
        }
    }

    return {available, monitored};
}
