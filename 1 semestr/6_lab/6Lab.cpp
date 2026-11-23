#include <algorithm>
#include <codecvt>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <string>
using namespace std;

const u32string upper =
    U"ABCDEFGHIJKLMNOPQRSTUVWXYZАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
const u32string lower =
    U"abcdefghijklmnopqrstuvwxyzабвгдеёжзийклмнопрстуфхцчшщъыьэюя";

size_t rankOf(char32_t c) {
    size_t pos = lower.find(c);
    return pos == u32string::npos ? upper.find(c) : pos;
}

void sortWord(u32string& text, size_t first, size_t end) {
    u32string letters;
    for (size_t i = first; i < end; ++i)
        if (rankOf(text[i]) != u32string::npos)
            letters += text[i];
    stable_sort(letters.begin(), letters.end(),
                [](char32_t a, char32_t b) {
                    return rankOf(a) < rankOf(b);
                });
    size_t j = 0;
    for (size_t i = first; i < end; ++i)
        if (rankOf(text[i]) != u32string::npos)
            text[i] = letters[j++];
}

int main() {
    cout << "Введите строку с точкой в конце (до 255 символов):\n";
    string input;
    if (!getline(cin, input)) return 1;
    wstring_convert<codecvt_utf8<char32_t>, char32_t> utf8;
    try {
        u32string text = utf8.from_bytes(input);
        if (text.empty() || text.size() > 255 || text.back() != U'.') {
            cerr << "Нужна строка до 255 символов с точкой в конце.\n";
            return 1;
        }
        size_t first = 0;
        for (size_t i = 0; i < text.size(); ++i) {
            if (text[i] == U' ' || i + 1 == text.size()) {
                sortWord(text, first, i);
                first = i + 1;
            }
        }
        cout << utf8.to_bytes(text) << '\n';
    } catch (const range_error&) {
        cerr << "Ожидается текст в кодировке UTF-8.\n";
        return 1;
    }
}
