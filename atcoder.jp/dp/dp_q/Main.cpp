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
// http://codeforces.com/contest/777/submission/25058525
// SegmentTreeMax
template <typename ValueType>
class SegmentTreeMax
{
  public:
    SegmentTreeMax() {}
    SegmentTreeMax(int n, ValueType max_value)
    {
        this->N = 1;
        this->max_value = max_value;
        while (this->N < n)
            this->N *= 2;
        this->data.resize(2 * N - 1, this->max_value);
    }
    // init
    void init(int n, ValueType max_value)
    {
        this->N = 1;
        this->max_value = max_value;
        while (this->N < n)
            this->N *= 2;
        this->data.resize(2 * N - 1, this->max_value);
    }
    // update k th element
    void update(int k, ValueType val)
    {
        k += N - 1;
        data[k] = val;
        while (k > 0)
        {
            k = (k - 1) / 2;
            data[k] = std::max(data[2 * k + 1], data[2 * k + 2]);
        }
    }
    // Max [a, b)
    ValueType max(int a, int b) { return max(a, b, 0, 0, N); }
    ValueType max(int a, int b, int k, int l, int r)
    {
        if (r <= a or b <= l)
            return max_value;
        if (a <= l and r <= b)
            return data[k];
        int med = (l + r) / 2;
        return std::max(max(a, b, 2 * k + 1, l, med), max(a, b, 2 * k + 2, med, r));
    }

  private:
    std::vector<ValueType> data;
    int N;
    ValueType max_value;
};
///////////////////////////////////////

int N;
vector<pii> HA;
const int MAX_N = 200100;
map<int, ll> dp;
int main()
{
    cin >> N;
    HA.resize(N);
    SegmentTreeMax<ll> seg;
    seg.init(MAX_N, 0);
    for (auto &val : HA)
    {
        cin >> val.first;
    }
    for (auto &val : HA)
    {
        cin >> val.second;
    }
    seg.update(HA[0].first, HA[0].second);
    for (int i = 1; i < N; i++)
    {
        ll val = seg.max(0, HA[i].first);
        seg.update(HA[i].first, val + HA[i].second);
    }
    cout << seg.max(0, MAX_N) << endl;
    return 0;
}
