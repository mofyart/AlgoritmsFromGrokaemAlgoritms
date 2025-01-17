#include <iostream>
#include <vector>
#include <cmath>

double FindBinary(std::vector<int> num, int element) {
    if (num.size() == 1) {
        return num[0];
    } else if (num.empty()){
        return NAN;
    }

    if (num[num.size() / 2 - 1] > element) {
        num.erase(num.cbegin() + (num.size() / 2 - 1) , num.cend());
    } else if (num[num.size() / 2 - 1] < element){
        num.erase(num.cbegin(), num.cend() - (num.size() - (num.size() / 2)));\
    } else if (num[num.size() / 2 - 1] == element) {
        return num[num.size() / 2 - 1] ;
    }

    return FindBinary(num, element);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    std::vector<int> num = {1, 2 , 4, 6, 7 ,8, 10, 13 , 89};

    int userElement{};
    std::cin >> userElement;

    if (FindBinary(num, userElement) == userElement) {
        std::cout << "Всё нашлось" ;
    } else {
        std::cout << "Не нашлось";
    }

    return 0;
}
