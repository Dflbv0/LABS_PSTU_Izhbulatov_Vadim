#include <iostream>
using namespace std;

int main() {
    int a[] = {7, 2, 9, 4, 1, 6, 3};
    const int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n - 1; i++) {
        for (int j = n - 1; j > i; j--) {
            if (a[j] < a[j - 1]) {
                int temp = a[j];
                a[j] = a[j - 1];
                a[j - 1] = temp;
            }
        }

        cout << "Шаг " << i + 1 << ": ";
        for (int k = 0; k < n; k++) {
            cout << a[k] << " ";
        }
        cout << endl;
    }
    return 0;
}
