#include <iostream>
#include <vector>
#include <string>
using namespace std;

// see https://www.hackerrank.com/challenges/saveprincess

int m;
vector <string> grid;


void displayPathtoPrincess(int m, vector <string> grid){
	
	int pY,pX;
	int mY,mX;
	
	// find
	for (std::vector<string>::size_type i = 0; i != grid.size(); ++i){
		std::size_t foundX;
		foundX = grid[i].find('p');
		if (foundX != std::string::npos){
			pY=i;
			pX=foundX;
			break;
		}
	}

	// (redundant find for bot)
	for (std::vector<string>::size_type i = 0; i != grid.size(); ++i){
		std::size_t foundX;
		foundX = grid[i].find('m');
		if (foundX != std::string::npos){
			mY=i;
			mX=foundX;
			break;
		}
	}
	//cout << mX << "," << mY << endl;
	//cout << pX << "," << pY << endl;
	
	// bot move to pX
	signed int delta = 0;
	while (true){
		delta=mX-pX;
		if (delta == 0){
			break;
		} else if( delta >= 1 ){
			cout << "LEFT" << endl;
			--mX;
		} else { 
			cout << "RIGHT" << endl;
			++mX;
		}
	}
	
	// bot move to pY
	while (true){
		delta=mY-pY;
		
		if (delta == 0){
			break;
		} else if( delta >= 1 )	{
			cout << "UP" << endl;
			--mY;
		} else  {
			cout << "DOWN" << endl;
			++mY;
		}
	}
 
}

void stdiny(){

    cin >> m;

    for(int i=0; i<m; i++) {
        string s;
        cin >> s;
        grid.push_back(s);
    }


}

void testcase1(){
	m = 3;
	grid.push_back("---");
	grid.push_back("-m-");
	grid.push_back("p--");
}

int main() {

	//stdiny();
	testcase1();
	
    displayPathtoPrincess(m,grid);	
	system("pause");
	return 0;
}
