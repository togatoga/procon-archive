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
const int MAX_N = 200100;
string S;
int N;
ll result;
map<char, int> deg;
int main() {

  cin >> S;
  N = S.size();

  result = (ll) N * (N + 1) / 2;
  for (int i = 0; i < S.size(); i++){
    deg[S[i]]++;
  }
  ll tmp = 0;
  for (char i = 'a'; i <= 'z'; i++){
    tmp += (ll)deg[i] * (deg[i] + 1) / 2;
  }
  cout << result - tmp + 1<< endl;
  return 0;
}
