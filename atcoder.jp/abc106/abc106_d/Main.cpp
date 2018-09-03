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
const int MAX_N = 510;
ll cnts[MAX_N][MAX_N];
int N, M, Q;
int main()
{
  cin >> N >> M >> Q;
  for (int i = 0; i < M; i++)
  {
    int L, R;
    cin >> L >> R;
    cnts[R][L]++;
  }
  for (int i = 0; i < MAX_N; i++)
  {
    for (int j = 1; j < MAX_N; j++)
    {
      cnts[i][j] += cnts[i][j - 1];
    }
  }
  
  for (int i = 0; i < Q; i++)
  {
    int p, q;
    cin >> p >> q;
    ll res = 0;
    for (int j = p; j <= q; j++)
    {
      res += cnts[j][q] - cnts[j][p - 1];
    }
    cout << res << endl;
  }
  return 0;
}
