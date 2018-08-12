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
template <class T> using max_priority_queue = priority_queue<T>;
template <class T>
using min_priority_queue = priority_queue<T, std::vector<T>, std::greater<T>>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
string S;
int N;
const int MAX_N = 100100;
ll dp[MAX_N][4];
int main() {
  cin >> S;
  N = S.size();
  dp[0][0] = 1;
  for (int i = 0; i < N; i++) {
    dp[i][0] %= MOD;
    const char c = S[i];
    const ll p = c == '?' ? 3 : 1;
    dp[i + 1][0] += p * dp[i][0];
    dp[i + 1][1] += p * dp[i][1];
    dp[i + 1][2] += p * dp[i][2];
    dp[i + 1][3] += p * dp[i][3];
    if (c == 'A') {
      dp[i + 1][1] += dp[i][0];
    } else if (c == 'B') {
      dp[i + 1][2] += dp[i][1];
    } else if (c == 'C') {
      dp[i + 1][3] += dp[i][2];
    } else {
      dp[i + 1][1] += dp[i][0];
      dp[i + 1][2] += dp[i][1];
      dp[i + 1][3] += dp[i][2];
    }
    dp[i + 1][1] %= MOD;
    dp[i + 1][2] %= MOD;
    dp[i + 1][3] %= MOD;
  }
  cout << dp[N][3] % MOD << endl;
  return 0;
}
