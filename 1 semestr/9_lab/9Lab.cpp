#include <codecvt>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale>
#include <stdexcept>
#include <string>
using namespace std;

void createFile(int count) {
    ofstream out("F1.txt");
    if (!out) throw runtime_error("Не открыть F1.txt.");
    string line;
    for (int i = 0; i < count; ++i) {
        if (!getline(cin, line)) throw runtime_error("Недостаточно строк.");
        out << line << '\n';
    }
    out.close();
    if (!out) throw runtime_error("Ошибка записи F1.txt.");
}

void printFile(const char* path) {
    ifstream in(path);
    if (!in) throw runtime_error(string("Не открыть ") + path);
    string line;
    int n = 0;
    while (getline(in, line)) cout << ++n << ". " << line << '\n';
    if (in.bad()) throw runtime_error("Ошибка чтения.");
    if (n == 0) cout << "(пусто)\n";
}

void copyLines(int n1, int n2) {
    ifstream in("F1.txt");
    ofstream out("F2.txt");
    if (!in || !out) throw runtime_error("Не открыть F1.txt или F2.txt.");
    string line;
    int n = 0;
    while (getline(in, line)) {
        ++n;
        if (n1 < n && n < n2 && line.rfind("А", 0) == 0)
            out << line << '\n';
    }
    if (in.bad()) throw runtime_error("Ошибка чтения F1.txt.");
    out.close();
    if (!out) throw runtime_error("Ошибка записи F2.txt.");
}

int consonantCount(const string& line) {
    static const u32string letters =
        U"бвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
    wstring_convert<codecvt_utf8<char32_t>, char32_t> utf8;
    int count = 0;
    for (char32_t ch : utf8.from_bytes(line))
        if (letters.find(ch) != u32string::npos) ++count;
    return count;
}

void printMaximum() {
    ifstream in("F2.txt");
    if (!in) throw runtime_error("Не открыть F2.txt.");
    int n = 0, bestLine = 0, maximum = -1;
    string line;
    while (getline(in, line)) {
        ++n;
        int count = consonantCount(line);
        if (count > maximum) {
            maximum = count;
            bestLine = n;
        }
    }
    if (in.bad()) throw runtime_error("Ошибка чтения F2.txt.");
    if (bestLine == 0) cout << "В F2 нет подходящих строк.\n";
    else cout << "Строка F2: " << bestLine << ", согласных: "
              << maximum << '\n';
}

int main() {
    try {
        int count, n1, n2;
        cout << "Введите число строк F1 (не менее 10):\n";
        if (!(cin >> count) || count < 10) return 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите строки F1:\n";
        createFile(count);
        cout << "Содержимое F1:\n";
        printFile("F1.txt");
        cout << "Введите N1 и N2:\n";
        if (!(cin >> n1 >> n2) || n1 < 1 || n1 >= n2 || n2 > count)
            throw runtime_error("Требуется 1 <= N1 < N2 <= число строк.");
        copyLines(n1, n2);
        cout << "Содержимое F2:\n";
        printFile("F2.txt");
        printMaximum();
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
