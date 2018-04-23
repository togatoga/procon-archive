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
int N;
ll C;
vector<pair<ll, ll>> xy;
ll result;
int main() {
  cin >> N >> C;
  xy.resize(N);

  for (int i = 0; i < N; i++) {
    cin >> xy[i].first >> xy[i].second;
  }
  if (N == 1){
    result = max(result, xy[0].second - min(C - xy[0].first, xy[0].first));
    cout << result << endl;
    return 0;
  }
  vector<ll> lst, rst;
  ll lsum, rsum;
  lsum = rsum = 0;
  // right
  for (int i = N - 1; i >= 0; i--) {
    ll tmp = xy[i].second + rsum - (C - xy[i].first);
    if (not rst.empty()) {
      tmp = max(tmp, rst.back());
    }
    rst.emplace_back(tmp);
    rsum += xy[i].second;
  }
  // left
  for (int i = 0; i < N; i++) {
    ll tmp = xy[i].second - xy[i].first + lsum;
    if (not lst.empty()) {
      tmp = max(tmp, lst.back());
    }
    lst.emplace_back(tmp);
    lsum += xy[i].second;
  }
  lsum = 0;
  // 2 * left + right
  for (int i = 0; i < N; i++) {
    ll left, right;
    left = right = 0;
    left = xy[i].second - xy[i].first + lsum;
    if (i != N - 1) {
      right = max(0LL, rst[N - 2 - i] - xy[i].first);
    }
    result = max(result, left + right);
    lsum += xy[i].second;
  }
  // left + 2 * right
  rsum = 0;
  for (int i = 0; i < N; i++) {
    ll left, right;
    left = right = 0;
    right = xy[N - 1 - i].second + rsum -(C - xy[N - 1 - i].first);
    if (i != N - 1) {
      left = max(0LL, lst[N - 2 - i] - (C - xy[N - 1 - i].first));
    }
    result = max(result, left + right);
    rsum += xy[N - 1 - i].second;
  }
  cout << result << endl;
  return 0;
}
