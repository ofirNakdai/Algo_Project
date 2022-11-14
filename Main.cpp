#define _CRT_SECURE_NO_WARNINGS
#include "Binumber.h"
#include <iostream>
#include <vector>
using namespace std;

Binumber algo1(Binumber& m, Binumber& n)
{
	int n1, m1;
	while (m.size() > 0)
	{
		n.add1();
		m.dec1();
	}

	return n;
}

void main()
{
	const char* m = "1101"; //13
	const char* n = "0001"; //1
	Binumber num1(m,4), num2(n,4);
	
	cout << "num1: "; num1.print();	cout << "dec value: " << num1.get_dec_val() << endl;
	cout << "num2: "; num2.print();	cout << "dec value: " << num2.get_dec_val() << endl;
	
	cout << "algo1 res: " << algo1(num1, num2).get_dec_val();
}
