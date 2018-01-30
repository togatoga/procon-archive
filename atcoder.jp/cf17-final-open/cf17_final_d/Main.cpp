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
int N;
const int MAX_N = 5010;
struct State
{
    ll H, P;
    State() {}
    State(ll h, ll p) : H(h), P(p) {}
    bool operator<(const State &right) const
    {
        return H + P < right.H + right.P;
    }
};
vector<State> tasks;
ll dp[MAX_N][MAX_N];
void init()
{
    rep(i, MAX_N)
    {
        rep(j, MAX_N)
        {
            dp[i][j] = LL_INF;
        }
    }
}
int main()
{
    init();
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int h, p;
        cin >> h >> p;
        tasks.emplace_back(State(h, p));
    }
    sort(tasks.begin(), tasks.end());
    dp[0][0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (dp[i][j] == LL_INF)
            {
                continue;
            }
            ll h = tasks[i].H;
            ll p = tasks[i].P;
            if (dp[i][j] > h)
            {
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                continue;
            }
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
            dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + p);
        }
    }
    for (int j = N; j >= 0; j--)
    {
        if (dp[N][j] != LL_INF)
        {
            cout << j << endl;
            return 0;
        }
    }
    return 0;
}
