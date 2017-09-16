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
#include <assert.h>

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
const int MAX_N = 1010;
const int MAX_X = 5010;
int N;
vector<int> edges[MAX_N];
vector<int> X;
bool dp[MAX_N][MAX_X];
int dfs(int pos){
  if (edges[pos].empty()){
    return 0;
  }
  vector<int> x,y;
  int result = 0;
  for (const auto &next : edges[pos]){
    int tmpx = X[next];
    int tmpy = dfs(next);
    if (tmpy == -1){
      return -1;
    }
    x.push_back(tmpx);
    y.push_back(tmpy);
    result += tmpx + tmpy;
  }

  int M = x.size();
  int W = X[pos];
  memset(dp, false, sizeof(dp));
  dp[0][0] = true;

  for (int i = 0; i < M; i++){
    for (int j = 0; j <= W; j++){
      if (not dp[i][j])continue;
      if (j + x[i] <= W){
        dp[i + 1][j + x[i]] = true;
      }
      if (j + y[i] <= W){
        dp[i + 1][j + y[i]] = true;
      }
    }
  }
  int tmp = -1;
  for (int j = 0; j <= W; j++){
    if (dp[M][j]){
      tmp = j;
    }
  }

  if (tmp == -1){
    return -1;
  }

  return result - tmp;
}

int main() {
  cin >> N;
  for (int i = 0; i < N-1; i++){
    int x;
    cin >> x;
    x--;
    edges[x].push_back(i + 1);
  }
  X.resize(N);
  // cerr << "N = " << N << endl;
  for (auto &val : X){
    cin >> val;

  }
  // cerr << "X.size() = " << X.size() << endl;
  if (dfs(0) != -1){// root is white
    cout << "POSSIBLE" << endl;
  }else{
    cout << "IMPOSSIBLE" << endl;
  }
  return 0;
}
