#include <iostream>

using namespace std;

//Первый вариант
int main(){
	int x = 5, y = 9;
	x += y;
	y = x - y;
	x = x - y;
} 

//Второй вариант
int main(){
	x ^= y ^= x ^= y;
}
