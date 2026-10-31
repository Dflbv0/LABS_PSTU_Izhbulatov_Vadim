#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int main()
{
    double a = 0.2;
    double b = 1;
    int k = 10;
    int n = 10;
    double epsilon = pow(10, -4);

    cout << fixed << setprecision(6);
    cout << "X\t\tSN\t\tSE\t\tY" << endl;

    for (int i = 0; i <= k; i++) {
        double x = a + (b - a) * i / k;
        double z = (x - 1) / (x + 1);

        //summa dlya n = 10
        double sumN = 0;
        double chlen = z;
        for (int j = 0; j <= n; j++) {
            sumN = sumN + chlen;
            chlen = chlen * z * z * (2 * j + 1) / (2 * j + 3);
        }

        //summa s tochnostyu 0.0001
        double sumE = 0;
        double an = z;
        int j = 0;
        do {
            sumE = sumE + an;
            an = an * z * z * (2 * j + 1) / (2 * j + 3);
            j = j + 1;
        } while (fabs(an) >= epsilon);

        double y = log(x) / 2;
        cout << x << "\t" << sumN << "\t" << sumE << "\t" << y << endl;
    }

    return 0;
}
