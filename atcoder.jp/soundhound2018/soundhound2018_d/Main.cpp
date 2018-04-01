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
int H, W;
const int MAX_H = 11;
const int MAX_W = 50010;
vector<vector<ll>> P, F;
vector<ll> update(const vector<ll> &dp, const vector<ll> &P, const vector<ll> &F)
{
    vector<ll> left(W), right(W);
    for (int i = 1; i < W; i++)
    {
        left[i] = max(P[i - 1] - F[i - 1], left[i - 1] + P[i - 1] - 2 * F[i - 1]);
    }
    for (int i = W - 2; i >= 0; i--)
    {
        right[i] = max(P[i + 1] - F[i + 1], right[i + 1] + P[i + 1] - 2 * F[i + 1]);
    }
    ll ma = -LL_INF;
    vector<ll> results(W);
    for (int i = 0; i < W; i++)
    {
        ll a = ma + P[i] - F[i];
        ll b = dp[i] + left[i] + P[i] - 2 * F[i];
        ll c = dp[i] + P[i] - F[i];
        ma = max(a, max(b, c));
        results[i] = max(ma, ma + right[i] - F[i]);
    }
    return results;
}
int main()
{
    cin >> H >> W;
    P.resize(H, vector<ll>(W));
    F.resize(H, vector<ll>(W));
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> P[i][j];
        }
    }
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            cin >> F[i][j];
        }
    }

    vector<ll> dp(W, -LL_INF);
    dp[0] = 0;
    for (int i = 0; i < H; i++)
    {
        vector<ll> res1 = update(dp, P[i], F[i]);
        reverse(dp.begin(), dp.end());
        reverse(P[i].begin(), P[i].end());
        reverse(F[i].begin(), F[i].end());
        vector<ll> res2 = update(dp, P[i], F[i]);
        for (int i = 0; i < W; i++)
        {
            dp[i] = max(res1[i], res2[W - 1 - i]);
        }
    }
    for (int i = 0; i < W; i++)
    {
        cout << dp[i] << endl;
    }
    return 0;
}
