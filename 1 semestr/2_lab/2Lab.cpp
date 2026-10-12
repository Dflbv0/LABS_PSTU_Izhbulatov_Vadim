#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    double a = 0;
    int n = 1;
    double sum = 0;
    float epsilon = pow(10, -4);

    do {

        double fact_n = 1;
        for (int i = 1; i <= n; i++) {
            fact_n *= i;
        }

        double fact_3n = 1;
        for (int i = 1; i <= 3 * n; i++) {
            fact_3n *= i;
        }

        a = (pow(3, n) * fact_n) / fact_3n;

        sum = sum + a;
        n = n + 1;

    } while (a >= epsilon);

    cout << "Sum: " << sum << endl;

    return 0;
}

