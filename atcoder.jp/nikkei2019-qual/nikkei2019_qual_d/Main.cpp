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
int N, M;
const int MAX_NM = 100010;
vector<int> edges[MAX_NM];
int deg[MAX_NM];
int main()
{
    cin >> N >> M;
    for (int i = 0; i < N + M - 1; i++)
    {
        int A, B;
        cin >> A >> B;
        A--, B--;
        edges[A].push_back(B);
        deg[B]++;
    }
    queue<int> que;
    for (int i = 0; i < N; i++)
    {
        if (deg[i] == 0)
        {
            que.push(i);
            break;
        }
    }
    vector<int> answers(N, -1);
    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        for (auto &q : edges[p])
        {
            deg[q]--;
            if (!deg[q])
            {
                que.push(q);
                answers[q] = p;
            }
        }
    }
    for (auto &val : answers)
    {
        cout << val + 1 << endl;
    }
    return 0;
}
