#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

namespace {
const size_t kGrouthFactor = 2;

const int kMaxProcent = 100;

const int kMaxAcceptableProcent = 70;
}  // namespace

struct Item {
    std::string namenNode = "";
    std::string nameParentNode = "";
};

struct HashMapParents {
    Item* arrayItems{};
    int capacity = 3;
    int count = 0;

    void InitializeArray() { this->arrayItems = new Item[this->capacity]; }

    int HashElement(std::string name) {
        int sum = 0;

        for (int i = 0; i < name.length(); ++i) {
            sum += name[i] * (i + 1);
        }

        return sum % this->capacity;
    }

    void ReinitializeHashTable() {
        if (this->count / this->capacity * kMaxProcent >= kMaxAcceptableProcent) {
            Item* newArrayItems = new Item[this->capacity * kGrouthFactor];
            Item* oldArrayItems = this->arrayItems;

            std::copy(this->arrayItems, this->arrayItems + this->count, newArrayItems);

            this->arrayItems = newArrayItems;
            this->capacity *= kGrouthFactor;

            delete[] oldArrayItems;
        }
    }

    void AddNewItem(std::string namenNode, std::string nameParentNode) {
        ReinitializeHashTable();

        int hashedIndex = HashElement(namenNode);
        if (this->arrayItems[hashedIndex].namenNode != "") {
            int newCount = (hashedIndex == (this->capacity - 1)) ? 0 : hashedIndex + 1;

            while (this->arrayItems[newCount].namenNode != "") {
                if (newCount == (this->capacity - 1)) {
                    newCount = -1;
                }
                ++newCount;
            }

            this->arrayItems[newCount].namenNode = namenNode;
            this->arrayItems[newCount].nameParentNode = nameParentNode;
        } else {
            this->arrayItems[hashedIndex].namenNode = namenNode;
            this->arrayItems[hashedIndex].nameParentNode = nameParentNode;
        }

        ++this->count;
    }

    std::string GetItem(std::string namenNode) {
        int hashedIndex = HashElement(namenNode);

        if (this->arrayItems[hashedIndex].namenNode == namenNode) {
            return this->arrayItems[hashedIndex].nameParentNode;
        } else {
            for (int i = hashedIndex + 1; i < hashedIndex + this->capacity; ++i) {
                if (this->arrayItems[i % this->capacity].namenNode == namenNode) {
                    return this->arrayItems[i % this->capacity].nameParentNode;
                }
            }
        }
        return "";
    }

    void ChangeParentNode(std::string nameNode, std::string newParent) {
        int hashedIndex = HashElement(nameNode);

        if (this->arrayItems[hashedIndex].namenNode == nameNode) {
            this->arrayItems[hashedIndex].nameParentNode = newParent;
        } else {
            for (size_t i = 0; i < hashedIndex + this->capacity; ++i) {
                if (this->arrayItems[i % this->capacity].namenNode == nameNode) {
                    this->arrayItems[i % this->capacity].nameParentNode = newParent;
                }
            }
        }
    }
};
