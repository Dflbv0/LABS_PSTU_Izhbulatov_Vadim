#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int rows = 2;
    const int cols = 5;
    int a[rows][cols] = {
        {12, -4, 7, 15, -8},
        {-3, 11, 20, -5, 6}
    };
    int sum[rows] = {0};

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            sum[i] += a[i][j];
        }
    }

    cout << "Матрица:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(6) << right << a[i][j];
        }
        cout << endl;
    }

    cout << "Суммы строк:" << endl;
    for (int i = 0; i < rows; i++) {
        cout << setw(6) << right << sum[i];
    }
    cout << endl;
    return 0;
}
