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
vector<int> P;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);

    cin >> N;
    P.resize(N);
    for (auto &val : P)
    {
        cin >> val;
    }
    vector<int> ord(N);
    for (int i = 0; i < N; i++)
    {
        ord[i] = i;
    }
    sort(ord.begin(), ord.end(), [&](int i, int j) {
        return P[i] > P[j];
    });
    multiset<int> s;
    ll ans = 0;
    s.insert(N);
    s.insert(N);
    s.insert(-1);
    s.insert(-1);
    ll result = 0;
    for (auto i : ord)
    {
        auto iter = s.lower_bound(i);
        ll idx1 = *iter;
        ++iter;
        ll idx2 = *iter;
        --iter;
        --iter;
        ll idx3 = *iter;
        --iter;
        ll idx4 = *iter;
        result += P[i] * (idx2 - idx1) * (i - idx3);
        result += P[i] * (idx3 - idx4) * (idx1 - i);
        s.insert(i);
    }
    cout << result << endl;
    return 0;
}
