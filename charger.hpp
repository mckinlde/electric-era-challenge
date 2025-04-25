// Charger.hpp

#pragma once
#include <vector>
#include <tuple>

class Charger {
public:
    Charger(int id);

    void addReport(long long startTime, long long endTime, bool isAvailable);

    int getId() const;

private:
    int id;
    std::vector<std::tuple<long long, long long, bool>> reports; // (start_time, end_time, is_available)
};
