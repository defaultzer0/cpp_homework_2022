#include <bits/stdc++.h>

using namespace std;

int main(){
	double a, b, c;
	cin >> a >> b >> c;

	double D = b*b - 4*a*c;
	if (D < 0)
		cout << "No real solutions";

	else if (D == 0)
		cout << -b / (2 * a);

	else 
		cout << (-b + sqrt(D)) / (2 * a) << " " << (-b - sqrt(D)) / (2 * a);
} 
