#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Binumber.h"
#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

static void remove_spaces_from_input(string& s)
{
	int last = s.size() - 1;

	while (last >= 0 && (s[last] == ' '|| s[last] == '\n' || s[last] == '\t' || s[last] == '\v'))
		--last;
	s.resize(last + 1);
}



Binumber::Binumber(const char* arrin, int lengthin)
{
	arr.reserve(lengthin);
	for (int i = lengthin - 1; i >= 0; i--)
		arr.push_back(arrin[i]);

	optimize();
}
Binumber::Binumber(string arrin)
{
	remove_spaces_from_input(arrin);
	int lengthin = arrin.size();
	arr.reserve(arrin.size());
	for (int i = lengthin - 1; i >= 0; i--) {
		if (arrin[i] == '0' || arrin[i] == '1')
			arr.push_back(arrin[i]);
		else
		{
			cout << " error: invalid number, not in Binary Base " << endl;
			system("pause");
			exit(1);
		}
	}
	optimize();
}

Binumber::Binumber(const char* arrin)
{
	int lengthin = strlen(arrin);
	arr.reserve(lengthin);
	for (int i = lengthin - 1; i >= 0; i--)
		arr.push_back(arrin[i]);

	optimize();
}

Binumber::Binumber(int size, char bit)
{
	this->arr.reserve(size);
	for (int i = 0; i < size; i++)
		arr.push_back(bit);
}
Binumber::Binumber(Binumber& x)
{
	for (int i = 0; i < x.size(); i++)
		arr.push_back(x.get_cell_bit(i) + '0');

	optimize();
}
Binumber::Binumber(Binumber&& x)
{
	arr = x.arr;
	/*for (int i =0; i <  x.size(); i++)
		arr.push_back(x.get_cell_bit(i) + '0');

	optimize();*/
} 


Binumber Binumber::operator = (const Binumber& x)
{
	this->arr = x.arr;
	/*for (int i = 0; i < x.size(); i++)
		arr.push_back(x.get_cell_bit(i) + '0');

	optimize();*/
	return *this;
}
/*void Binumber::copy(Binumber& x)
{
	for (int i = 0; i < x.size(); i++)
		arr.push_back(x.get_cell_bit(i) + '0');

	optimize();
}*/

void Binumber::set_arr(const char* arrin, int lengthin)
{
	arr.reserve(lengthin);
	for (int i = lengthin - 1; i >= 0; i--)
		arr.push_back(arrin[i]);

	optimize();
}
int Binumber::get_cell_bit(int cell)
{
	if (cell < this->arr.size()) {
		if (this->arr[cell] == '1')
			return 1;
		else
			return 0;
	}

	return -1;
}
void Binumber::set_cell_bit(int cell, char bit)
{
	if (cell < this->arr.size()) {
		this->arr[cell] = bit;
	}

}
void Binumber::add1()
{
	char flag = '1';
	int i;
	if (this->arr.size() == 0)
	{
		this->arr.push_back('1');
		return;
	}

	if (arr[0] == '0')
		arr[0] = '1';

	else
	{
		flag = '1';
		i = 0;

		while (flag != '0' && i < this->arr.size() - 1)
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
			arr[i] = '0';
			arr.push_back('1');
		}
	}//else
}
void Binumber::dec1()
{
	char flag;
	int i;
	if (this->arr.size() <= 0)
		return;

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
void Binumber::resize(int newSize, char val)
{
	arr.resize(newSize, val);
}
void Binumber::erase(int start, int end)
{
	if (end > arr.size())
		end = arr.size();
	arr.erase(arr.begin(), arr.begin() + end);
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
void Binumber::print_to_file(fstream& out_file)
{
	for (int i = this->arr.size() - 1; i >= 0; i--)
		out_file << arr[i];

	if (this->arr.size() == 0)
		out_file << '0';
	out_file << endl;
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
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		if (arr[i] == '1')
			sum += pow(2, i);
	}
	return sum;
}
Binumber Binumber::shift_right(int len)
{
	this->resize(this->arr.size() + len);
	int i;

	for (i = this->arr.size() - 1; i - len >= 0; i--)
		this->arr[i] = this->arr[i - len];

	for (i = 0; i < len; i++)
		this->arr[i] = '0';

	return *this;
}
Binumber Binumber::dev2()
{ // 11011001001  -> 1101100100
	if (this->size() == 1)
		this->arr[0] = '0';
	else // size > 1
	{
		for (int i = 0; i < arr.size()-1; i++)
			this->arr[i] = this->arr[i + 1];

		this->resize(this->arr.size() - 1);

		return *this;

	}

}
int Binumber::comp(Binumber& num)
{ // 1 - this > num     0 - this = num    -1 - this < num
	this->optimize();
	num.optimize();

	if (this->size() > num.size())
		return 1;
	else if (num.size() > this->size())
		return -1;
	else
	{//equal size
		for (int i = this->size()-1; i >= 0; i--)
		{
			if (num.get_cell_bit(i) > this->get_cell_bit(i))
				return -1;
			else if (this->get_cell_bit(i) > num.get_cell_bit(i))
				return 1;
		}

		return 0; // equal numbers
	}
}