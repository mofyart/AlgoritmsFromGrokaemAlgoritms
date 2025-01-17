#include <algorithm>
#include <iostream>
#include <string>

void FindTheLongestOverallSequence(int** tableDynamicCoding, std::string wordInputUser) {
    for (size_t i = 1; i < wordInputUser.length() + 1; ++i) {
        for (size_t j = 1; j < wordInputUser.length() + 1; ++j) {
            if (tableDynamicCoding[i][0] == tableDynamicCoding[0][j]) {
                tableDynamicCoding[i][j] = tableDynamicCoding[i - 1][j - 1] + 1;
            } else {
                if (i == 1) {
                    tableDynamicCoding[i][j] = tableDynamicCoding[i][j - 1];
                } else if (j == 1) {
                    tableDynamicCoding[i][j] = tableDynamicCoding[i - 1][j];
                } else {
                    tableDynamicCoding[i][j] = std::max(tableDynamicCoding[i - 1][j], tableDynamicCoding[i][j - 1]);
                }
            }
        }
    }

    std::cout << "Самая длинная общая последовательность: " << tableDynamicCoding[wordInputUser.length()][wordInputUser.length()];
    std::cout << std::endl;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::cout << "Введите слово, которое хотите проверить" << std::endl;
    std::string wordInputUser;
    std::cin >> wordInputUser;

    std::string trueWord = "fish";

    int** tableDynamicCoding = new int*[wordInputUser.length() + 1];

    for (size_t i = 0; i < wordInputUser.length() + 1; ++i) {
        tableDynamicCoding[i] = new int[wordInputUser.length() + 1];
    }

    for (size_t i = 1; i < wordInputUser.length() + 1; ++i) {
        tableDynamicCoding[0][i] = wordInputUser[i - 1];
        tableDynamicCoding[i][0] = trueWord[i - 1];
    }
    tableDynamicCoding[0][0] = 0;

    FindTheLongestOverallSequence(tableDynamicCoding, wordInputUser);

    for (size_t i = 0; i < wordInputUser.length() + 1; ++i) {
        for (size_t j = 0; j < wordInputUser.length() + 1; ++j) {
            std::cout << tableDynamicCoding[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
