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
int N;
vector<int> C;
const int MAX_N = 200010;

ll dp[MAX_N];
vector<int> indices[MAX_N];
map<int, int> map_nxt_index;
ll memo(int pos)
{

    if (pos >= N)
    {
        return 1;
    }
    ll &res = dp[pos];
    if (res >= 0)
    {
        return res;
    }
    res = 0;
    res += memo(pos + 1);
    res %= MOD;
    if (map_nxt_index.count(pos) > 0)
    {
        res += memo(map_nxt_index[pos]);
        res %= MOD;
    }
    return res;
}
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    memset(dp, -1, sizeof(dp));
    cin >> N;
    C.resize(N);
    for (auto &val : C)
    {
        cin >> val;
    }
    //erase
    C.erase(unique(C.begin(), C.end()), C.end());
    N = C.size();
    for (int i = 0; i < C.size(); i++)
    {
        indices[C[i]].push_back(i);
    }

    for (int i = 0; i < MAX_N; i++)
    {
        if (indices[i].size() < 2)
        {
            continue;
        }

        int pre = indices[i][0];

        for (int j = 1; j < indices[i].size(); j++)
        {

            map_nxt_index[pre] = indices[i][j];
            pre = indices[i][j];
        }
    }

    memset(dp, -1, sizeof(dp));
    cout << memo(0) % MOD << endl;
    return 0;
}
