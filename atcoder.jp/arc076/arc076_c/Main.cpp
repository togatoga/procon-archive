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
int R, C, N;
bool is_edge(int x, int y)
{
    if (x == 0 or x == R or y == 0 or y == C)
    {
        return true;
    }
    return false;
}
int convert(int x, int y)
{
    if (x == 0)
    {
        return y;
    }
    if (y == C)
    {
        return C + x;
    }
    if (x == R)
    {
        return C + R + (C - y);
    }
    if (y == 0)
    {
        return C + R + C + (R - x);
    }
    assert(0);
}
int main()
{
    cin >> R >> C >> N;
    vector<pii> positions;
    for (int i = 0; i < N; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (is_edge(x1, y1) and is_edge(x2, y2))
        {
            positions.emplace_back(mp(convert(x1, y1), i));
            positions.emplace_back(mp(convert(x2, y2), i));
        }
    }
    sort(positions.begin(), positions.end());
    stack<int> st;
    for (int i = 0; i < positions.size(); i++)
    {
        if (st.empty() or st.top() != positions[i].second)
        {
            st.push(positions[i].second);
        }
        else
        {
            st.pop();
        }
    }
    if (st.empty())
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
    return 0;
}
