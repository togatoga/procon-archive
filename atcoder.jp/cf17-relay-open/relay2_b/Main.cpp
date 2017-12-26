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
int N, Q;

int parent(int p)
{
    if (p % N == 0)
    {
        return p / N - 1;
    }
    return p / N;
}
void path(int p, int q)
{
    // cerr << "root = "  << p << endl;
    if (N == 1){
        printf("%d\n", min(p, q) + 1);
        return ;
    }
    while (p != q)
    {
        if (p < q)
        {
            swap(p, q);
        }
        p = parent(p);
        // p = max(p, 0);
    }
    printf("%d\n", p+1);
}
int main()
{

    scanf("%d %d", &N, &Q);
    for (int i = 0; i < Q; i++)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        a--, b--;
        
        path(a, b);
        // cerr << a << " " << b << endl;
    }
    return 0;
}
