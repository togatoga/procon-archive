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
const int MAX_N = 2010;
int board[MAX_N][MAX_N];
void init()
{
  for (int i = 0; i < MAX_N; i++)
  {
    for (int j = 0; j < MAX_N; j++)
    {
      board[i][j] = 1;
    }
  }
}
const int RIGHT = 0;
const int TOP = 1;
const int LEFT = 2;
const int BOTTOM = 3;
ll sum[MAX_N][MAX_N][4];

void calc_right()
{

  for (int i = 1; i <= N; i++)
  {
    int cnt = 0;
    for (int j = M; j >= 1; j--)
    {
      sum[i][j][RIGHT] = cnt;
      if (board[i][j] == 0)
      {
        cnt++;
      }
      else
      {
        cnt = 0;
      }
    }
  }
}

void calc_top()
{

  for (int j = 1; j <= M; j++)
  {
    int cnt = 0;
    for (int i = 1; i <= N; i++)
    {
      sum[i][j][TOP] = cnt;
      if (board[i][j] == 0)
      {
        cnt++;
      }
      else
      {
        cnt = 0;
      }
    }
  }
}

void calc_left()
{

  for (int i = 1; i <= N; i++)
  {
    int cnt = 0;
    for (int j = 1; j <= M; j++)
    {
      sum[i][j][LEFT] = cnt;
      if (board[i][j] == 0)
      {
        cnt++;
      }
      else
      {
        cnt = 0;
      }
    }
  }
}

void calc_bottom()
{

  for (int j = 1; j <= M; j++)
  {
    int cnt = 0;
    for (int i = N; i >= 1; i--)
    {
      sum[i][j][BOTTOM] = cnt;
      if (board[i][j] == 0)
      {
        cnt++;
      }
      else
      {
        cnt = 0;
      }
    }
  }
}

int main()
{
  init();
  cin >> N >> M;
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      char c;
      cin >> c;
      if (c == '.')
      {
        board[i + 1][j + 1] = 0;
      }
    }
  }
  calc_right();
  calc_top();
  calc_left();
  calc_bottom();

  ll result = 0;
  for (int i = 1; i <= N; i++)
  {
    for (int j = 1; j <= M; j++)
    {
      if (board[i][j] == 1)
      {
        continue;
      }
      ll tmp = 0;
      tmp += sum[i][j][RIGHT] * sum[i][j][TOP];
      tmp += sum[i][j][TOP] * sum[i][j][LEFT];
      tmp += sum[i][j][LEFT] * sum[i][j][BOTTOM];
      tmp += sum[i][j][BOTTOM] * sum[i][j][RIGHT];
      result += tmp;
      // cerr << i << " " << j << " " << tmp << " " << result << endl;
    }
  }
  cout << result << endl;
  return 0;
}
