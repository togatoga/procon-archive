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
int N;
vector<int> A;
int min_val, max_val;
int main()
{
    cin >> N;
    A.resize(N);
    min_val = INF;
    max_val = -INF;
    for (auto &val : A)
    {
        cin >> val;
        min_val = min(min_val, val);
        max_val = max(max_val, val);
    }
    vector<pii> result;
    if (abs(min_val) <= abs(max_val))
    {
        int max_idx = -1;
        for (int i = 0; i < N; i++)
        {
            if (max_val == A[i])
            {
                max_idx = i;
                break;
            }
        }

        for (int i = 0; i < N; i++)
        {
            result.emplace_back(mp(max_idx, i));
            result.emplace_back(mp(max_idx, i));
            max_idx = i;
        }
    }
    else
    {
        int min_idx = -1;
        for (int i = 0; i < N; i++)
        {
            if (min_val == A[i])
            {
                min_idx = i;
                break;
            }
        }
        for (int i = N - 1; i >= 0; i--)
        {
            result.emplace_back(mp(min_idx, i));
            result.emplace_back(mp(min_idx, i));
            min_idx = i;
        }
    }
    cout << result.size() << endl;
    for (auto &val : result)
    {
        cout << val.first + 1 << " " << val.second + 1 << endl;
    }

    return 0;
}
