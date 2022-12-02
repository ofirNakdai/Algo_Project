#define _CRT_SECURE_NO_WARNINGS
#include "Binumber.h"
#include <iostream>
#include <vector>
using namespace std;

Binumber algo1(Binumber& m, Binumber& n)//n increases by m, m stays the same
{
	Binumber mCopy(m);
	while (mCopy.size() > 0)
	{
		n.add1();
		mCopy.dec1();
	}

	return n;
}

 Binumber algo2(Binumber& m, Binumber& n)
 {
 	int flag = 0;
 	int i = 0, n_size = n.size(), m_size = m.size(), res_num;
	Binumber res(max(n_size,m_size));
	
 	while(i < n_size && i < m_size)
 	{
		res_num = m.get_cell_bit(i) + n.get_cell_bit(i) + flag;
		switch (res_num)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			flag = 0;
			break;
		case 2:
			res_num = 0;
			flag = 1;
			break;
		default:
			break;
		}
		
		res.pushBack((char)res_num + '0');
		i++;

 	}

	while (i < n_size)
	{
		res_num = n.get_cell_bit(i) + flag;
		switch (res_num)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			flag = 0;
			break;
		case 2:
			res_num = 0;
			flag = 1;
			break;
		default:
			break;
		}
		res.pushBack((char)res_num + '0');
		i++;
	}
	while (i < m_size)
	{
		res_num = m.get_cell_bit(i)+ flag;
		switch (res_num)
		{
		case 0:
			flag = 0;
			break;
		case 1:
			flag = 0;
			break;
		case 2:
			res_num = 0;
			flag = 1;
			break;
		default:
			break;
		}
		res.pushBack((char)res_num + '0');
		i++;
	}
	
	if (flag == 1)
		res.pushBack('1');

	return res;
 }

 Binumber algo3(Binumber& m, Binumber& n)
{
	 Binumber mCopy(m), nCopy(n);
	 mCopy.dec1();
	 //for (int i = 0; i < t - 1; i++)
	 while(mCopy.size()>0)
	 {
		mCopy.dec1();
		algo1(n, nCopy);		
	 }
		 
	 
	return nCopy;
}

Binumber algo4(Binumber& m, Binumber& n, int m_size)
{// m_size = m.size() -1
	if (m_size == 1)
	{
		if (m.get_cell_bit(0) == 1)
			return Binumber(n);
		else
			return Binumber(1, '0');
	}

	else
	{ // i > 0
		if (m.get_cell_bit(m_size - 1) == 1)
		{
			Binumber tmp(n);
			tmp.shift_right(m_size - 1);
			Binumber rec = algo4(m, n, m_size - 1);
			return algo2(tmp, rec);
		}
			
		else
		{
			Binumber tmp(1, '0');
			Binumber rec = algo4(m, n, m_size - 1);
			return algo2(tmp, rec);
		}
	}
}

 
 Binumber algo5_rec(Binumber& m, Binumber& n, int N)
 {
	 if(N<=128)
	 {
		return algo4(m, n, N);
	 }
	 Binumber n1(n);
	 n1.erase(0, N / 2 + 1);	 
	 Binumber n2(n);
	 n2.resize(N / 2);
	 Binumber m1(m);
	 m1.erase(0, N / 2 + 1);
	 Binumber m2(m);
	 m2.resize(N / 2);

	 Binumber n1m1 = algo5_rec(n1, m1, N / 2);
	 Binumber n1m2 = algo5_rec(n1, m2, N / 2);
	 Binumber n2m1 = algo5_rec(n2, m1, N / 2);
	 Binumber n2m2 = algo5_rec(n2, m2, N / 2);

	 n1m1.shift_right(N);
	 Binumber n1m2_plus_n2m1 = algo2(n1m2, n2m1);
	 n1m2_plus_n2m1.shift_right(N / 2);

	 Binumber res = algo2(n1m1, n1m2_plus_n2m1);
	 Binumber test(algo2(res, n2m2));
	 res.copy();




 }



 Binumber algo5(Binumber& m, Binumber& n)
 {
	 if (m.size() != n.size() || n.size() % 2 != 0 || m.size() % 2 != 0)
	 {
		 cout << "invalid input for algo5";
		 return NULL;
	 }
	 int N = m.size();
	 algo5_rec(m, n, N);

 }


 

void main()
{
	const char* m = "1101"; //13
	const char* n = "0011"; //3
	Binumber num1(m,4), num2(n,4);
	
	cout << "num1: "; num1.print();	cout << "dec value: " << num1.get_dec_val() << endl;
	cout << "num2: "; num2.print();	cout << "dec value: " << num2.get_dec_val() << endl;
	
	/*Binumber algo1_res = algo1(num1, num2);
	cout << "algo1 res: "; 
	algo1_res.print();
	cout << "dec val: " << algo1_res.get_dec_val() << endl;*/

	//Binumber algo2_res = algo2(num1, num2);
	//cout << "algo2 res: ";
	//algo2_res.print();
	//cout << "dec val: " << algo2_res.get_dec_val() << endl;

	Binumber algo3_res(algo3(num1, num2));
	cout << "algo3 res: ";
	algo3_res.print();
	cout << "dec val: " << algo3_res.get_dec_val() << endl;
}
