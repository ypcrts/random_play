#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
// https://www.hackerrank.com/contests/101hack24/challenges/rat-race

class Rat {
public:
	int name;
	int speed;
	int dist;
	double finishtime;

	Rat(int name,int speed,int dist);
	bool operator< (const Rat &other) const {
		return finishtime < other.finishtime;
	}
};
int n; // number of rats
vector <int> speed, dist;
vector <Rat> rats;



Rat::Rat(int name, int speed, int dist){
	this->name = name;
	this->speed = speed;
	this->dist = dist;
	this->finishtime = (double) this->dist / (double) this->speed;

}


void getinput(){
	
	// n
	scanf("%d", &n);

	//speed[]
	for (int i = 0; i < n; ++i){
		int x;
		scanf("%d", &x);
		speed.push_back(x);
	}

	//distance[]
	for (int i = 0; i < n; ++i){
		int x;
		scanf("%d", &x);
		dist.push_back(x);
	}


}

void testcase1() {
	n = 3;
	speed.push_back(2); speed.push_back(5); speed.push_back(1);
	dist.push_back(4); dist.push_back(10); dist.push_back(3);
}

int main() {
	//testcase1();
	getinput();

	for (int i = 0; i < n; ++i){
		rats.push_back(Rat(i+1, speed[i], dist[i]));
	}

	std::sort(rats.begin(), rats.end());

	cout << rats[0].name << endl;
	for (int i = 1; i < n; ++i){
		if (rats[i].finishtime == rats[0].finishtime){
			cout << rats[i].name << endl;
		} else {
			break;
		}
	}

	system("pause");
	return 0;
}

