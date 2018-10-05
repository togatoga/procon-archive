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
int K;
int main()
{
  cin >> K;
  int tmp = K;
  min_priority_queue<tuple<int, int, int, bool>> que; //(cost, mod, greater K)
  que.emplace(mt(0, 0, 0, false));
  set<pii> visited;
  int result = INF;
  while (not que.empty())
  {
    auto p = que.top();
    que.pop();
    int cost, mod, digit;
    bool greater;
    tie(cost, mod, digit, greater) = p;
    if (mod == 0 && greater)
    {
      result = min(result, cost);
      // cerr << " result = " << result << " " << cost << endl;
    }
    if (visited.count(mp(mod, greater)))
    {
      continue;
    }
    visited.emplace(mp(mod, greater));

    for (int i = 0; i <= 9; i++)
    {
      bool next_greater = greater | ((10 * mod + i) >= K);
      int next_mod = (10 * mod + i) % K;
      int next_digit = digit + 1;
      // cerr << "i = " << i << " next_mod = " << next_mod << " "<< next_greater << endl;
      if (visited.count(mp(next_mod, next_greater)))
      {
        continue;
      }
      if (cost + i > 100)
      {
        continue;
      }
      if (digit + 1 > 100000)
      {
        continue;
      }

      que.emplace(mt(cost + i, next_mod, next_digit, next_greater));
    }
  }
  cout << result << endl;

  return 0;
}
