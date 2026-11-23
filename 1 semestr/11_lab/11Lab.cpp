#include <algorithm>
#include <codecvt>
#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale>
#include <stdexcept>
#include <string>
using namespace std;

struct Node {
    char* key;
    Node* prev = nullptr;
    Node* next = nullptr;

    explicit Node(const string& text) : key(new char[text.size() + 1]) {
        strcpy(key, text.c_str());
    }
    ~Node() { delete[] key; }
};

struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    List() = default;
    List(const List&) = delete;
    List& operator=(const List&) = delete;
    ~List() { clear(); }

    void insertAfter(Node* left, const string& key) {
        Node* node = new Node(key);
        Node* right = left ? left->next : head;
        node->prev = left;
        node->next = right;
        if (left) left->next = node;
        else head = node;
        if (right) right->prev = node;
        else tail = node;
    }

    void popFront() {
        Node* old = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete old;
    }

    void removeFirst(int k) {
        while (k > 0 && head) {
            popFront();
            --k;
        }
    }

    void clear() {
        while (head) popFront();
    }

    bool insertByInitial(const string& letter, const string& value) {
        for (Node* p = head; p; p = p->next) {
            if (strncmp(p->key, letter.c_str(), letter.size()) == 0) {
                insertAfter(p, value);
                return true;
            }
        }
        return false;
    }

    void print() const {
        if (!head) cout << "Список пустой\n";
        for (Node* p = head; p; p = p->next)
            cout << p->key << (p->next ? " <-> " : "\n");
    }

    void save(const string& path) const {
        ofstream out(path);
        if (!out) throw runtime_error("Не открыть файл для записи.");
        for (Node* p = head; p; p = p->next) out << p->key << '\n';
        out.close();
        if (!out) throw runtime_error("Ошибка записи.");
    }

    void load(const string& path) {
        ifstream in(path);
        if (!in) throw runtime_error("Не открыть файл для чтения.");
        List restored;
        string key;
        while (getline(in, key)) restored.insertAfter(restored.tail, key);
        if (in.bad()) throw runtime_error("Ошибка чтения.");
        swap(head, restored.head);
        swap(tail, restored.tail);
    }
};

string readLine() {
    string line;
    if (!getline(cin, line)) throw runtime_error("Ошибка ввода строки.");
    return line;
}

void createList(List& list, int count) {
    for (int i = 0; i < count; ++i) list.insertAfter(list.tail, readLine());
}

int main() {
    try {
        List list;
        int count, k;
        cout << "Число узлов и далее по одному ключу на строку:\n";
        if (!(cin >> count) || count < 0) return 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        createList(list, count);
        cout << "Исходный список:\n";
        list.print();
        cout << "Сколько первых узлов удалить?\n";
        if (!(cin >> k) || k < 0) return 1;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        list.removeFirst(k);
        cout << "После удаления:\n";
        list.print();

        cout << "Введите начальный символ, затем ключ с новой строки:\n";
        string initial = readLine();
        wstring_convert<codecvt_utf8<char32_t>, char32_t> utf8;
        if (utf8.from_bytes(initial).size() != 1)
            throw runtime_error("Требуется один символ.");
        string key = readLine();
        if (!list.insertByInitial(initial, key))
            cout << "Узел с таким начальным символом не найден.\n";
        cout << "После поиска и вставки:\n";
        list.print();

        list.save("list.txt");
        list.clear();
        cout << "После уничтожения:\n";
        list.print();
        list.load("list.txt");
        cout << "Восстановленный список:\n";
        list.print();
        list.clear();
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
