#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

int main()
{
    double mas[100];
    int n = 12;
    srand(time(0));

    //sozdanie massiva
    for (int i = 0; i < n; i++) {
        mas[i] = rand() % 21 - 10;
    }

    cout << "Nachalniy massiv:" << endl;
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;

    //poisk minimuma
    double min = mas[0];
    for (int i = 1; i < n; i++) {
        if (mas[i] < min) {
            min = mas[i];
        }
    }

    //udalenie vseh minimalnih elementov
    for (int i = 0; i < n;) {
        if (mas[i] == min) {
            for (int j = i; j < n - 1; j++) {
                mas[j] = mas[j + 1];
            }
            n = n - 1;
        }
        else {
            i = i + 1;
        }
    }

    cout << "Posle udaleniya minimuma:" << endl;
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;

    //srednee arifmeticheskoe
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum = sum + mas[i];
    }
    double sred = sum / n;

    //sdvig massiva na tri mesta
    for (int i = n - 1; i >= 0; i--) {
        mas[i + 3] = mas[i];
    }
    for (int i = 0; i < 3; i++) {
        mas[i] = sred;
    }
    n = n + 3;

    cout << fixed << setprecision(3);
    cout << "Srednee = " << sred << endl;
    cout << "Konechniy massiv:" << endl;
    for (int i = 0; i < n; i++) {
        cout << mas[i] << " ";
    }
    cout << endl;

    return 0;
}
