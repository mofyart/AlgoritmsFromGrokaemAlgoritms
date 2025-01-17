#include "ParentsHashMap.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

std::string FindLowestCostNode(std::vector<std::string> arrayProcessedElements, std::unordered_map<std::string, double> hashMapCost) {
    double lowestCost = INFINITY;
    std::string lowestCostElement = "";

    for (const auto& [node, cost] : hashMapCost) {
        if (cost < lowestCost && (std::find(begin(arrayProcessedElements), end(arrayProcessedElements), node) == end(arrayProcessedElements))) {
            lowestCost = cost;
            lowestCostElement = node;
        }
    }
    return lowestCostElement;
}

void FindMinDistance(std::unordered_map<std::string, std::unordered_map<std::string, int>>& hashMapGraph,
                     std::unordered_map<std::string, double>& hashMapCost, HashMapParents& hashMapParents) {
    std::vector<std::string> arrayProcessedElements;

    std::string lowestCostNode = FindLowestCostNode(arrayProcessedElements, hashMapCost);

    while (lowestCostNode != "") {
        double cost = hashMapCost[lowestCostNode];
        std::vector<std::string> neighborsNodes;

        for (const auto& [mainNode, hashMapSubsidiariesNodes] : hashMapGraph) {
            if (mainNode == lowestCostNode) {
                for (const auto& [node, cost] : hashMapSubsidiariesNodes) {
                    if (node != "") {
                        neighborsNodes.push_back(node);
                    }
                }
                break;
            }
        }

        for (auto checkElement : neighborsNodes) {
            double newCost = cost + hashMapGraph[lowestCostNode][checkElement];

            if (newCost < hashMapCost[checkElement]) {
                hashMapCost[checkElement] = newCost;

                hashMapParents.ChangeParentNode(checkElement, lowestCostNode);
            }
        }

        arrayProcessedElements.push_back(lowestCostNode);

        lowestCostNode = FindLowestCostNode(arrayProcessedElements, hashMapCost);
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::unordered_map<std::string, std::unordered_map<std::string, int>> hashMapGraph;
    std::unordered_map<std::string, double> hashMapCost;
    HashMapParents hashMapParents;

    hashMapParents.InitializeArray();

    hashMapGraph["start"]["a"] = 10;
    hashMapGraph["a"]["b"] = 20;
    hashMapGraph["b"]["c"] = 1;
    hashMapGraph["b"]["end"] = 30;
    hashMapGraph["c"]["a"] = 1;
    hashMapGraph["end"][""] = {};

    hashMapCost["a"] = 10;
    hashMapCost["b"] = INFINITY;
    hashMapCost["c"] = INFINITY;
    hashMapCost["end"] = INFINITY;

    hashMapParents.AddNewItem("a", "start");
    hashMapParents.AddNewItem("b", "");
    hashMapParents.AddNewItem("c", "");
    hashMapParents.AddNewItem("end", "");

    FindMinDistance(hashMapGraph, hashMapCost, hashMapParents);

    std::cout << "Минимальный путь: " << hashMapCost["end"] << std::endl;

    std::string namEndPunct = "end";
    std::cout << namEndPunct << ' ';

    bool beginPunct = false;

    while (!beginPunct) {
        std::cout << hashMapParents.GetItem(namEndPunct) << ' ';
        namEndPunct = hashMapParents.GetItem(namEndPunct);

        if (namEndPunct == "start") {
            beginPunct = true;
        }
    }

    return 0;
}
