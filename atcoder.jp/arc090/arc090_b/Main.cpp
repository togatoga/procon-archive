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
int N, M;
const int MAX_N = 100010;
vector<pii> edges1[MAX_N];
vector<pii> edges[MAX_N];
int visited[MAX_N];
int costs[MAX_N];
bool parent[MAX_N];

void init()
{
    rep(i, MAX_N)
    {
        costs[i] = INF;
        parent[i] = true;
    }
}
bool dfs(int pos, int pre, int cost)
{
    if (visited[pos] != 0)
    {
        if (visited[pos] == 2)
        {
            return false;
        }
        if (cost == costs[pos])
        {
            return true;
        }
        return false;
    }

    costs[pos] = cost;
    visited[pos] = 2;
    bool ok = true;
    for (auto &val : edges[pos])
    {
        int nxt = val.first;
        int c = val.second;
        if (nxt == pre)
        {
            continue;
        }

        ok &= dfs(nxt, pre, cost + c);
    }
    visited[pos] = 1;
    return ok;
}
int main()
{
    init();
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int l, r, d;
        cin >> l >> r >> d;
        l--, r--;
        edges[l].push_back(mp(r, d));
        parent[r] = false;
    }
    if (M == 0)
    {
        cout << "Yes" << endl;
        return 0;
    }
    bool ok = true;
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        if (visited[i] != 0 || !parent[i])
        {
            continue;
        }
        if (edges[i].empty())
        {
            continue;
        }
        res++;
        // cerr << i << " " << res << endl;
        ok &= dfs(i, -1, 0);
    }

    if (ok && res > 0)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}
