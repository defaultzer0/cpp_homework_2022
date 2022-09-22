#include <bits/stdc++.h>

using namespace std;


// 1 Вариант
int main()
{
    cout << "Enter the miles\n";
    double a, b;
    cin >> a;
    const double miles_to_km = 1.609; 
    b = a * miles_to_km;
    cout << "The km. = " << b << endl;
    return 0;
}

// 2 Вариант
int main()
{
    cout << "Enter the pounds\n";
    double b;
    const double a = 405.9;

    cin >> b;
    cout << "The kg. = " << a * b << endl;
    return 0;
}