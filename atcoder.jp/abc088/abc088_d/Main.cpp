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
const int MAX_N = 51;
int H, W;
char board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
void bfs()
{
    queue<tuple<pii, int>> que; //pos,pre,cost
    que.emplace(mt(mp(1, 1), 0));
    int result = -1;
    while (not que.empty())
    {
        auto p = que.front();
        que.pop();
        pii pos;
        int cost;
        tie(pos, cost) = p;
        int y = pos.first;
        int x = pos.second;
        //goal
        if (y == H and x == W)
        {
            result = cost;
            break;
        }
        //pre visited
        if (visited[y][x])
        {
            continue;
        }
        visited[y][x] = true;
        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (board[ny][nx] == '.')
            {
                que.emplace(mt(mp(ny, nx), cost + 1));
            }
        }
    }
    if (result == -1)
    {
        cout << result << endl;
        return;
    }
    
    int white = 0;
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (i == 1 and j == 1){
                continue;
            }
            if (i == H and j == W){
                continue;
            }
            if (board[i][j] == '.')
            {
                white++;
            }
        }
    }
    // cout << result << " " << white << endl;
    cout << white - result  + 1 << endl;
}

int main()
{
    cin >> H >> W;
    for (int i = 1; i <= H; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            cin >> board[i][j];
        }
    }
    bfs();
    return 0;
}
