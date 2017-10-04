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
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
const int MAX_N = 100100;
int N,M;
vector<ll> values;
vector<int> graphs[MAX_N];
bool visited[MAX_N];
int cnt;
int node;
ll result;
ll dfs(int pos){
  visited[pos] = true;
  cnt++;
  result += values[pos];
  ll res = values[pos];
  node += graphs[pos].size();
  for (const int &nxt : graphs[pos]){
    if (visited[nxt])continue;
    res = min(res, dfs(nxt));
  }
  return res;
}
int main() {
  cin >> N >> M;
  values.resize(N);
  for (int i = 0; i < N; i++){
    cin >> values[i];
  }
  for (int i = 0; i < M; i++){
    int x,y;
    cin >> x >> y;
    x--;
    y--;
    graphs[x].push_back(y);
    graphs[y].push_back(x);
  }
  for (int i = 0; i < N; i++){
    if (not visited[i]){
      cnt = node = 0;
      ll res = dfs(i);
      if (2 * (cnt - 1) >= node){
        result -= res;
      }
    }
  }
  cout << result << endl;
  return 0;
}
