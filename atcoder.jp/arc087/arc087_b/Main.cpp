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
string S;
int N;
int X, Y;
const int MAX_N = 8010;
bool dp1[MAX_N][MAX_N + MAX_N];
bool dp2[MAX_N][MAX_N + MAX_N];
vector<int> tmpX, tmpY;
int main()
{
    cin >> S;
    N = S.size();
    cin >> X >> Y;
    int cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] == 'F')
        {
            cnt++;
        }
        else
        {
            break;
        }
    }
    int x, y;
    x = cnt;
    y = 0;
    bool flag = true;
    int tmp = 0;

    for (int i = cnt; i < N; i++)
    {
        if (S[i] == 'F')
        {
            tmp++;
        }
        else
        {
            if (tmp > 0)
            {
                if (flag)
                {
                    tmpX.push_back(tmp);
                }
                else
                {
                    tmpY.push_back(tmp);
                }
            }
            tmp = 0;
            flag = !flag;
        }
    }
    if (tmp > 0)
    {
        if (flag)
        {
            tmpX.push_back(tmp);
        }
        else
        {
            tmpY.push_back(tmp);
        }
    }
    dp1[0][x+MAX_N] = true;
    for (int i = 0; i < tmpX.size(); i++){
        for (int j = 0; j < 2 * MAX_N; j++){
            if (!dp1[i][j]){
                continue;
            }
            if (j + tmpX[i] < 2 * MAX_N){
                dp1[i + 1][j + tmpX[i]] = true;
            }
            if (j - tmpX[i] >= 0){
                dp1[i + 1][j - tmpX[i]] = true;
            }
        }
    }
    dp2[0][MAX_N] = true;
    for (int i = 0; i < tmpY.size(); i++){
        for (int j = 0; j < 2 * MAX_N; j++){
            if (!dp2[i][j]){
                continue;
            }
            if (j + tmpY[i] < 2 * MAX_N){
                dp2[i + 1][j + tmpY[i]] = true;
            }
            if (j - tmpY[i] >= 0){
                dp2[i + 1][j - tmpY[i]] = true;
            }
        }
    }    
    if (dp1[tmpX.size()][X + MAX_N] and dp2[tmpY.size()][Y + MAX_N]){
        cout << "Yes" << endl;
    }else{
        cout << "No" << endl;
    }


    return 0;
}
