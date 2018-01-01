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
const int MAX_N = 1010;
int N, K, Q;
int board[MAX_N][MAX_N];
int sm[2 * MAX_N][2 * MAX_N];
void pre()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            sm[i][j] = board[i][j] + sm[i - 1][j] + sm[i][j - 1] - sm[i - 1][j - 1];
        }
    }
}
bool chk(int y, int x)
{
    int py = y + K - 1;
    int px = x + K - 1;
    int sum = sm[py][px] - sm[py][x - 1] - sm[y - 1][px] + sm[y - 1][x - 1];
    return sum == 0;
}
int color[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
void do_color()
{
    int c = 1;
    memset(color, -1, sizeof(color));
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (visited[i][j] or color[i][j] != -1 or not chk(i, j))
            {
                continue;
            }
            queue<pii> que;
            que.emplace(mp(i, j));
            while (not que.empty())
            {
                pii p = que.front();
                que.pop();
                int y, x;
                y = p.first;
                x = p.second;
                if (visited[y][x] or color[y][x] != -1)
                {
                    continue;
                }
                color[y][x] = c;
                visited[y][x] = true;
                for (int k = 0; k < 4; k++)
                {
                    int ny, nx;
                    ny = y + dy[k];
                    nx = x + dx[k];
                    if (ny < 1 or ny > N or nx < 1 or nx > N)
                    {
                        continue;
                    }
                    if (chk(ny, nx))
                    {
                        que.emplace(mp(ny, nx));
                    }
                }
            }
            c++;
        }
    }
}
int main()
{
    cin >> N >> K >> Q;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            char c;
            cin >> c;
            board[i][j] = c == '#' ? 1 : 0;
        }
    }
    pre();
    do_color();
    for (int i = 0; i < Q; i++)
    {
        int sy, sx;
        int ty, tx;
        cin >> sy >> sx >> ty >> tx;
        bool ok = true;
        if (color[sy][sx] == -1 or color[ty][tx] == -1 or color[sy][sx] != color[ty][tx])
        {
            ok = false;
        }
        if (ok)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
    return 0;
}
