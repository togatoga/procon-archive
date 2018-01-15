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
const ll LL_INF = 1LL << 61;
const double EPS = 1e-9;
const ll MOD = 1000000007;

const int dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
ll N, K;
vector<pair<ll, ll>> WD;
bool ok1(ll val)
{
    ll res = 0;
    for (int i = 0; i < N; i++)
    {
        ll w = WD[i].first;
        ll d = WD[i].second;
        if (val < w)
        {
            continue;
        }
        res++;
        res += (val - w) / d;
        if (res >= K)
        {
            return true;
        }
    }
    return res >= K;
}

int main()
{
    cin >> N >> K;
    WD.resize(N);
    for (int i = 0; i < N; i++)
    {
        cin >> WD[i].first >> WD[i].second;
    }
    sort(WD.begin(), WD.end());
    ll left, right;
    left = 0;
    right = LL_INF;
    while (right - left > 1)
    {
        ll med = (right + left) / 2;
        if (med < 0)
        {
            left = med;
            continue;
        }
        if (ok1(med))
        {
            right = med;
        }
        else
        {
            left = med;
        }
    }
    cout << left + 1 << endl;

    // cout << right2 << endl;
    return 0;
}
