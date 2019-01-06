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

const int MAX_N = 110;
const int MAX_W = 100010;
int N, W;
vector<pii> WV;
ll dp[MAX_N][MAX_W];
void init()
{
    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j < MAX_W; j++)
        {
            dp[i][j] = -1;
        }
    }
}
int main()
{
    cin >> N >> W;
    for (int i = 0; i < N; i++)
    {
        int w, v;
        cin >> w >> v;
        WV.emplace_back(mp(w, v));
    }
    ll result = 0;
    for (int i = 0; i < N; i++)
    {
        int w, v;
        tie(w, v) = WV[i];
        for (int j = 0; j <= W; j++)
        {
            if (dp[i][j] == -1)
            {
                continue;
            }
            if (j + w <= W)
            {
                dp[i + 1][j + w] = max(dp[i + 1][j + w], dp[i][j] + v);
            }
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
        }
    }
    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j < MAX_W; j++)
        {
            result = max(result, dp[i][j]);
        }
    }
    cout << result << endl;
    return 0;
}
