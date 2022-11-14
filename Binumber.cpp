#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Binumber.h"
#include <iostream>
#include <vector>

using namespace std;


Binumber::Binumber(const char* arrin, int lengthin)
{
	
	arr.insert(arr.begin(), &arrin[0], &arrin[lengthin]);
	arr.resize(lengthin);
	optimize();
}
void Binumber::set_arr(const char* arrin, int lengthin)
{
	
	arr.insert(arr.begin(), &arrin[0], &arrin[lengthin]);
	arr.resize(lengthin);
	optimize();
}
void Binumber::add1()
{
	char flag = '1';
	int i;

	if (arr[0] == '0')
		arr[0] = '1';

	else
	{
		flag = '1';
		i = 0;

		while (flag != '0' && i < this->arr.size()-1)
		{
			if (arr[i] == '0')
			{
				arr[i] = '1';
				flag = '0';
			}

			else // arr[i] = '1'
			{
				arr[i] = '0';
			}
			i++;
		}//while

		if (arr[i] == '1' && flag == '1')// last bit
		{
			arr[i] = 0;
			arr.push_back('1');
		}
	}//else
}
void Binumber::dec1()
{	
	char flag;
	int i;

	if (arr[0] == '1')
		arr[0] = '0';
	else
	{
		flag = '1';
		i = 0;

		while (flag != '0' && i < this->arr.size())
		{
			if (arr[i] == '1')
			{
				arr[i] = '0';
				flag = '0';
			}//if

			else // arr[i] = '0'
			{
				arr[i] = '1';
			}//else

			i++;
		}//while
	}//else

	optimize();
}
void Binumber::resize(int newSize)
{
	arr.resize(newSize);
}
void Binumber::optimize()
{//delete zero from the end 
	int i = this->arr.size() - 1;

	while (i >= 0 && arr[i] == '0')
		i--;
	i++;

	if (i < this->arr.size())
		arr.resize(i);
}
void Binumber::print()
{
	for (int i = this->arr.size() - 1; i >= 0; i--)
		cout << arr[i];
	cout << endl;
}
int Binumber::get_dec_val()
{
	int sum = 0;
	for (int i = arr.size()-1; i>= 0; i--)
	{
		if (arr[i] == '1')
			sum += pow(2, i);
	}
	return sum;
}
