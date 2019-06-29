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
int S, T;
const int MAX_NM = 100100;
vector<int> edges[MAX_NM];
int costs[MAX_NM][4];
void init()
{
    for (int i = 0; i < MAX_NM; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            costs[i][j] = INF;
        }
    }
}
void dijkstra()
{
    init();
    min_priority_queue<tuple<int, int, int>> min_que;
    min_que.emplace(mt(0, S, 0));
    while (not min_que.empty())
    {
        auto p = min_que.top();
        min_que.pop();
        int cost, pos, cnt;
        tie(cost, pos, cnt) = p;
        // cerr << pos << " " << cost << " " << cnt << " " << costs[pos][cnt] << endl;
        if (costs[pos][cnt] <= cost)
        {
            continue;
        }
        costs[pos][cnt] = cost;

        int nxt_cnt = cnt + 1;
        int nxt_cost = cost;
        if (nxt_cnt > 3)
        {
            nxt_cost += 1;
            nxt_cnt = 1;
        }
        for (auto &nxt : edges[pos])
        {
            if (costs[nxt][nxt_cnt] >= nxt_cost)
            {
                min_que.emplace(nxt_cost, nxt, nxt_cnt);
            }
        }
    }
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        edges[u].push_back(v);
    }
    cin >> S >> T;
    S--, T--;
    dijkstra();
    int res = costs[T][3] == INF ? -1 : costs[T][3] + 1;
    cout << res << endl;
    return 0;
}
