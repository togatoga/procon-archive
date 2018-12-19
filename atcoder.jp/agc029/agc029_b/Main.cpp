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
vector<int> A;
map<int, int> cnts;
int main()
{
    cin >> N;
    A.resize(N);
    for (auto &val : A)
    {
        cin >> val;
        cnts[val]++;
        // cout << cnts[val] << endl;
    }
    sort(A.rbegin(), A.rend());

    vector<ll> results;
    results.push_back(1);
    for (int i = 1; i < 40; i++)
    {
        results.push_back(2LL * results[i - 1]);
    }
    sort(results.rbegin(), results.rend());

    ll res = 0;
    for (int i = 0; i < N; i++)
    {
        if (cnts[A[i]] <= 0)
        {
            continue;
        }
        // cout << A[i] << " " << cnts[A[i]] << endl;
        for (int j = 0; j < results.size(); j++)
        {
            int value = results[j] - A[i];
            
            if (value <= 0)
            {
                continue;
            }
            if (value == A[i])
            {
                if (cnts[value] <= 1)
                {
                    continue;
                }
            }
            if (cnts[value] >= 1)
            {
                
                res++;
                cnts[value]--;
                cnts[A[i]]--;
                break;
            }
        }
    }
    cout << res << endl;
    return 0;
}
