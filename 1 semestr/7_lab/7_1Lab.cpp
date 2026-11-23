#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
using namespace std;

struct Fraction {
    long long numerator, denominator;
};

// Точная запись конечной десятичной дроби без округления.
Fraction convert(const string& input) {
    size_t start = (input[0] == '-' || input[0] == '+') ? 1 : 0;
    string digits;
    bool point = false;
    size_t places = 0;
    for (size_t i = start; i < input.size(); ++i) {
        char c = input[i];
        if ((c == '.' || c == ',') && !point) {
            point = true;
        } else if (c >= '0' && c <= '9') {
            digits += c;
            if (point) ++places;
        } else throw invalid_argument("Некорректная десятичная дробь.");
    }
    if (digits.empty()) throw invalid_argument("Нет цифр.");
    while (places > 0 && digits.back() == '0') {
        digits.pop_back();
        --places;
    }
    size_t first = digits.find_first_not_of('0');
    if (first == string::npos) return {0, 1};
    digits.erase(0, first);
    if (digits.size() > 18 || places > 18)
        throw out_of_range("Превышен предел точного ввода (18 цифр).");

    long long p = stoll(digits), q = 1;
    for (size_t i = 0; i < places; ++i) q *= 10;
    long long divisor = gcd(p, q);
    return {(input[0] == '-' ? -p : p) / divisor, q / divisor};
}

long double convert(Fraction f) {
    if (f.denominator == 0)
        throw invalid_argument("Знаменатель равен нулю.");
    return static_cast<long double>(f.numerator) / f.denominator;
}

int main() {
    string decimal;
    Fraction fraction{};
    try {
        cout << "Введите десятичную дробь:\n";
        if (!(cin >> decimal)) return 1;
        Fraction result = convert(decimal);
        cout << result.numerator << '/' << result.denominator << '\n';
        cout << "Введите числитель и знаменатель через пробел:\n";
        if (!(cin >> fraction.numerator >> fraction.denominator)) return 1;
        long double value = convert(fraction);
        cout << setprecision(15) << value << '\n';
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
