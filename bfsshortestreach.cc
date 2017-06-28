#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

/**
 * @author ypcrts
 * https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach
 * 
 * IN:
 * 2
 * 4 2
 * 1 2
 * 1 3
 * 1
 * 3 1
 * 2 3
 * 2
 * 
 * OUT:
 * 6 6 -1
 * -1 6
 */

class Graph {
  public:
    Graph(int n) {
      this->n = n;
      for (int i=0; i < n; ++i)
        this->edges.push_back(vector<bool>(n, false));
    }
    ~Graph() {
    }

    void add_edge(int u, int v) {
      assert(u < n);
      assert(v < n);
      this->edges[u][v] = true;
      this->edges[v][u] = true;
    }

    vector<int> edges_of(int u) {
      vector<int> edges;
      assert(u < n);
      for (int i=0; i < n; i++) {
        if (i == u)
          continue;
        if (this->edges.at(u).at(i))
          edges.push_back(i);
      }
      return edges;
    }

    vector<int> shortest_reach(int start) {
      int pos = start, distance;
      vector<int> bfs(n, -1);
      deque<int> next;
      bfs[start] = 0;
      for (;;) {
        distance = bfs[pos] + 6;
        vector<int> edges = edges_of(pos);
        for (const auto &v : edges) {
          if (bfs[v] > distance || bfs[v] == -1) {
            // unvisited
            bfs[v] = distance;
            next.push_back(v);
          }
        }
        if (next.size() <= 0) {
          break;
        }
        pos = next.front();
        next.pop_front();
      }

      return bfs;
    }
  private:
    vector<vector<bool>> edges;
    int n;

};

int main() {
  int queries;
  cin >> queries;
  assert(1 <= queries && queries <= 10);

  for (int t = 0; t < queries; t++) {

    int n, m;
    cin >> n;
    assert(2 <= n && n <= 1000);
    // Create a graph of size n where each edge weight is 6: 
    Graph graph(n);
    cin >> m;
    assert(1 <= m && m <= n*(n-1)/2);
    // read and set edges
    for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      assert(u < n);
      assert(v < n);
      // add each edge to the graph
      graph.add_edge(u, v);
    }
    int startId;
    cin >> startId;
    startId--;
    assert(startId < n);
    // Find shortest reach from node s
    vector<int> distances = graph.shortest_reach(startId);

    for (int i = 0; i < distances.size(); i++) {
      if (i != startId) {
        cout << distances[i] << " ";
      }
    }
    cout << endl;
  }

  return 0;
}
