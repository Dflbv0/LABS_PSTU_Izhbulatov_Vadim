#include <iostream>
using namespace std;

int main() {
    int a[] = {2, 4, 7, 11, 13, 19, 22};
    const int n = sizeof(a) / sizeof(a[0]);

    bool f = false;
    int i = 0;

    while (i < n - 1 && !f) {
        if (a[i] >= a[i + 1]) {
            f = true;
        } else {
            i++;
        }
    }

    if (f) {
        cout << "Массив не является строго возрастающим" << endl;
    } else {
        cout << "Массив является строго возрастающим" << endl;
    }
    return 0;
}
