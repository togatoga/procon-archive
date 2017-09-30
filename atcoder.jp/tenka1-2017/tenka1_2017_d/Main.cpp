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
vector<ll> A,B;
ll N,K;
ll solve(int border){
  ll mask = (1LL << border);
  ll bit = K;
  if ((K & mask) != 0){
    bit |= (mask - 1);
    bit ^= mask;
  }
  ll res = 0;
  for (int i = 0; i < A.size(); i++){
    if ((A[i] | bit) == bit){
      res += B[i];
    }
  }
  return res;
}
int main() {
  cin >> N >> K;
  A.resize(N);
  B.resize(N);
  for (int i = 0; i < N; i++){
    cin >> A[i] >> B[i];
  }
  ll ans = 0;
  for (int i = 0; i < 32; i++){
    ans = max(ans, solve(i));
  }
  cout << ans << endl;
  return 0;
}
