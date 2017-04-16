#include <iostream>
#include <utility>
#include <vector>

using namespace std;

/**
 * https://www.hackerrank.com/challenges/ctci-connected-cell-in-a-grid
 *
 * Find the largest area of contingous filled cells (marked with '1').
 *
 * INPUT
 * 4
 * 4
 * 1 1 0 0
 * 0 1 1 0
 * 0 0 1 0
 * 1 0 0 0 
 *
 * OUTPUT
 * 5
 *
 */

int get_biggest_region(vector< vector<int> > grid) {
  int cur=-1, biggest=0;
  vector<pair<int,int>> area_next;
  for (;;) {
    int i, j;
    if (area_next.size() > 0) {
      const auto &from = area_next.back();
      i = from.first, j= from.second;
      area_next.pop_back();
    } else {
      if (cur > biggest) biggest = cur;
      cur = -1;  // reset
      for (int y=0; y < grid.size(); ++y)
        for (int x=0; x < grid[y].size(); ++x) {
          if (grid[y][x] == 1) {
            i = y, j = x;
            cur = 0; // mark success
            break;
          }
        }
      if (cur <= -1)
        return biggest;
    }

    if (grid[i][j] == 1) {
      grid[i][j] = 0;
      cur++;
      bool i_lower, i_upper, j_lower, j_upper;
      if ((i_lower=i-1 >= 0))              area_next.push_back(pair<int,int>(i-1, j));
      if ((i_upper=i+1 < grid.size()))     area_next.push_back(pair<int,int>(i+1, j));
      if ((j_lower=j-1 >= 0))              area_next.push_back(pair<int,int>(i,   j-1));
      if ((j_upper=j+1 < grid[i].size()))  area_next.push_back(pair<int,int>(i,   j+1));
      if (i_lower && j_lower)            area_next.push_back(pair<int,int>(i-1, j-1));
      if (i_upper && j_upper)            area_next.push_back(pair<int,int>(i+1, j+1));
      if (i_upper && j_lower)            area_next.push_back(pair<int,int>(i+1, j-1));
      if (i_lower && j_upper)            area_next.push_back(pair<int,int>(i-1, j+1));
    }
  }
}

int main(){
    int n;
    cin >> n;
    int m;
    cin >> m;
    vector< vector<int> > grid(n,vector<int>(m));
    for(int grid_i = 0; grid_i < n; grid_i++){
       for(int grid_j = 0; grid_j < m; grid_j++){
          cin >> grid[grid_i][grid_j];
       }
    }
    cout << get_biggest_region(grid) << endl;
    return 0;
}
