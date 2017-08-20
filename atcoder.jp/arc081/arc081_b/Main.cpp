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
const int MAX_N = 55;
int N;
string board[2];
int dp[MAX_N][4][4];

int memo(int pos, int pre1, int pre2){
  if (pos >= N){
    return 1;
  }
  int &res = dp[pos][pre1][pre2];
  if (res >= 0){
    return res;
  }
  res = 0;
  if (board[0][pos] == board[1][pos]){//tate
    for (int i = 1; i <= 3; i++){
      if (i != pre1 and i != pre2){
        res += memo(pos + 1, i, i);
        res %= MOD;
      }
    }
  }else{
    for (int i = 1; i <= 3; i++){
      for (int j = 1; j <= 3; j++){
        if (i == j)continue;
        if (i == pre1 or j == pre2)continue;
        res += memo(pos + 2, i, j);
        res %= MOD;
      }
    }
  }


  return res;
}

int main() {
  cin >> N;
  cin >> board[0];
  cin >> board[1];
  memset(dp, -1, sizeof(dp));

  cout << memo(0, 0, 0) << endl;

  return 0;
}
