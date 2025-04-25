#include "charger.hpp"

Charger::Charger() : id(-1) {}  // Default constructor, sets id to invalid -1

Charger::Charger(int id) : id(id) {}

void Charger::addReport(long long startTime, long long endTime, bool isAvailable) {
    reports.emplace_back(startTime, endTime, isAvailable);
}

int Charger::getId() const {
    return id;
}
