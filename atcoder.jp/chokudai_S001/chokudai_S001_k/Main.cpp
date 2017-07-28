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
vector<int> values;
int N;
const int MAX_N = 100010;
ll sum[MAX_N];
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
int main() {
  cin >> N;
  values.resize(N);
  for (auto &val : values){
    cin >> val;
  }
  sum[0] = 1;
  for (int i = 1; i < MAX_N; i++){
    sum[i] = (sum[i - 1] * i) % MOD;
  }
  BIT<int> bit(MAX_N);
  ll res = 0;
  for (int i = N - 1; i >= 0; i--){
    int tmp = bit.sum(values[i]);
    if (tmp > 0){
      res += tmp * sum[N - i - 1];
      res %= MOD;
    // cout << res << " " << tmp << " " << sum[N - i] << endl;
    }

    bit.add(values[i], 1);
  }
  cout << (res + 1) % MOD << endl;
  return 0;
}
