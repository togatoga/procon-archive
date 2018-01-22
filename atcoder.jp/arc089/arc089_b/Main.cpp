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
int N, K;
const int MAX_K = 4010;
int black[MAX_K][MAX_K];
int sumB[MAX_K][MAX_K];
int areaB(int y1, int x1, int y2, int x2)
{
    int res = sumB[y2][x2] - sumB[y1 - 1][x2] - sumB[y2][x1 - 1] + sumB[y1 - 1][x1 - 1];
    assert(res >= 0);
    return res;
}
int main()
{
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        int x, y;
        char c;
        cin >> x >> y >> c;
        if (c == 'W')
        {
            y += K;
        }

        y %= (2 * K);
        x %= (2 * K);
        y++;
        x++;
        black[y][x]++;
        black[y + 2 * K][x]++;
        black[y][x + 2 * K]++;
        black[y + 2 * K][x + 2 * K]++;
        
    }

    for (int i = 1; i <= 4 * K; i++)
    {
        for (int j = 1; j <= 4 * K; j++)
        {
            sumB[i][j] += black[i][j];

            sumB[i][j] += sumB[i - 1][j];
            sumB[i][j] += sumB[i][j - 1];
            sumB[i][j] -= sumB[i - 1][j - 1];
            // assert(sumB[i][j] >= 0);
            // assert(sumB[i][j] <= N);
        }
    }

    int result = -INF;
    // cerr << N << endl;
    for (int i = 1; i <= 2 * K; i++)
    {
        for (int j = 1; j <= 2 * K; j++)
        {
            int res = 0;
            int y1, x1;
            y1 = i;
            x1 = j;
            res += areaB(y1, x1, y1 + K - 1, x1 + K - 1);
            int y2, x2;
            y2 = y1 + K;
            x2 = x1 + K;
            res += areaB(y2, x2, y2 + K - 1, x2 + K - 1);
            assert(res >= 0);
            result = max(result, res);
            // result = max(result, N - res);
        }
    }
    cout << result << endl;
    return 0;
}
