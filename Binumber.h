#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <vector>

using namespace std;

class Binumber
{
	vector<char> arr;

public:
	Binumber();
	Binumber(int size)
	{
		if (size == 0)
		{
			this->arr.push_back(0);
		}
		this->arr.reserve(size);
	}
	Binumber(const char* arrin, int lengthin);
	Binumber(int size, char bit);
	Binumber(Binumber& x); // copy c'tor
	Binumber(Binumber&& x); // move c'tor



	void set_arr(const char* arrin, int lengthin);
	void copy(Binumber& x);
	int get_cell_bit(int cell);
	void set_cell_bit(int cell, char bit);
	
	int size(){ return this->arr.size(); }
	void resize(int newSize);
	void erase(int start, int end);
	void add1();
	void dec1();
	void print();
	int get_dec_val();
	void pushBack(char val) { this->arr.push_back(val); }	
	Binumber shift_right(int len);

private:
	void optimize();//delete zero from the end 

};



