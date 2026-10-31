#include <iostream>
using namespace std;

int main() {
    int a[] = {7, 2, 9, 4, 1, 6, 3};
    const int n = sizeof(a) / sizeof(a[0]);

    for (int i = 1; i < n; i++) {
        int y = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > y) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = y;

        cout << "Шаг " << i << ": ";
        for (int k = 0; k < n; k++) {
            cout << a[k] << " ";
        }
        cout << endl;
    }
    return 0;
}
