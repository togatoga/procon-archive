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
const int MAX_NM = 310;
int N, M;
int A[MAX_NM][MAX_NM];
int indices[MAX_NM];
int deg[MAX_NM];
int main()
{
    
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> A[i][j];
            A[i][j]--;
        }
        deg[A[i][0]]++;
    }

    set<int> tabooo;
    int result = N;
    while (tabooo.size() < M)
    {
        int max_deg = -1;
        int max_sports = -1;
        //add max sport to tabooo
        for (int i = 0; i < M; i++)
        {
            if (deg[i] > max_deg)
            {
                max_deg = deg[i];
                max_sports = i;
            }
        }
        if (max_sports == -1)
        {
            break;
        }
        // cerr << max_deg << " " << max_sports << " " << deg[max_sports] << endl;
        // assert(tabooo.count(max_sports) == 0);

        result = min(result, max_deg);
        tabooo.insert(max_sports);
        //update
        for (int i = 0; i < N; i++)
        {
            int idx = indices[i];
            int val = A[i][idx];
            while (tabooo.count(val) > 0)
            {
                deg[val]--;
                indices[i]++;
                int idx = indices[i];
                val = A[i][idx];
                deg[val]++;
            }
        }
    }
    cout << result << endl;
    return 0;
}
