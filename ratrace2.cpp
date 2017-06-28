#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
// https://www.hackerrank.com/contests/101hack24/challenges/rat-race

int n;
vector<int> s;
vector<int> d;
vector<double> ft;

void getinput(){

	// n
	scanf("%d", &n);

	//speed[]
	for (int i = 0; i < n; ++i){
		int x;
		scanf("%d", &x);
		s.push_back(x);
	}

	//distance[]
	for (int i = 0; i < n; ++i){
		int x;
		scanf("%d", &x);
		d.push_back(x);
	}


}

void testcase1() {
	n = 3;
	s.push_back(2); s.push_back(5); s.push_back(1);
	d.push_back(4); d.push_back(10); d.push_back(3);
}

int main() {
	//testcase1();
	getinput();

	double win = 200;
	for (int i = 0; i < n; ++i) {
		ft.push_back( d[i] / (double) s[i] );
		if (ft[i] < win) 
			win = ft[i];
	}
	for (int i = 0; i < n; ++i) {
		if (ft[i] == win) cout << i + 1 << endl;
	}

	//system("pause");
	return 0;
}