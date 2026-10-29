#include <iostream>
#include <string>
#include <unordered_map>

class UndergroundSystem {
private:
    struct CheckInInfo {
        std::string stationName;
        int time;
    };

    struct TripInfo {
        long long totalTime = 0;
        int count = 0;
    };

    std::unordered_map<int, CheckInInfo> checkInMap;
    std::unordered_map<std::string, TripInfo> tripStats;

public:
    UndergroundSystem() {}

    void checkIn(int id, std::string stationName, int t) {
        checkInMap[id] = {stationName, t};
    }

    void checkOut(int id, std::string stationName, int t) {
        if (checkInMap.find(id) != checkInMap.end()) {
            auto& entry = checkInMap[id];
            std::string route = entry.stationName + "#" + stationName;

            tripStats[route].totalTime += (t - entry.time);
            tripStats[route].count += 1;

            checkInMap.erase(id);
        }
    }

    double getAverageTime(std::string startStation, std::string endStation) {
        std::string route = startStation + "#" + endStation;
        auto& stats = tripStats[route];

        if (stats.count == 0) return 0.0;
        return static_cast<double>(stats.totalTime) / stats.count;
    }
};
