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
vector<int> A,B,C;
int main() {
  cin >> N;
  A.resize(N);
  B.resize(N);
  C.resize(N);
  for (auto &val : A){
    cin >> val;
  }
  for (auto &val : B){
    cin >> val;
  }
  for (auto &val : C){
    cin >> val;
  }
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());
  sort(C.begin(), C.end());

  ll res = 0;
  for (int i = 0; i < B.size(); i++){
    int a = lower_bound(A.begin(), A.end(), B[i]) - A.begin();
    int c = upper_bound(C.begin(), C.end(), B[i]) - C.begin();
    if (a - 1 >= 0 and a - 1 < N and c >= 0 and c < N){
      res += (ll)(a) * (N - c);
    }
  }
  cout << res << endl;
  return 0;
}
