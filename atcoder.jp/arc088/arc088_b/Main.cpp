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
string S;
int result;
int main() {
  cin >> S;
  N = S.size();
  result = N / 2;
  int left, right;
  if (N % 2 == 0) {
    left = N / 2 - 1;
    right = left + 1;
  } else {
    left = N / 2;
    right = left;
  }
  char c = S[left];
  while (left >= 0 and right < N) {
    if (c == S[left] and c == S[right]) {
      left--;
      right++;
      result++;
    } else {
      break;
    }
  }
  cout << result << endl;
  return 0;
}
