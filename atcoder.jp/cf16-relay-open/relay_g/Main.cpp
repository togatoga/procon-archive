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
int N,Q;
const int MAX_N = 100100;
bool dp[MAX_N][2];
int main() {
  cin >> N >> Q;
  dp[0][0] = true;
  for (int i = 0; i < Q; i++){
    int a,b;
    cin >> a >> b;
    a--,b--;
    if (dp[a][0]){
      if (a - 1 >= 0){
        dp[a - 1][1] = true;
      }
      if (a + 1 < N){
        dp[a + 1][1] = true;
      }
    }
    if (dp[b][0]){
      if (b - 1 >= 0){
        dp[b - 1][1] = true;
      }
      if (b + 1 < N){
        dp[b + 1][1] = true;
      }
    }

    bool a0,b0;
    a0 = b0 = false;
    bool a1,b1;
    a1 = b1 = false;
    if (dp[a][0]){
      b0 |= true;
    }
    if (dp[a][1]){
      b1 |= true;
    }
    if (dp[b][0]){
      a0 |= true;
    }
    if (dp[b][1]){
      a1 |= true;
    }
    if (a - 1 >= 0 and dp[a - 1][0]){
      b1 |= true;
    }
    if (a + 1 < N and dp[a + 1][0]){
      b1 |= true;
    }
    if (b - 1 >= 0 and dp[b - 1][0]){
      a1 |= true;
    }
    if (b + 1 < N and dp[b + 1][0]){
      a1 |= true;
    }
    dp[a][0] = a0;
    dp[a][1] = a1;
    dp[b][0] = b0;
    dp[b][1] = b1;

  }

  int cnt = 0;
  for (int i = 0; i < N; i++){
    if (i - 1 >= 0){
      dp[i - 1][1] |= dp[i][0];
    }
    if (i + 1 < N){
      dp[i + 1][1] |= dp[i][0];
    }
  }
  for (int i = 0; i < N; i++){
    cnt += (dp[i][0] | dp[i][1]);
  }
  cout << cnt << endl;
  return 0;
}
