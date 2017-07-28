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

template <class T> class BIT {
public:
  BIT() {}
  BIT(int N) : N(N) { dat.assign(N, 0); }
  // sum [0,i)
  T sum(int i) {
    T ret = 0;
    for (--i; i >= 0; i = (i & (i + 1)) - 1)
      ret += dat[i];
    return ret;
  }
  // sum [i,j)
  T sum(int i, int j) { return sum(j) - sum(i); }
  // add x to i
  void add(int i, T x) {
    for (; i < N; i |= i + 1)
      dat[i] += x;
  }
  int size() { return N; }

private:
  int N;
  vector<T> dat;
};
int N;
vector<int> values;
const int MAX_N = 100010;
int main() {
  cin >> N;
  values.resize(N);
  ll ans = 0;
  BIT<ll> bit(MAX_N);
  for (int i = 0; i < N; i++){
    int a;
    cin >> a;
    ans += i - bit.sum(a);
    bit.add(a, 1);
  }
  cout << ans << endl;
  return 0;
}
