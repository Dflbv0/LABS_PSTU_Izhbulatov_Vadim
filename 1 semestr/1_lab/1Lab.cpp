#include <iostream>
#include <math.h>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //float
    float aF = 1000;
    float bF = 0.0001;

    float chisl1 = pow(aF - bF, 2) - (pow(aF, 2) - 2 * aF * bF);
    float znamen1 = pow(bF, 2);
    float result1 = chisl1 / znamen1;

    cout << "float: " << result1 << endl;

    //double
    double aD = 1000;
    double bD = 0.0001;

    double chisl2 = pow(aD - bD, 2) - (pow(aD, 2) - 2 * aD * bD);
    double znamen2 = pow(bD, 2);
    double result2 = chisl2 / znamen2;

    cout << "double: " << result2 << endl;

    return 0;
}