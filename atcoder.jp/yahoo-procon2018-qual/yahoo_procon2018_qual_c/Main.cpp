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
vector<ll> X, C, V;
const int MAX_N = 19;
ll dp[MAX_N][1 << MAX_N];
ll memo[MAX_N][1 << MAX_N];
ll f(int n, int bit)
{
    if (n >= N)
    {
        return 0;
    }
    ll &res = memo[n][bit];
    if (res >= 0)
    {
        return res;
    }
    ll sold = LL_INF;
    for (int i = 0; i <= N; i++)
    {
        if (bit & (1 << i))
        {
            sold = min(sold, f(n + 1, bit - (1 << i)));
        }
    }
    ll buy = dp[n][bit];
    res = max(sold, buy);
    return res;
}
int main()
{
    cin >> N;
    X.resize(N);
    C.resize(N);
    V.resize(N);
    for (auto &val : X)
    {
        cin >> val;
    }
    for (auto &val : C)
    {
        cin >> val;
    }
    for (auto &val : V)
    {
        cin >> val;
    }
    for (int n = 0; n <= N; n++)
    {
        ll yen = 0;
        for (int i = 0; i < n; i++)
        {
            yen += X[i];
        }
        for (int bit = 0; bit < (1 << N); bit++)
        {
            ll co = 0, va = 0;
            for (int i = 0; i < N; i++)
            {
                if (bit & (1 << i))
                {
                    co += C[i];
                    va += V[i];
                }
            }
            if (co <= yen)
            {
                dp[n][bit] = va;
            }
            else
            {
                dp[n][bit] = 0;
            }
        }

        for (int bit = 0; bit < (1 << N); bit++)
        {
            for (int i = 0; i < N; i++)
            {
                if (bit & (1 << i))
                {
                    dp[n][bit] = max(dp[n][bit], dp[n][bit ^ (1 << i)]);
                }
            }
        }
    }
    memset(memo, -1, sizeof(memo));
    cout << f(0, (1 << N) - 1) << endl;

    return 0;
}
