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
const int MAX_N = 200100;
const int MAX_C = 30;
int N;
string A;
int dp[MAX_N];
int nxt[MAX_N][MAX_C];
int restore[MAX_N];
int main() {
  cin >> A;
  N = A.size();
  for (int j = 0; j < MAX_C; j++){
      nxt[N][j] = N;
  }
  for (int i = N-1; i >= 0 ; i--){
      dp[i] = INF;
      for (int j = 0; j < MAX_C; j++){
          nxt[i][j] = nxt[i + 1][j];
          if (A[i] - 'a' == j){
              nxt[i][j] = i;
          }
      }
  }
  memset(restore, -1, sizeof(restore));
  dp[N] = 1;
  for (int i = N-1; i >= 0; i--){
      for (char j = 'a'; j <= 'z'; j++){
          const int p = j - 'a';
          if (dp[nxt[i][p] + 1] + 1 < dp[i]){
              restore[i] = p;
              dp[i] = dp[nxt[i][p] + 1] + 1;
          }
      }
  }
  int res = dp[0];
  int pos = 0;
  string result = "";
  while (result.size() < res){
      if (restore[pos] != -1){
          result += char('a' + restore[pos]);
          pos = nxt[pos][restore[pos]] + 1;
      }else{
          pos++;
      }

  }
  cout << result << endl;
  return 0;
}
