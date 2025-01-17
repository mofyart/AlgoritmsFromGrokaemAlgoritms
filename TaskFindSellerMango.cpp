#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>

namespace {
const size_t kGrouthFactor = 2;

const int kMaxProcent = 100;

const int kMaxAcceptableProcent = 70;
}  // namespace

struct Person {
    std::string name = "";
    std::string* namesNeighbors{};

    bool sellerMango = false;
    bool checking = false;
};

struct HashMap {
    Person* arrayPersons{};
    int capacity = 3;
    int count = 0;

    void InitializeArray() { this->arrayPersons = new Person[this->capacity]; }

    void ChangeChecking(std::string name) {
        int hashedIndex = HashElement(name);

        if (this->arrayPersons[hashedIndex].name == name) {
            this->arrayPersons[hashedIndex].checking = true;
        } else {
            for (int i = hashedIndex + 1; i < hashedIndex + this->capacity - 1; ++i) {
                if (this->arrayPersons[i % this->capacity].name == name) {
                    this->arrayPersons[i % this->capacity].checking = true;
                }
            }
        }
    }

    int HashElement(std::string name) {
        int sum = 0;

        for (size_t i = 0; i < name.length(); ++i) {
            int element = static_cast<int>(i);
            sum += name[i] * (element + 1);
        }

        return sum % this->capacity;
    }

    void ReinitializeHashTable() {
        if (this->count / this->capacity * kMaxProcent >= kMaxAcceptableProcent) {
            Person* newArrayPersons = new Person[this->capacity * kGrouthFactor];
            Person* oldArrayPersons = this->arrayPersons;

            std::copy(this->arrayPersons, this->arrayPersons + this->count, newArrayPersons);

            this->arrayPersons = newArrayPersons;
            this->capacity *= kGrouthFactor;

            delete[] oldArrayPersons;
        }
    }

    void AddNewPerson(std::string name, std::string* namesNeighbors, bool sellerMango) {
        ReinitializeHashTable();

        int hashedIndex = HashElement(name);
        if (this->arrayPersons[hashedIndex].name != "") {
            int newCount = (hashedIndex == (this->capacity - 1)) ? 0 : hashedIndex + 1;

            while (this->arrayPersons[newCount].name != "") {
                if (newCount == (this->capacity - 1)) {
                    newCount = -1;
                }
                ++newCount;
            }

            this->arrayPersons[newCount].name = name;
            this->arrayPersons[newCount].namesNeighbors = namesNeighbors;
            this->arrayPersons[newCount].sellerMango = sellerMango;
        } else {
            this->arrayPersons[hashedIndex].name = name;
            this->arrayPersons[hashedIndex].namesNeighbors = namesNeighbors;
            this->arrayPersons[hashedIndex].sellerMango = sellerMango;
        }

        ++this->count;
    }

    Person GetPerson(std::string name) {
        int hashedIndex = HashElement(name);

        if (this->arrayPersons[hashedIndex].name == name) {
            return arrayPersons[hashedIndex];
        } else {
            for (int i = hashedIndex + 1; i < hashedIndex + this->capacity - 1; ++i) {
                if (this->arrayPersons[i % this->capacity].name == name) {
                    return this->arrayPersons[i % this->capacity];
                }
            }
        }
        return {.name = " "};
    }
};

void FindMango(std::string finder, HashMap& hashMap) {
    std::queue<std::string> persons;

    persons.push(finder);

    while (!persons.empty()) {
        std::string individ = persons.front();
        Person pers = hashMap.GetPerson(individ);

        if (pers.checking == false) {
            if (pers.sellerMango == true) {
                std::cout << "Мы нашли продавца манго: " << pers.name << std::endl;
                return;
            }

            hashMap.ChangeChecking(pers.name);

            if (pers.namesNeighbors == nullptr) {
                continue;
            }

            for (size_t i = 0; i < 2; ++i) {
                persons.push(pers.namesNeighbors[i]);
            }
        }
        persons.pop();
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    HashMap hashMap;

    hashMap.InitializeArray();

    std::string arrayNeighborsFirst[2] = {"Andrey", "Leha"};
    hashMap.AddNewPerson("Artem", arrayNeighborsFirst, false);

    std::string arrayNeighborsSecond[2] = {"Leha", "dom"};
    hashMap.AddNewPerson("Andrey", arrayNeighborsSecond, false);

    std::string arrayNeighborsThird[2] = {"Sasha", "Timur"};
    hashMap.AddNewPerson("Leha", arrayNeighborsThird, false);

    std::string arrayNeighborsFourth[2] = {"Ilia", "Ahe"};
    hashMap.AddNewPerson("Arina", arrayNeighborsFourth, false);

    std::string* six = {};
    hashMap.AddNewPerson("dom", six, true);

    std::string arrayNeighborsFives[2] = {"Egor", "Pasha"};
    hashMap.AddNewPerson("Sasha", arrayNeighborsFives, false);

    FindMango("Artem", hashMap);

    return 0;
}
