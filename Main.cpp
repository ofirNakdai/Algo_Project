#define _CRT_SECURE_NO_WARNINGS
#include "Binumber.h"
#include <iostream>
#include <vector>
using namespace std;

#define RECURSION_STOP 8

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
	Binumber res(max(n_size, m_size));

	while (i < n_size && i < m_size)
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
		case 3:
			res_num = 1;
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
		case 3:
			res_num = 1;
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
		res_num = m.get_cell_bit(i) + flag;
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
		case 3:
			res_num = 1;
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
	while (mCopy.size() > 0)
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
			Binumber test(algo2(tmp, rec));
			return test;
		}

		else
		{
			Binumber tmp(1, '0');
			Binumber rec = algo4(m, n, m_size - 1);
			Binumber test = algo2(tmp, rec);
			return test;
		}
	}
}

Binumber algo5_rec(Binumber& m, Binumber& n)
{
	int N;
	if (m.size() <= RECURSION_STOP && n.size() <= RECURSION_STOP)
	{
		return algo4(m, n, m.size());
	}
	int adjustM = 0;
	int adjustN = 0;
	int adjust = 0;
	if (m.size() % 2 != 0) {
		m.shift_right(1);
		adjustM++;
	}
	if (n.size() % 2 != 0) {
		n.shift_right(1);
		adjustN++;
	}
	if (n.size() > m.size())
	{
		adjustM += n.size() - m.size();
		m.shift_right(n.size() - m.size());
	}
	if (m.size() > n.size())
	{
		adjustN += m.size() - n.size();
		n.shift_right(m.size() - n.size());
	}
	adjust = adjustM + adjustN;
	N = m.size();


	Binumber n1(n);
	n1.erase(0, N / 2);
	Binumber n2(n);
	n2.resize(N / 2);
	Binumber m1(m);
	m1.erase(0, N / 2);
	Binumber m2(m);
	m2.resize(N / 2);

	
	Binumber n1m1 = algo5_rec(n1, m1);
	Binumber n1m2 = algo5_rec(n1, m2);
	Binumber n2m1 = algo5_rec(n2, m1);
	Binumber n2m2 = algo5_rec(n2, m2);

	n1m1.shift_right(N);
	Binumber n1m2_plus_n2m1 = algo2(n1m2, n2m1);
	n1m2_plus_n2m1.shift_right(N / 2);

	Binumber res1 = algo2(n1m1, n1m2_plus_n2m1);
	Binumber res2 = algo2(res1, n2m2);

	res2.erase(0, adjust);
	n.erase(0, adjustN);
	m.erase(0, adjustM);
	return res2;

}

Binumber algo5(Binumber& m, Binumber& n)
{
	int adjustM = 0;
	int adjustN = 0;
	int adjust = 0;
	if (m.size() % 2 != 0) {
		m.shift_right(1);
		adjustM++;
	}
	if (n.size() % 2 != 0) {
		n.shift_right(1);
		adjustN++;
	}
	if (n.size() > m.size())
	{
		adjustM += n.size() - m.size();
		m.shift_right(n.size() - m.size());

	}
	if (m.size() > n.size())
	{
		adjustN += m.size() - n.size();
		n.shift_right(m.size() - n.size());

	}
	adjust = adjustM + adjustN;
	int N = m.size();
	Binumber res = algo5_rec(m, n);
	res.erase(0, adjust);
	n.erase(0, adjustN);
	m.erase(0, adjustM);
	return res;
}

Binumber returnBiggerMinusSmallerBinumber(Binumber bigger, Binumber smaller)
{
	int temp = 0, carry = 0, index = 0;
	Binumber copyOfBigger(bigger);
	Binumber copyOfSmaller(smaller);
	Binumber biggerMinusSmaller(0, '0');

	while (copyOfSmaller.size() < copyOfBigger.size())
		copyOfSmaller.pushBack('0');


	for (int i = 0; i < copyOfBigger.size(); i++)
	{
		if (copyOfBigger.get_cell_bit(i) == 1 && copyOfSmaller.get_cell_bit(i) == 0)
			biggerMinusSmaller.pushBack('1');

		else if (copyOfBigger.get_cell_bit(i) == 1 && copyOfSmaller.get_cell_bit(i) == 1)
			biggerMinusSmaller.pushBack('0');

		else if (copyOfBigger.get_cell_bit(i) == 0 && copyOfSmaller.get_cell_bit(i) == 0)
			biggerMinusSmaller.pushBack('0');

		else
		{
			for (int j = i + 1; j < copyOfBigger.size(); j++)
			{
				if (copyOfBigger.get_cell_bit(j) == 0)
					copyOfBigger.set_cell_bit(j, '1');
				else
				{
					copyOfBigger.set_cell_bit(j, '0');
					biggerMinusSmaller.pushBack('1');
					break;
				}
			}
		}
	}
	return biggerMinusSmaller;
}


Binumber algo6_rec(Binumber& m, Binumber& n)
{
	int N;
	if (m.size() <= RECURSION_STOP && n.size() <= RECURSION_STOP)
	{
		return algo4(m, n, m.size());
	}
	int adjustM = 0;
	int adjustN = 0;
	int adjust = 0;
	if (m.size() % 2 != 0) {
		m.shift_right(1);
		adjustM++;
	}
	if (n.size() % 2 != 0) {
		n.shift_right(1);
		adjustN++;
	}
	if (n.size() > m.size())
	{
		adjustM += n.size() - m.size();
		m.shift_right(n.size() - m.size());
	}
	if (m.size() > n.size())
	{
		adjustN += m.size() - n.size();
		n.shift_right(m.size() - n.size());
	}
	adjust = adjustM + adjustN;
	N = m.size();

	Binumber n1(n);
	n1.erase(0, N / 2);
	Binumber n2(n);
	n2.resize(N / 2);
	Binumber m1(m);
	m1.erase(0, N / 2);
	Binumber m2(m);
	m2.resize(N / 2);

	Binumber n1Plusn2 = algo2(n1, n2);
	Binumber m1Plusm2 = algo2(m1, m2);

	Binumber F = algo6_rec(n1, m1);
	Binumber H = algo6_rec(n1Plusn2, m1Plusm2);
	Binumber G = algo6_rec(n2, m2);

	Binumber HminusF = returnBiggerMinusSmallerBinumber(H, F);
	Binumber HminusFminusG = returnBiggerMinusSmallerBinumber(HminusF, G);

	HminusFminusG.shift_right(N / 2);
	F.shift_right(N);

	Binumber res1 = algo2(F, HminusFminusG);
	Binumber res2 = algo2(res1, G);

	res2.erase(0, adjust);
	n.erase(0, adjustN);
	m.erase(0, adjustM);
	return res2;
}


Binumber algo6(Binumber& m, Binumber& n)
{
	int adjustM = 0;
	int adjustN = 0;
	int adjust = 0;
	if (m.size() % 2 != 0) {
		m.shift_right(1);
		adjustM++;
	}
	if (n.size() % 2 != 0) {
		n.shift_right(1);
		adjustN++;
	}
	if (n.size() > m.size())
	{
		adjustM += n.size() - m.size();
		m.shift_right(n.size() - m.size());

	}
	if (m.size() > n.size())
	{
		adjustN += m.size() - n.size();
		n.shift_right(m.size() - n.size());

	}
	adjust = adjustM + adjustN;
	int N = m.size();
	Binumber res = algo6_rec(m, n);
	res.erase(0, adjust);
	n.erase(0, adjustN);
	m.erase(0, adjustM);
	return res;

}


void algo7(Binumber& n, Binumber& m, Binumber& q_out, Binumber& r_out)
{ //  n / m

	Binumber q(1, '0');

	while (algo4(m, q, m.size()).comp(n) == -1)// while (mq < n)
		q.add1();

	if (algo4(m, q, m.size()).comp(n) == 0)// if(mk == n)
		q_out = q;
	else
	{
		q.dec1();
		q_out = q;
	}

	Binumber mq = algo4(m, q, m.size());
	Binumber tmp = returnBiggerMinusSmallerBinumber(n, mq);
	r_out = tmp;
}

void algo8(Binumber& n, Binumber& m, Binumber& q_out, Binumber& r_out)
{
	Binumber start(1, '1');
	Binumber end(n);
	Binumber res(1, '0');

	while (end.comp(start) == 1 || end.comp(start) == 0) // while (end >= start)
	{
		q_out = algo2(start, end); // long adding
		q_out.dev2();

		res = algo4(m, q_out, m.size()); // long multi
		if (res.comp(n) == 0)//res == n
			break;
		else if (res.comp(n) == 1 || res.comp(n) == 0)// if res >= n
		{
			q_out.dec1();
			end = q_out;
		}
		else {
			q_out.add1();
			start = q_out;
		}

	}

	if (algo4(m, q_out, m.size()).comp(n) != 0)// if(mk != n) means m does not devide n
		q_out.dec1();

	res = algo4(m, q_out, m.size());//long multi
	r_out = returnBiggerMinusSmallerBinumber(n, res);
}

void main()
{
	const char* m = "0"; // 8
	const char* n = "1"; // 5
	Binumber num1(m), num2(n);

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

	//Binumber algo3_res(algo3(num1, num2));
	//cout << "algo3 res: ";
	//algo3_res.print();
	//cout << "dec val: " << algo3_res.get_dec_val() << endl;
	//

	/*Binumber algo4_res(algo4(num1, num2,4));
	cout << "algo4 res: ";
	algo4_res.print();
	cout << "dec val: " << algo4_res.get_dec_val() << endl;*/


	Binumber algo5_res(algo5(num1, num2));
	cout << "algo5 res: ";
	algo5_res.print();
	cout << "dec val: " << algo5_res.get_dec_val() << endl;

	Binumber algo6_res(algo6(num1, num2));
	cout << "algo6 res: ";
	algo6_res.print();
	cout << "dec val: " << algo6_res.get_dec_val() << endl;

	/*Binumber test = returnBiggerMinusSmallerBinumber(num2, num1);
	test.print();
	cout << test.get_dec_val();*/

	
	/*Binumber q_algo7_res;
	Binumber r_algo7_res;

	algo7(num1, num2, q_algo7_res, r_algo7_res);
	cout << "algo 7: dec val: q = " << q_algo7_res.get_dec_val() << "      r= " << r_algo7_res.get_dec_val() << endl;


	algo8(num1, num2, q_algo7_res, r_algo7_res);
	cout << "algo 8: dec val: q = " << q_algo7_res.get_dec_val() << "      r= " << r_algo7_res.get_dec_val() << endl;*/

	






}
