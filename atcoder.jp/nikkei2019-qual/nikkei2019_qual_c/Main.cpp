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
max_priority_queue<tuple<ll, int>> mque;

vector<pair<ll, ll>> AB;
int main()
{

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        ll a, b;
        cin >> a >> b;
        AB.emplace_back(mp(a, b));
        mque.emplace(mt(a + b, i));
    }
    set<int> used;
    bool turn = true;
    ll result = 0;
    while (used.size() < N)
    {
        auto p = mque.top();
        mque.pop();
        ll v;
        int idx;
        tie(v, idx) = p;
        if (used.count(idx) > 0)
        {
            continue;
        }
        if (turn)
        {
            result += AB[idx].first;
        }
        else
        {
            result -= AB[idx].second;
        }
        used.insert(idx);
        // cout << result << " " << used.size() << endl;
        turn = !turn;
    }
    cout << result << endl;
    return 0;
}
