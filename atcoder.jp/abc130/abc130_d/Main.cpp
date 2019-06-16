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
ll N, K;
vector<ll> A;
int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
    cin >> N >> K;
    A.resize(N);
    for (auto &val : A)
    {
        cin >> val;
    }
    ll sum = 0;
    int left = 0;
    int right = 0;
    ll result = 0;
    while (left <= right)
    {
        //cerr << left << " " << right << " " << sum << endl;
        if (sum >= K)
        {
            result += (N - right + 1);
            sum -= A[left];
            left++;
        }
        else
        {
            if (right < N)
            {
                sum += A[right];
                right++;
            }
            else
            {
                break;
            }
        }
    }
    if (sum >= K)
    {
        result += N - right + 1;
    }
    cout << result << endl;
    return 0;
}
