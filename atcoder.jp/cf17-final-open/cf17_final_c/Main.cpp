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
int N;
const int MAX_N = 51;
vector<int> times;
bool dp[2][1 << 24];
int main() {
  cin >> N;
  times.resize(N);
  for (auto &val : times){
    cin >> val;
  }
  sort(times.begin(), times.end());
  if (times[0] == 0){
    cout << 0 << endl;
    return 0;
  }

  memset(dp, false, sizeof(dp));
  dp[0][1] = true;
  for (int i = 0; i < N; i++){
    for (int bit = 0; bit < (1 << 24); bit++){
      if (dp[i%2][bit]){
        int t1 = times[i];
        int t2 = 24 - times[i];
        if (((bit >> t1)&1) == 0){
            dp[(i + 1) % 2][bit | (1 << t1)] = true;
        }
        if (((bit >> t2)&1) == 0){
            dp[(i + 1) % 2][bit | (1 << t2)] = true;
        }
      }
    }

    for (int bit = 0; bit < (1 << 24); bit++){
      dp[i%2][bit] = false;
    }
  }
  int result = 0;
  for (int bit = 0; bit < (1 << 24); bit++){
    if (dp[N % 2][bit] == 0)continue;
    int res = INF;
    for (int i = 0; i <= 24; i++){
      for (int j = i + 1; j <= 24; j++){
        if (((bit >> i)&1) and ((bit >> j) &1)){
          res = min(res, min(j - i, 24 - (j - i)));
        }
      }
    }
    if (res == INF)continue;
    result = max(result, res);
  }
  cout << result << endl;
  return 0;
}
