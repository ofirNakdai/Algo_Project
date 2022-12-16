//project by roman vitvitsky 324065184 and ofir nakdai 
#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <vector>
#include <string>
#include <fstream>



using namespace std;

class Binumber
{
	vector<char> arr;

public:
	Binumber() = default;
	Binumber(int size)
	{
		if (size == 0)
		{
			this->arr.push_back('0');
		}
		this->arr.reserve(size);
	}
	Binumber(const char* arrin, int lengthin);
	Binumber(string arrin);
	Binumber(const char* arrin);
	Binumber(int size, char bit);
	Binumber(Binumber& x); // copy c'tor
	Binumber(Binumber&& x); // move c'tor



	void set_arr(const char* arrin, int lengthin);
	//void copy(Binumber& x);
	int get_cell_bit(int cell);
	void set_cell_bit(int cell, char bit);

	int size() { return this->arr.size(); }
	void resize(int newSize);
	void resize(int newSize, char val);//val = value inserted into new slots 
	void erase(int start, int end);
	void add1();
	void dec1();
	void print_to_file(fstream& out_file);
	void print();
	int get_dec_val();
	void pushBack(char val) { this->arr.push_back(val); }
	Binumber shift_right(int len);
	int comp(Binumber& num);
	Binumber operator = (const Binumber& x);
	Binumber dev2();


private:		
	void optimize();//delete zero from the end 

};



