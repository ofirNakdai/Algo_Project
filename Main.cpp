//project by roman vitvitsky 324065184 and ofir nakdai 
#define _CRT_SECURE_NO_WARNINGS
#include "Binumber.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

string DIV_BY_0 = "ERROR! div by zero is not allowed";
Binumber zero(1, '0');
Binumber one(1, '1');
#define RECURSION_STOP 128

using namespace std;

Binumber algo1(Binumber& m, Binumber& n)//n increases by m, m stays the same
{
	Binumber mCopy(m);
	Binumber nCopy(n);
	while (mCopy.size() > 0)
	{
		nCopy.add1();
		mCopy.dec1();
	}
	return nCopy;
}

Binumber algo2(Binumber& m, Binumber& n)
{// long adding
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
{// naive multiplication
	Binumber mCopy(m), nCopy(n);
	Binumber tmp(n);

	if (m.comp(zero) == 0 || n.comp(zero) == 0)
		return zero;

	mCopy.dec1();
	//for (int i = 0; i < t - 1; i++)
	while (mCopy.size() > 0)
	{
		mCopy.dec1();
		tmp = algo1(n, tmp);
	}


	return tmp;
}

/*Binumber algo4_test(Binumber& m, Binumber& n, int m_size)
{// m_size = m.size() -1		long multiplication
	
	if (m_size == 1)
	{
		if (m.get_cell_bit(0) == 1)
			return Binumber(n);
		else
			return Binumber(1, '0');
	}
	/*if (m_size <= RECURSION_STOP)
	{
		//Binumber litleM(m);
		//litleM.resize(m_size);
		//return algo3(litleM, n);
		return zero;
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
			Binumber rec = algo4(m, n, m_size - 1);
			Binumber test = algo2(zero, rec);
			return test;
		}
	}
}*/
Binumber algo4(Binumber& m, Binumber& n)
{
	int m_size = m.size();
	Binumber tmp, sum(zero);
	for (int i = 0; i < m_size; i++)
	{
		if (m.get_cell_bit(i) == 1)
		{
			tmp = n;
			tmp.shift_right(i);
			sum = algo2(tmp, sum);
		}
	}	

	return sum;
}

Binumber algo5_rec(Binumber& m, Binumber& n)
{
	int N;
	if (m.size() <= RECURSION_STOP && n.size() <= RECURSION_STOP)
	{
		return algo4(m, n);
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
		return algo4(m, n);
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

	Binumber q(one);

	if (m.comp(zero) == 0)
	{
		throw DIV_BY_0;// division by 0
	}

	while (algo4(m, q).comp(n) == -1) // while (mq < n)
		q.add1();

	if (algo4(m, q).comp(n) == 0)// if(mk == n)
		q_out = q;
	else
	{
		q.dec1();
		q_out = q;
	}

	Binumber mq = algo4(m, q);
	Binumber tmp = returnBiggerMinusSmallerBinumber(n, mq);
	r_out = tmp;
}

void algo8(Binumber& n, Binumber& m, Binumber& q_out, Binumber& r_out)
{ // n / m
	Binumber start(1, '1');
	Binumber end(n);
	Binumber res(1, '0');

	if (m.comp(zero) == 0)
	{
		throw DIV_BY_0;// division by 0
	}

	while (end.comp(start) == 1 || end.comp(start) == 0) // while (end >= start)
	{
		q_out = algo2(start, end); // long adding
		q_out.dev2();

		res = algo6(m, q_out); // long multi
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

	if (algo6(m, q_out).comp(n) != 0)// if(mk != n) means m does not devide n
		q_out.dec1();

	res = algo6(m, q_out);//long multi
	r_out = returnBiggerMinusSmallerBinumber(n, res);
}


void run_algorithms_up_to_num(fstream& out_file, Binumber& m, Binumber& n, int num)
{
	if (num == 1 || num == 9)
	{
		algo1(m, n).print_to_file(out_file);
	}
	if (num == 2 || num == 9)
	{
		algo2(m, n).print_to_file(out_file);

	}
	if (num == 3 || num == 9)
	{
		algo3(m, n).print_to_file(out_file);

	}
	if (num == 4 || num == 9)
	{
		algo4(m, n).print_to_file(out_file);

	}
	if (num == 5 || num == 9)
	{
		algo5(m, n).print_to_file(out_file);

	}
	if (num == 6 || num == 9)
	{
		algo6(m, n).print_to_file(out_file);

	}
	if (num == 7 || num == 9)
	{
		Binumber q_algo7_res;
		Binumber r_algo7_res;

		try
		{
			algo7(m, n, q_algo7_res, r_algo7_res);
			q_algo7_res.print_to_file(out_file);
			r_algo7_res.print_to_file(out_file);
		}
		catch (string msg)
		{
			cout << msg << endl;
		}
	}
	if (num == 8 || num == 9)
	{
		Binumber q_algo8_res;
		Binumber r_algo8_res;

		try
		{
			algo8(m, n, q_algo8_res, r_algo8_res);
			q_algo8_res.print_to_file(out_file);
			r_algo8_res.print_to_file(out_file);
		}
		catch (string msg)
		{
			cout << msg << endl;
		}
	}

}

void main(int argc, char* argv[])
{ 
	fstream fin, fout;
	fin.open(argv[1], ios::in);
	if (!fin)
	{
		cout << "Input File doesn't exist!" << endl;
	}
	fout.open(argv[2], ios::out);
	if (!fout)
	{
		cout << "Output File doesn't exist!" << endl;
	}

	string line1, line2, line3;
	int algo_num;
	getline(fin, line1);
	algo_num = stoi(line1);

	if (algo_num < 0 || algo_num > 9)
	{
		cout << " error: invalid algo num" << endl;
	}
	else
	{
		getline(fin, line2);
		if (line2.size() == 0)
		{
			cout << " error: missing number!" << endl;
			system("pause");
			exit(0);
		}
		getline(fin, line3);
		if (line3.size() == 0)
		{
			cout << " error: missing number!" << endl;
			system("pause");
			exit(0);
		}

		Binumber m(line2); //first m
		Binumber n(line3);// second n
		run_algorithms_up_to_num(fout, m, n, algo_num);
	}
	

	//time_t start, end;
	//double time_taken = 0;
	//string n_str = "1011",
	//	m_str = "1011";
	//int pow = 2;
	//while(time_taken <= 300)
	//{
	//	m_str = m_str + m_str;
	//	n_str = n_str + n_str;
	//	pow++;
	//	Binumber m(m_str);
	//	Binumber n(n_str);
	//	time(&start);
	//	algo6(m, n);
	//	time(&end);

	//	time_taken = double(end - start);
	//	cout <<"INPUT SIZE IS 2^"<<pow<< ". Time taken by program is : " << time_taken << " sec " << endl;
	//}
	//system("pause");


	


	//const char* m = "1001"; // 25
	//const char* n = "0"; // 3
	

	//cout << "num1: "; num1.print();	cout << "dec value: " << num1.get_dec_val() << endl;
	//cout << "num2: "; num2.print();	cout << "dec value: " << num2.get_dec_val() << endl;

	///*Binumber algo1_res = algo1(num1, num2);
	//cout << "algo1 res: ";
	//algo1_res.print();
	//cout << "dec val: " << algo1_res.get_dec_val() << endl;*/

	////Binumber algo2_res = algo2(num1, num2);
	////cout << "algo2 res: ";
	////algo2_res.print();
	////cout << "dec val: " << algo2_res.get_dec_val() << endl;

	////Binumber algo3_res(algo3(num1, num2));
	////cout << "algo3 res: ";
	////algo3_res.print();
	////cout << "dec val: " << algo3_res.get_dec_val() << endl;
	////

	///*Binumber algo4_res(algo4(num1, num2,4));
	//cout << "algo4 res: ";
	//algo4_res.print();
	//cout << "dec val: " << algo4_res.get_dec_val() << endl;*/


	//Binumber algo5_res(algo5(num1, num2));
	//cout << "algo5 res: ";
	//algo5_res.print();
	//cout << "dec val: " << algo5_res.get_dec_val() << endl;

	//Binumber algo6_res(algo6(num1, num2));
	//cout << "algo6 res: ";
	//algo6_res.print();
	//cout << "dec val: " << algo6_res.get_dec_val() << endl;

	///*Binumber test = returnBiggerMinusSmallerBinumber(num2, num1);
	//test.print();
	//cout << test.get_dec_val();*/

	//
	//Binumber q_algo7_res;
	//Binumber r_algo7_res;

	//try
	//{
	//	algo7(num1, num2, q_algo7_res, r_algo7_res);
	//	cout << "algo 7: dec val: q = " << q_algo7_res.get_dec_val() << "      r= " << r_algo7_res.get_dec_val() << endl;
	//}
	//catch(string msg)
	//{
	//	cout << msg << endl;
	//}

	//try
	//{
	//	algo8(num1, num2, q_algo7_res, r_algo7_res);
	//	cout << "algo 8: dec val: q = " << q_algo7_res.get_dec_val() << "      r= " << r_algo7_res.get_dec_val() << endl;
	//}
	//catch (string msg)
	//{
	//	cout << msg << endl;
	//}
	//


}
