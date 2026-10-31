#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    const int rows = 3;
    const int cols = 4;
    int a[rows][cols] = {
        {5, 12, -3, 8},
        {17, 4, 17, -2},
        {0, 7, 9, 14}
    };

    int mx = a[0][0];
    int rowIndex = 0, colIndex = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (a[i][j] > mx) {
                mx = a[i][j];
                rowIndex = i;
                colIndex = j;
            }
        }
    }

    cout << "Матрица:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }
    cout << "Максимум = " << mx << endl;
    cout << "Индексы первого максимума = [" << rowIndex << "][" << colIndex << "]" << endl;
    cout << "Номер строки = " << rowIndex + 1 << ", номер столбца = " << colIndex + 1 << endl;
    return 0;
}
