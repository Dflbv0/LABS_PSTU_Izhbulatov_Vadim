#include <iostream>
using namespace std;

int main() {
    int a[] = {7, 2, 9, 4, 1, 6, 3};
    const int n = sizeof(a) / sizeof(a[0]);

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }

        int temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;

        cout << "Шаг " << i + 1 << ": ";
        for (int k = 0; k < n; k++) {
            cout << a[k] << " ";
        }
        cout << endl;
    }
    return 0;
}
