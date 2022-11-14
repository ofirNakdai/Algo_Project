#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <vector>

using namespace std;

class Binumber
{
	vector<char> arr;

public:
	Binumber();
	Binumber(const char* arrin, int lengthin);

	void set_arr(const char* arrin, int lengthin);
	
	int size(){ return this->arr.size(); }
	void resize(int newSize);
	void add1();
	void dec1();
	void print();
	int get_dec_val();

private:
	void optimize();//delete zero from the end 

};

