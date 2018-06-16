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
vector<tuple<ll, ll, ll>> ABC;
ll solve(int a, int b, int c)
{
    vector<ll> tmp;
    for (int i = 0; i < N; i++)
    {
        ll A, B, C;
        tie(A, B, C) = ABC[i];
        if (a == 1)
        {
            A *= -1;
        }
        if (b == 1)
        {
            B *= -1;
        }
        if (c == 1)
        {
            C *= -1;
        }
        tmp.push_back(A + B + C);
    }
    sort(tmp.rbegin(), tmp.rend());
    ll res = 0;
    for (int i = 0; i < M; i++)
    {
        res += tmp[i];
    }
    return res;
}
int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        ll a, b, c;
        cin >> a >> b >> c;
        ABC.emplace_back(mt(a, b, c));
    }
    ll result = -LL_INF;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                result = max(result, solve(i, j, k));
            }
        }
    }
    cout << result << endl;
    return 0;
}
