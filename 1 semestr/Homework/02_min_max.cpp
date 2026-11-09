#include <iostream>
using namespace std;

int main() {
    int a[] = {8, -5, 3, 12, -5, 12, 0, 12, -5, 4};
    const int n = sizeof(a) / sizeof(a[0]);

    int mn = a[0], mx = a[0];
    int minIndex = 0, maxIndex = 0;
    int minCount = 1, maxCount = 1;

    for (int i = 1; i < n; i++) {
        if (a[i] < mn) {
            mn = a[i];
            minIndex = i;
            minCount = 1;
        } else if (a[i] == mn) {
            minCount++;
        }

        if (a[i] > mx) {
            mx = a[i];
            maxIndex = i;
            maxCount = 1;
        } else if (a[i] == mx) {
            maxCount++;
        }
    }

    cout << "Минимум = " << mn << endl;
    cout << "Индекс первого минимума = " << minIndex << endl;
    cout << "Номер первого минимума = " << minIndex + 1 << endl;
    cout << "Количество минимумов = " << minCount << endl;

    cout << "Максимум = " << mx << endl;
    cout << "Индекс первого максимума = " << maxIndex << endl;
    cout << "Номер первого максимума = " << maxIndex + 1 << endl;
    cout << "Количество максимумов = " << maxCount << endl;
    return 0;
}
