#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

void FindStationsCoveringStates(std::unordered_map<std::string, std::set<std::string>> stationsInformation,
                                std::set<std::string> necessaryStatesCovered, std::set<std::string>& finalStations) {
    while (!necessaryStatesCovered.empty()) {
        std::string bestStation = "";
        std::set<std::string> maxStatesCoveredStation{};

        for (const auto& [nameStation, statesCoveredStation] : stationsInformation) {
            std::set<std::string> unificationMultiplesStations;

            for (const auto& stateCovered : statesCoveredStation) {
                for (const auto& necessaryStateCovered : necessaryStatesCovered) {
                    if (stateCovered == necessaryStateCovered) {
                        unificationMultiplesStations.insert(stateCovered);
                    }
                }
            }

            if (maxStatesCoveredStation.size() < unificationMultiplesStations.size()) {
                bestStation = nameStation;
                maxStatesCoveredStation = unificationMultiplesStations;
            }
        }
        finalStations.insert(bestStation);

        std::set<std::string> copyNecessaryStatesCovered = necessaryStatesCovered;

        for (const auto& stateCovered : maxStatesCoveredStation) {
            for (const auto& necessryStateCovered : necessaryStatesCovered) {
                if (stateCovered == necessryStateCovered) {
                    copyNecessaryStatesCovered.erase(stateCovered);
                }
            }
        }

        necessaryStatesCovered = copyNecessaryStatesCovered;
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::set<std::string> necessaryStatesCovered{"mt", "wa", "or", "id", "nv", "ut", "ca", "az"};
    std::set<std::string> finalStations{};

    std::unordered_map<std::string, std::set<std::string>> stationsInformation;

    stationsInformation["firstStation"] = {"id", "nv", "ut"};
    stationsInformation["secondStation"] = {"wa", "id", "mt"};
    stationsInformation["thirdStation"] = {"or", "nv", "ca"};
    stationsInformation["fourthStation"] = {"nv", "ut"};
    stationsInformation["fifthStation"] = {"ca", "az"};

    FindStationsCoveringStates(stationsInformation, necessaryStatesCovered, finalStations);

    for (auto station : finalStations) {
        std::cout << station << ' ';
    }

    return 0;
}
