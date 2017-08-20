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
int N;
vector<ll> A;
map<ll, int> cnt;
int main() {

  cin >> N;
  A.resize(N);
  for (auto &val : A){
    cin >> val;
    cnt[val]++;
  }
  sort(A.begin(), A.end());
  ll result = 0;
  ll a = 0;
  for (const auto &val : cnt){
    if (val.second >= 4){
      result = max(result, val.first * val.first);
    }
    if (val.second >= 2){
      result = max(result, val.first * a);
      a = max(a, val.first);
    }
  }
  cout << result << endl;
  return 0;
}
