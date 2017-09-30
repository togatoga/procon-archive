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
ll N;
void solve(ll N){
  for (ll h = 1; h <= 3500; h++){
    for (ll w = 1; w <= 3500; w++){
      ll a = h * w * N;
      ll b = 4 * h * w - N * w - N * h;
      if (b == 0){
        continue;
      }
      if (a <= 0 or b <= 0){
        continue;
      }
      if (a % b == 0){
        cout << h << " " << w << " " << a / b << endl;
        return ;
      }
    }
  }
}
int main() {
  cin >> N;
  solve(N);
  return 0;
}
