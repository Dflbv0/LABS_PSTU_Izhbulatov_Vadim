#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <string>
using namespace std;

string toTernary(int number) {
    long long value = number;
    if (value < 0) value = -value;
    string digits;
    do {
        digits += static_cast<char>('0' + value % 3);
        value /= 3;
    } while (value > 0);
    if (number < 0) digits += '-';
    reverse(digits.begin(), digits.end());
    return digits;
}

template<class... Rest>
void printTernary(int first, Rest... rest) {
    for (int number : {first, rest...})
        cout << number << " -> " << toTernary(number) << '\n';
    cout << '\n';
}

int main() {
    printTernary(0, 1, 2);
    printTernary(3, 4, 8, 9);
    printTernary(-10, 10, 13, 26, 27, 28, 81);
}
