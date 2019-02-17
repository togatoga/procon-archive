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
template <class T>
using max_priority_queue = priority_queue<T>;
template <class T>
using min_priority_queue = priority_queue<T, std::vector<T>, std::greater<T>>;

const int INF = 1 << 29;
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
int N, M;
set<int> available_numbers;
const int MAX_N = 10100;
int costs[MAX_N];
int dp[MAX_N];

int main()
{
  cin >> N >> M;
  for (int i = 0; i < M; i++)
  {
    int x;
    cin >> x;
    available_numbers.insert(x);
  }
  costs[1] = 2;
  costs[2] = 5;
  costs[3] = 5;
  costs[4] = 4;
  costs[5] = 5;
  costs[6] = 6;
  costs[7] = 3;
  costs[8] = 7;
  costs[9] = 6;

  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  for (int i = 0; i <= N; i++)
  {
    for (int j = 9; j >= 1; j--)
    {
      if (dp[i] == -1 || available_numbers.count(j) == 0)
      {
        continue;
      }

      if (dp[i] + 1 > dp[i + costs[j]])
      {
        dp[i + costs[j]] = dp[i] + 1;
      }
    }
  }
  int pos = N;
  string result = "";
  while (pos > 0)
  {
    for (int i = 9; i >= 1; i--)
    {
      if (available_numbers.count(i) == 0)
      {
        continue;
      }
      if (pos - costs[i] >= 0 && dp[pos - costs[i]] == dp[pos] - 1)
      {
        result += to_string(i);
        pos -= costs[i];
        break;
      }
    }
  }
  cout << result << endl;
  return 0;
}