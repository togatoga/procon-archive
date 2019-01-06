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
int N, W;
const int MAX_N = 110;
const int MAX_V = 100010;
vector<pii> WV;
ll dp[MAX_N][MAX_V]; //(index, value)
void init()
{
    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j < MAX_V; j++)
        {
            dp[i][j] = LL_INF;
        }
    }
}
int main()
{
    init();
    cin >> N >> W;
    for (int i = 0; i < N; i++)
    {
        int w, v;
        cin >> w >> v;
        WV.emplace_back(mp(w, v));
    }
    dp[0][0] = 0;
    for (int i = 0; i < N; i++)
    {
        int w, v;
        tie(w, v) = WV[i];
        for (int j = 0; j < MAX_V; j++)
        {
            if (j + v < MAX_V)
            {
                dp[i + 1][j + v] = min(dp[i + 1][j + v], dp[i][j] + w);
            }
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
        }
    }
    for (int j = MAX_V - 1; j >= 0; j--)
    {
        if (dp[N][j] <= W)
        {
            cout << j << endl;
            return 0;
        }
    }
    return 0;
}
