#include "charger.hpp"

const long long SECONDS_IN_DAY = 86400;
const long long SECONDS_IN_WEEK = 7 * 86400;

Charger::Charger() : id(-1) {}

Charger::Charger(int id) : id(id) {}

void Charger::addReport(long long startTime, long long endTime, bool isAvailable) {
    reports.emplace_back(startTime, endTime, isAvailable);
}

int Charger::getId() const {
    return id;
}

double Charger::computeUptimeLast24h(long long now) const {
    return computeUptime(now - SECONDS_IN_DAY, now);
}

double Charger::computeUptimeLast7d(long long now) const {
    return computeUptime(now - SECONDS_IN_WEEK, now);
}

double Charger::computeUptime(long long windowStart, long long now) const {
    if (reports.empty() || windowStart >= now) return 0.0;

    long long availableTime = 0;
    for (const auto& [start, end, isAvailable] : reports) {
        if (end < windowStart || start > now) continue;

        long long overlapStart = std::max(start, windowStart);
        long long overlapEnd = std::min(end, now);

        if (overlapStart < overlapEnd && isAvailable) {
            availableTime += (overlapEnd - overlapStart);
        }
    }

    long long totalWindow = now - windowStart;
    if (totalWindow <= 0) return 0.0;

    return (availableTime * 100.0) / totalWindow;
}
