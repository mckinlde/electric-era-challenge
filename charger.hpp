#pragma once
#include <vector>
#include <tuple>

class Charger {
public:
    Charger();
    Charger(int id);

    void addReport(long long startTime, long long endTime, bool isAvailable);
    double computeUptimeLast24h(long long now) const;
    double computeUptimeLast7d(long long now) const;

    int getId() const;

private:
    int id;
    std::vector<std::tuple<long long, long long, bool>> reports; // (start, end, available)

    double computeUptime(long long windowStart, long long now) const;
};
