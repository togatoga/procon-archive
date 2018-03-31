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
const ll LL_INF = 1LL << 60;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
string S;
int N;
bool is_uniq(const string &T)
{
  map<char, int> cnts;
  for (const auto &val : T)
  {
    cnts[val]++;
    if (cnts[val] >= 2)
    {
      return false;
    }
  }
  return true;
}
int main()
{
  cin >> S;
  N = S.size();
  for (char i = 'a'; i <= 'z'; i++)
  {
    string tmp = S + i;
    if (is_uniq(tmp))
    {
      cout << tmp << endl;
      return 0;
    }
  }
  string result = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
  bool ok = false;
  for (int i = 0; i < N; i++)
  {
    
    for (char j = 'a'; j <= 'z'; j++)
    {
      string tmp = S.substr(0, i) + j;

      if (is_uniq(tmp) && S < tmp)
      {

        ok = true;
        result = min(result, tmp);
      }
    }
  }
  if (ok){
    cout << result << endl;
    return 0;
  }

  cout << -1 << endl;
  return 0;
}
