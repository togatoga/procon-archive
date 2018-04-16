#include <algorithm>
#include <bitset>
#include <cassert>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// c++11
#include <array>
#include <tuple>
#include <unordered_map>
#include <unordered_set>

#define mp make_pair
#define mt make_tuple
#define rep(i, n) for (int i = 0; i < (n); i++)

using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
int N;
vector<pii> A,B;
const int MAX = 210;
struct edge { int to, cap, rev; };

vector<edge> G[MAX];
bool used[MAX];

void add_edge(int from, int to, int cap) {
    G[from].push_back((edge){to, cap, int(G[to].size())});
    G[to].push_back((edge){from, 0, int(G[from].size()-1)});
}

int dfs(int v, int t, int f) {
    if(v == t) return f;
    used[v] = 1;
    for(int i = 0 ; i < G[v].size(); i++){
        edge &e = G[v][i];
        if(used[e.to] or e.cap <= 0) continue;
        int d = dfs(e.to, t, min(f, e.cap));
        if(d > 0){
            e.cap -= d;
            G[e.to][e.rev].cap += d;
            return d;
        }
    }
    return 0;
}

int ford_fulkerson(int s, int t) {
    int flow = 0, f;
    while(1){
        memset(used, 0, sizeof(used));
        f = dfs(s, t, INF);
        if(f == 0) return flow;
        flow += f;
    }
}
int main() {
  cin >> N;
  for (int i = 0; i < N; i++){
    int a,b;
    cin >> a >> b;
    A.emplace_back(mp(a, b));
  }
  for (int i = 0; i < N; i++){
    int a,b;
    cin >> a >> b;
    B.emplace_back(mp(a, b));
  }
  int src = 0;
  int tar = 2 * N + 1;

  for (int i = 0; i < A.size(); i++){
    for (int j = 0; j < B.size(); j++){
      int a = i + 1;
      int b = N + j + 1;
      if (A[i].first < B[j].first and A[i].second < B[j].second){
	add_edge(a, b, 1);
      }
    }
  }

  for (int i = 0; i < N; i++){
    int a = i + 1;
    int b = N + i + 1;
    add_edge(src, a, 1);
    add_edge(b, tar, 1);
  }
  int res = ford_fulkerson(src, tar);
  cout << res << endl;
  return 0;
}
