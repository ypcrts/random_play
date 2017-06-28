#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

struct Twisty {
	int i;
	int j;
	int k;
};

int n;
vector<int> a;
vector<Twisty> tuples;


void getinput(){

	
	scanf("%d", &n);

	for (int i = 0; i < n; ++i){
		int x;
		scanf("%d", &x);
		a.push_back(x);
	}

}

void testcase1() {
	n = 6;
	int q[] = { 1, 6, 3, 4, 7, 4 };
	for (int i = 0; i < n; ++i){
		a.push_back(q[i]);
	}
}


int main() {
	testcase1();
	//getinput();


	//// FIND min & max
	//int min=a[0];
	//int max=a[0];
	//for (int i = 1; i < n; ++i){
	//	if (a[i] > max) max = a[i];
	//	if (a[i]) < min) min = a[i];
	//}

	//// Reverse iterate, remove values at end if highest
	//for (int i = n - 1; i > 3; --i){
	//	if (a[i] == max) a.erase(i);
	//	else break;
	//}

	//// Forward iterate, remove values at beginning if lowest
	//for (int i = n - 1; i > 3; --i){
	//	if (a[i] == max) a.erase(i);
	//	else break;
	//}

	for (int i = 0; i < n - 2; ++i){
		for (int j = i + 1; j < n - 1; ++j){
			for (int k = i + 2; k < n - 2; ++k){

				//check valid twisty
				if (a[k] < a[i] && a[i] < a[j]){
					//add
					Twisty s = {a[k],a[i],a[j]};


					tuples.push_back(s);
				}
			}
		}
		
	}

	cout << tuples.size() << endl;

	//system("pause");
	return 0;
}