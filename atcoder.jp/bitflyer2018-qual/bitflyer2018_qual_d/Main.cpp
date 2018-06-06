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
int H, W;
int N, M;
const int MAX_NM = 2010;
char board[MAX_NM][MAX_NM];
vector<int> X, Y;
int res[MAX_NM][MAX_NM];
int main()
{
    cin >> H >> W;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> board[i][j];
            X.push_back(j);
            X.push_back(W - M + j + 1);
            Y.push_back(i);
            Y.push_back(H - N + i + 1);
        }
    }
    sort(X.begin(), X.end());
    sort(Y.begin(), Y.end());
    X.erase(unique(X.begin(), X.end()), X.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (board[i][j] == '#')
            {
                int py = H - N + i + 1;
                int px = W - M + j + 1;

                int x1 = lower_bound(X.begin(), X.end(), j) - X.begin();
                int x2 = lower_bound(X.begin(), X.end(), px) - X.begin();

                int y1 = lower_bound(Y.begin(), Y.end(), i) - Y.begin();
                int y2 = lower_bound(Y.begin(), Y.end(), py) - Y.begin();

                res[y1][x1]++;
                res[y2][x1]--;
                res[y1][x2]--;
                res[y2][x2]++;
            }
        }
    }

    for (int i = 0; i < MAX_NM; i++)
    {
        for (int j = 1; j < MAX_NM; j++)
        {
            res[i][j] += res[i][j - 1];
        }
    }
    for (int j = 0; j < MAX_NM; j++)
    {
        for (int i = 1; i < MAX_NM; i++)
        {

            res[i][j] += res[i - 1][j];
        }
    }
    ll result = 0;
    int N1 = Y.size();
    int M1 = X.size();
    for (int i = 0; i < N1 - 1; i++)
    {
        for (int j = 0; j < M1 - 1; j++)
        {
            if (res[i][j] == 0)
            {
                continue;
            }
            int ty = i + 1;
            int tx = j + 1;

            int x1 = X[j];
            int x2 = X[tx];
            int y1 = Y[i];
            int y2 = Y[ty];

            ll dy = y2 - y1;
            ll dx = x2 - x1;

            result += dy * dx;
        }
    }
    cout << result << endl;
    return 0;
}
