#include <iostream>
using namespace std;

constexpr int limit = 100;

long long columnSum(const int a[][limit], int rows, int column) {
    long long sum = 0;
    for (int i = 0; i < rows; ++i)
        sum += a[i][column];
    return sum;
}

int findColumn(const int a[][limit], int rows, int cols,
               long long& left, long long& right) {
    left = right = 0;
    for (int j = 0; j < cols; ++j)
        right += columnSum(a, rows, j);

    for (int j = 0; j < cols; ++j) {
        long long current = columnSum(a, rows, j);
        right -= current;
        if (j > 0 && j + 1 < cols && left > right)
            return j;
        left += current;
    }
    return -1;
}

int main() {
    int rows, cols, a[limit][limit];
    cout << "Введите число строк и столбцов (1..100):\n";
    if (!(cin >> rows >> cols) || rows < 1 || rows > limit ||
        cols < 1 || cols > limit) return 1;

    cout << "Введите элементы по строкам:\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (!(cin >> a[i][j])) return 1;

    long long left, right;
    int j = findColumn(a, rows, cols, left, right);
    if (j == -1) cout << "Подходящего столбца нет.\n";
    else cout << "Столбец: " << j + 1 << "\nСлева: " << left
              << "\nСправа: " << right << '\n';
}
