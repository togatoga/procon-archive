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
vector<pair<ll, ll>> XS;
const int MAX_N = 200010;
ll dp[MAX_N];
int main()
{
    cin >> N;
    XS.resize(N);
    for (int i = 0; i < N; i++)
    {
        ll x, s;
        cin >> x >> s;
        XS[i] = mp(x, s);
    }
    ll sum = 0;
    ll L = XS[0].first;
    ll res = 0;
    for (int i = 0; i < N; i++)
    {
        dp[i] = XS[i].second - XS[i].first + (sum + L);
        res = max(res, XS[i].second);
        res = max(res, dp[i]);
        if (sum + L + XS[i].second < XS[i].first + XS[i].second)
        {
            sum = XS[i].second;
            L = XS[i].first;
        }
        else
        {
            sum += XS[i].second;
        }
    }
    cout << res << endl;

    return 0;
}