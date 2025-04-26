#pragma once
#include <vector>
#include <tuple>
#include <utility>

class Charger {
public:
    Charger();
    Charger(int id);

    void addReport(long long startTime, long long endTime, bool isAvailable);
    int getId() const;
    std::pair<long long, long long> getAvailableAndMonitoredSeconds(long long windowStart, long long now) const;

private:
    int id;
    std::vector<std::tuple<long long, long long, bool>> reports; // (start, end, available)
};
