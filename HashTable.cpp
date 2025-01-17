#include <iostream>
#include <cstring>

struct Item {
    std::string key = "";
    int value = 0;
};

struct HashMap {
    Item* elements;
    double capacity = 4;
    double count = 0;

    void Init() {
        this->elements = (Item*)malloc(sizeof(Item) * this->capacity);
    }

    int Hash(std::string key) {
        long sum = 0;

        for (size_t i = 0; i < key.length(); ++i) {
            sum+= key[i];
        }
        return sum;
    }

    void Reloc() {
        if (this->count / this->capacity * 100 >= 70) {
            this->elements = (Item*)std::realloc(NULL, sizeof(Item) * this->capacity * 2);
            capacity *= 2;
        }
    }

    void Add(std::string key, int value){
        Reloc();

        long hashed = Hash(key);

        if (this->elements[hashed].key != "") {
            int temp = hashed + 1;

            while (this->elements[temp].key != "") {
                ++temp;
            }

            this->elements[temp].key = key;
            this->elements[temp].value = value;
        } else {
            this->elements[hashed].key = key;
            this->elements[hashed].value = value;
        }

        ++count;

    }

    int Get(std::string key) {
        long hashed = Hash(key);

        if (this->elements[hashed].key == key) {
            return this->elements[hashed].value;
        } else {
            for (size_t i = hashed + 1; i < hashed + this->capacity; ++i) {
                if (this->elements[i].key== key) {
                    return this->elements[i].value;
                }
            }
        }
        return -1;
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {

    HashMap hashmap;

    hashmap.Init();

    hashmap.Add("net", 12);
    hashmap.Add("ten", 13);

    std::cout << hashmap.Get("net") << std::endl;

}
