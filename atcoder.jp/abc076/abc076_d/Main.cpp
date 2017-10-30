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
const int MAX_NV = 110;
const int MAX_T = 210;
 
int N;
vector<int> T,V;
map<int, int> limits;
double dp[MAX_NV * MAX_T * 2][MAX_NV * 2];
int sum;
double memo(int pos, int v){
    if (v < 0){
      return -INF;
    }
 
    if (v > limits[pos]){
      return -INF;
    }
    if (pos >= sum){
      if (v == 0){
        return 0;
      }
      return -INF;
    }
 
    double &res = dp[pos][v];
    if (res > -2 * INF){
      return res;
    }
    res = -INF;
    res = max(res, memo(pos + 1, v) + v);
    if (v < limits[pos]){
      res = max(res, memo(pos + 1, v + 1) + v + 0.5);
    }
    res = max(res, memo(pos + 1, v - 1) + v - 0.5);
    return res;
}
 
int main() {
  cin >> N;
  T.resize(N);
  V.resize(N);
  for (int i = 0; i < N; i++){
    cin >> T[i];
    T[i] *= 2;
    sum += T[i];
  }
  for (int i = 0; i < N; i++){
    cin >> V[i];
    V[i] *= 2;
  }
  for (int i = 1; i < N; i++){
    T[i] += T[i - 1];
  }
  int pre = 0;
  for (int i = 0; i < N; i++){
    for (int j = pre; j <= T[i]; j++){
      limits[j] = V[i];
    }
    pre = T[i];
  }
  // double dp[MAX_NV * MAX_T][MAX_NV * 2];
  for (int i = 0; i < MAX_NV * MAX_T * 2; i++){
    for (int j = 0; j < MAX_NV * 2; j++){
      dp[i][j] = -2 * INF;
    }
  }
  double result = (double)memo(0, 0) / 4;
  if (result <= 0){
    result = 0;
  }
  printf("%.20lf\n", result);
  return 0;
}