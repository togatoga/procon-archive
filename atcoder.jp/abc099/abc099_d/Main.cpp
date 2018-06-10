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
map<int, int> Color[3];
map<pii, int> D;
int N, C;
int calc(vector<int> c)
{
    int res = 0;
    for (int i = 0; i < 3; i++)
    {
        for (const auto &val : Color[i])
        {
            res += D[mp(val.first, c[i])] * val.second;
            // cerr << val.first << " " << val.second << " " << c[i] << endl;
        }
        // cerr << "res = " << res << endl;
    }
    // cerr << endl;
    return res;
}
int main()
{
    cin >> N >> C;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            int x;
            cin >> x;
            D[mp(i, j)] = x;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int idx = (i + j) % 3;
            int x;
            cin >> x;
            x--;
            Color[idx][x]++;
        }
    }
    int result = INF;
    for (int i = 0; i < C; i++)
    {
        for (int j = 0; j < C; j++)
        {
            for (int k = 0; k < C; k++)
            {
                vector<int> c = {i, j, k};
                if (i == j || j == k || i == k)
                {
                    continue;
                }
                result = min(result, calc(c));
            }
        }
    }
    cout << result << endl;
    return 0;
}
