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
ll A, B, Q;
vector<ll> S, T;
int main()
{
    cin >> A >> B >> Q;
    S.resize(A);
    T.resize(B);
    for (auto &val : S)
    {
        cin >> val;
    }
    for (auto &val : T)
    {
        cin >> val;
    }
    for (int i = 0; i < Q; i++)
    {
        ll x;
        cin >> x;
        vector<ll> s_points;
        int s1 = lower_bound(S.begin(), S.end(), x) - S.begin();
        s_points.emplace_back(S[s1]);

        if (s1 > 0)
        {
            int s2 = s1 - 1;
            s_points.emplace_back(S[s2]);
        }
        vector<ll> t_points;
        int t1 = lower_bound(T.begin(), T.end(), x) - T.begin();
        t_points.emplace_back(T[t1]);
        if (t1 > 0)
        {
            int t2 = t1 - 1;
            t_points.emplace_back(T[t2]);
        }
        ll result = LL_INF;
        for (int i = 0; i < s_points.size(); i++)
        {
            for (int j = 0; j < t_points.size(); j++)
            {
                ll l = min(s_points[i], t_points[j]);
                ll r = max(s_points[i], t_points[j]);
                ll c1 = abs(l - x);
                ll c2 = abs(r - x);
                if (l <= x && x <= r)
                {
                    result = min(result, min(2 * c1 + c2, 2 * c2 + c1));
                }
                else
                {
                    result = min(result, max(c1, c2));
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}
