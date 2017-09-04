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
const int MAX_K = 100010;
ll X,K;
vector<int> r;
int main() {
  cin >> X;
  cin >> K;
  r.resize(K + 1);
  for (int i = 0; i < K; i++){
    cin >> r[i + 1];
  }
  vector<ll> el(K + 1),em(K + 1), en(K + 1);
  vector<ll> curdir(K + 1);
  el[0] = 0;
  em[0] = X;
  en[0] = 0;
  ll dir = -1;
  curdir[0]= -1;
  for (int i = 0; i < K; i++){
    ll pass = r[i + 1] - r[i];
    en[i + 1] = en[i] + dir * pass;
    em[i + 1] = max(0LL, min(X, em[i] + dir * pass));
    el[i + 1] = max(0LL, min(X, el[i] + dir * pass));
    dir *= -1;
    curdir[i + 1] = dir;
  }
  int Q;
  cin >> Q;
  for (int i = 0; i < Q; i++){
    ll t,a;
    cin >> t >> a;
    int idx = upper_bound(r.begin(), r.end(), t) - r.begin() - 1;
    ll diff = t - r[idx];
    ll base = max(el[idx], min(em[idx], a + en[idx]));
    ll ans = max(0LL, min(X, base + curdir[idx] * diff));
    cout << ans << endl;
  }
  return 0;
}
