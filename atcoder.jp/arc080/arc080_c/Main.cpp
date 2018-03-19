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
//verifiy@http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
//SegmentTreeMin
template <typename ValueType>
class SegmentTreeMin
{
  public:
    SegmentTreeMin() {}
    SegmentTreeMin(int n, ValueType max_value)
    {
        this->N = 1;
        this->max_value = max_value;
        while (this->N < n)
            this->N *= 2;
        this->data.resize(2 * N - 1, this->max_value);
    }
    //init
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
            data[k] = std::min(data[2 * k + 1], data[2 * k + 2]);
        }
    }
    //min [a, b)
    ValueType min(int a, int b)
    {
        return min(a, b, 0, 0, N);
    }
    ValueType min(int a, int b, int k, int l, int r)
    {
        if (r <= a or b <= l)
            return max_value;
        if (a <= l and r <= b)
            return data[k];
        int med = (l + r) / 2;
        return std::min(min(a, b, 2 * k + 1, l, med), min(a, b, 2 * k + 2, med, r));
    }

  private:
    std::vector<ValueType> data;
    int N;
    ValueType max_value;
};
///////////////////////////////////////
const int MAX_N = 200010;
int N;
SegmentTreeMin<pii> even, odd;
vector<int> P;
vector<int> E[MAX_N];
vector<int> PA;
void dfs(int L, int R, int pa = 0)
{
    // cerr << L << " " << R << " " << pa << endl;
    pii mi1, mi2;
    if (L == R)
    {
        E[pa].push_back(P[L]);
        PA[P[L]] = P[R];
        return;
    }
    if (L % 2 == 0)
    {
        mi1 = even.min(L, R - 1);
        mi2 = odd.min(mi1.second + 1, R);
    }
    else
    {
        mi1 = odd.min(L, R - 1);
        mi2 = even.min(mi1.second + 1, R);
    }
    int A = mi1.second;
    int B = mi2.second;
    E[pa].push_back(mi1.first);
    PA[mi1.first] = mi2.first;
    if (L < A)
    {
        dfs(L, A, mi1.first);
    }
    if (A + 1 < B)
    {
        dfs(A + 1, B, mi1.first);
    }
    if (B + 1 < R)
    {
        dfs(B + 1, R, mi1.first);
    }
}

int main()
{
    cin >> N;
    P.resize(N);
    PA.resize(N + 1);
    for (int i = 0; i < N; i++)
    {
        cin >> P[i];
    }
    odd.init(N + 1, mp(INF, INF));
    even.init(N + 1, mp(INF, INF));
    for (int i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            even.update(i, mp(P[i], i));
        }
        else
        {
            odd.update(i, mp(P[i], i));
        }
    }
    
    dfs(0, N);
    
    priority_queue<int, vector<int>, greater<int>> que;
    que.push(E[0].front());
    vector<int> ans;
    
    while (not que.empty())
    {
        int q = que.top();
        que.pop();
        ans.push_back(q);
        ans.push_back(PA[q]);
        // cerr << q << " " << PA[q] << endl;
        for (auto &val : E[q])
        {
            que.push(val);
        }
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
