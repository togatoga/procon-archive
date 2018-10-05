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
int N;
int M;
string S;
enum Color
{
  RED,
  BLUE,
  NONE,
};
map<pair<string, string>, int> cnt1, cnt2;
int main()
{
  cin >> N;
  cin >> S;
  M = S.size();
  for (int bit = 0; bit < (1 << N); bit++)
  {
    string red1, blue1;
    red1 = blue1 = "";
    string red2, blue2;
    red2 = blue2 = "";
    for (int i = 0; i < N; i++)
    {
      if (((bit >> i) & 1))
      {
        red1 += S[i];
        red2 += S[i + N];
      }
      else
      {
        blue1 += S[i];
        blue2 += S[i + N];
      }
    }
    reverse(blue2.begin(), blue2.end());
    reverse(blue1.begin(), blue1.end());
    cnt2[mp(red2, blue2)]++;
    cnt1[mp(red1, blue1)]++;
  }

  ll res = 0;
  for (const auto &val : cnt1)
  {
    string s1 = val.first.first;
    string s2 = val.first.second;
    int cnt1 = val.second;
    res += (ll)cnt1 * cnt2[mp(s2, s1)];
  }
  cout << res << endl;
  return 0;
}
