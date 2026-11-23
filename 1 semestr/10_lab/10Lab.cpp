#include <iostream>
using namespace std;

// Строки матрицы лежат подряд в одном динамическом массиве.
int* createMatrix(int rows, int cols) {
    return new int[rows * cols];
}

void destroyMatrix(int*& a) {
    delete[] a;
    a = nullptr;
}

void printMatrix(const int* a, int rows, int cols) {
    if (cols == 0) cout << "Все столбцы удалены.\n";
    for (int i = 0; i < rows && cols > 0; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << a[i * cols + j] << (j + 1 == cols ? '\n' : ' ');
    }
}

int* removeColumns(const int* a, int rows, int cols, int key,
                   int& newCols) {
    bool* keep = new bool[cols];
    newCols = 0;
    for (int j = 0; j < cols; ++j) {
        keep[j] = true;
        for (int i = 0; i < rows; ++i) {
            if (a[i * cols + j] == key) {
                keep[j] = false;
                break;
            }
        }
        if (keep[j]) ++newCols;
    }

    int* result = createMatrix(rows, newCols);
    int index = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (keep[j]) result[index++] = a[i * cols + j];
    delete[] keep;
    return result;
}

int main() {
    int rows, cols;
    cout << "Введите число строк и столбцов (1..1000):\n";
    if (!(cin >> rows >> cols) || rows < 1 || cols < 1 ||
        rows > 1000 || cols > 1000) return 1;
    int* a = createMatrix(rows, cols);
    cout << "Введите элементы по строкам:\n";
    for (int i = 0; i < rows * cols; ++i) {
        if (!(cin >> a[i])) {
            destroyMatrix(a);
            return 1;
        }
    }
    cout << "Исходная матрица:\n";
    printMatrix(a, rows, cols);
    int key, newCols;
    cout << "Введите число для поиска:\n";
    if (!(cin >> key)) {
        destroyMatrix(a);
        return 1;
    }
    int* result = removeColumns(a, rows, cols, key, newCols);
    cout << "Результат (" << rows << " x " << newCols << "):\n";
    printMatrix(result, rows, newCols);
    destroyMatrix(result);
    destroyMatrix(a);
}
