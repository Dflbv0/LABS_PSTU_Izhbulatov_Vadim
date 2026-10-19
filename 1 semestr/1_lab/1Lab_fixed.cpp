#include <iostream>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    //zadanije 1
    //float
    float aF = 1000;
    float bF = 0.0001;

    float chisl1 = pow(aF - bF, 2) - (pow(aF, 2) - 2 * aF * bF);
    float znamen1 = pow(bF, 2);
    float result1 = chisl1 / znamen1;

    cout << "Zadanie 1" << endl;
    cout << "float: " << result1 << endl;

    //double
    double aD = 1000;
    double bD = 0.0001;

    double chisl2 = pow(aD - bD, 2) - (pow(aD, 2) - 2 * aD * bD);
    double znamen2 = pow(bD, 2);
    double result2 = chisl2 / znamen2;

    cout << "double: " << result2 << endl;

    //zadanije 2
    int m = 5;
    int n = 3;

    cout << "Zadanie 2" << endl;
    cout << "Nachalnie znacheniya: m = " << m << ", n = " << n << endl;

    int x1 = m - ++n;
    cout << "m - ++n = " << x1 << endl;
    cout << "m = " << m << ", n = " << n << endl;

    bool x2 = ++m > --n;
    cout << "++m > --n = " << x2 << endl;
    cout << "m = " << m << ", n = " << n << endl;

    bool x3 = --n < ++m;
    cout << "--n < ++m = " << x3 << endl;
    cout << "m = " << m << ", n = " << n << endl;

    return 0;
}
