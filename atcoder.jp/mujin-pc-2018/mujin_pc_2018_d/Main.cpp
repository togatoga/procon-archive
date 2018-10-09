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
template <class T>
using max_priority_queue = priority_queue<T>;
template <class T>
using min_priority_queue = priority_queue<T, std::vector<T>, std::greater<T>>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};

const int MAX_NM = 1000;
int dp[MAX_NM][MAX_NM];
int rev(int v)
{
  string r = to_string(v);
  reverse(r.begin(), r.end());
  return stoi(r);
}
int memo(int x, int y)
{
  // cerr << "x = " << x << " y = " << y << endl;
  if (x == 0 || y == 0)
  {
    return 1;
  }
  int &res = dp[x][y];
  if (res >= 0)
  {
    return res;
  }
  res = INF;
  if (x < y)
  {
    x = rev(x);
  }
  else
  {
    y = rev(y);
  }
  if (x < y)
  {
    y = y - x;
  }
  else
  {
    x = x - y;
  }
  res = memo(x, y);
  return res;
}

void init()
{
  memset(dp, -1, sizeof(dp));
}
int main()
{
  init();

  int N, M;
  cin >> N >> M;
  int result = 0;
  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= M; j++)
    {
      int res = memo(i, j);
      if (res == INF)
      {
        result++;
      }
    }
  }
  cout << result << endl;

  return 0;
}
