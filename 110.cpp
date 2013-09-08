/*
 * =====================================================================================
 *
 *       Filename:  110.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/06/2013 09:50:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Wei-Yi Cheng (weiyi-bitw), ninpy.weiyi@gmail.com
 *   Organization:  Columbia University
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const char cs[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

void swap(char* a, char* b)
{
	char c = *a;
	*a = *b;
	*b = c;
}

void compare_r(vector<char> & vec, string indent, int N, int k)
{
	if(k == N){
		cout << indent << "writeln(" << vec[0];
		for(int i = 1; i < N; i++){
			cout << "," << vec[i];
		}cout << ")"<< endl;
	}else{
		int i = vec.size();
		bool first = true;
		string newIndent(indent);
		newIndent += "  ";
		for(; i > 0; i--){
			vector<char> newVec(vec);
			cout << indent;
			if(!first) cout << "else ";
			cout << "if " << newVec[i-1] << " < " << cs[k] << " then" << endl;
			newVec.insert(newVec.begin()+i, cs[k]);
			compare_r(newVec, newIndent, N, k+1);
			first = false;
		}
		cout << indent << "else" << endl;
		vector<char> lastNewVec(vec);
		lastNewVec.insert(lastNewVec.begin(), cs[k]);
		compare_r(lastNewVec, newIndent, N, k+1);
		
	}
}


void pascalSort(int N)
{
	cout << "program sort(input,output);" << endl;
	cout << "var" << endl;
	cout << cs[0];
	for(int i = 1; i < N; i++){
		cout << "," << cs[i];
	}cout << " : integer;" << endl;
	cout << "begin" << endl;
	string indent("  ");

	cout << indent << "readln(";
	cout << cs[0];
	for(int i = 1; i < N; i++){
		cout << "," << cs[i];
	}cout << ");" << endl;
	vector<char> v;
	v.push_back(cs[0]);

	compare_r(v, indent, N, 1);
	

	cout << "end." << endl;
}

int main()
{
	int M;
	int n;
	cin >> M;
	
	for(int i = 0; i < M; i++){
		cin >> n;
		if(i) cout << endl;
		pascalSort(n);
	}

	return 0;
}
