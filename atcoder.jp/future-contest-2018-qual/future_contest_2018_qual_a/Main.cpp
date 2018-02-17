#define NDEBUG
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
//////////////////////////////////////////////////////////////////////////////////
#include <sys/time.h>
// get millsec
class Timer {
public:
  Timer() {}
  void start() { start_time = get_mill_sec(); }
  // millsec
  double get_duration() { return get_mill_sec() - start_time; }
  void set_time_limit(double limit) { time_limit = limit; }
  bool is_time_limit_exceeded() { return get_duration() > time_limit; }

private:
  double start_time;
  double time_limit;
  double get_mill_sec() {
    struct timeval res;
    gettimeofday(&res, NULL);
    return res.tv_sec * 1000 + res.tv_usec / 1000;
  }
};

class XorShift {
  static const int MAX = numeric_limits<int>::max();
  int x = 123456789, y = 362436069, z = 521288629, w = 88675123;

public:
  XorShift() {}
  XorShift(int seed) {
    x ^= seed;
    y ^= x << 10 & seed;
    w ^= y >> 20 | seed;
    z ^= w & x;
  }
  int next() {
    int t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
  }
  int next(int min_value, int max_value) {
    int range = max_value - min_value;
    return (sample() * range) + min_value;
  }
  double sample() { return next() * 1.0 / MAX; }
};

class Annealing {
public:
  const double TEMP_CTRL_PARAM = 4.8;
  double initial_temp, current_temp;
  double simulate_time;
  double start_time, end_time;
  double best_score;
  double param1, param2;
  XorShift rnd;
  Annealing(double initial_temp, double end_time, double start_time,
            XorShift rnd) {
    this->initial_temp = initial_temp;
    this->current_temp = initial_temp;
    this->rnd = rnd;

    this->best_score = 0;

    this->start_time = start_time;
    this->end_time = end_time;
    this->simulate_time = end_time - start_time;

    this->param1 = 1.0 / (simulate_time / TEMP_CTRL_PARAM);
    this->param2 = 1.0 / exp(TEMP_CTRL_PARAM);
  }
  bool cool_down(double elapsed) {
    if (elapsed >= end_time)
      return false;
    // linear function
    // current_temp = initial_temp + (final_temp - initial_temp) * ((time
    // -start_time) / simulate_time);
    // exp function
    current_temp = initial_temp * exp((end_time - elapsed) * param1) * param2;
    return true;
  }
  bool transition(int current_s, int neighbor_s) {
    // maximization problem
    if (current_s < neighbor_s)
      return true;
    double provability = exp((neighbor_s - current_s) / current_temp);

    // minimization problem
    // if (current_s > neighbor_s) return true;
    // double provability = exp((current_s - neighbor_s) / current_temp);

    if (provability >= rnd.sample())
      return true;
    return false;
  }
};

///////////////////////////////////////////////////////////////////////////////////
const int MAX_N = 100;
const int BASE_SCORE = 200000000;
const int MAX_Q = 1000;
Timer timer;

struct Board {
  Board() {
    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        this->set_value(i, j, 0);
      }
    }
  }
  set<pair<int, pii>> scores;
  array<int, MAX_N * MAX_N> board;
  pii get_pos_max_val() {
    auto p = *scores.rbegin();
    return p.second;
  }
  inline int get_value(const int y, const int x) {
    assert(y <= MAX_N and x <= MAX_N);
    return board[y * MAX_N + x];
  }

  inline const int get_value(const int y, const int x) const {
    assert(y <= MAX_N and x <= MAX_N);
    return board[y * MAX_N + x];
  }

  inline void set_value(const int y, const int x, int val) {
    assert(y <= MAX_N and x <= MAX_N);

    board[y * MAX_N + x] = val;
  }
  inline void add(const int y, const int x, int val) {
    assert(y <= MAX_N and x <= MAX_N);
    board[y * MAX_N + x] += val;
  }
  void clear() {
    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        this->set_value(i, j, 0);
      }
    }
  }
  void simulate(const int y, const int x, const int h) {

    for (int py = max(0, y - h); py < min(MAX_N, y + h); py++) {
      int rest = h - abs(py - y);
      int rx = x + rest;
      int lx = x - rest;

      for (int px = max(0, lx); px <= min(MAX_N - 1, rx); px++) {
        int d = abs(py - y) + abs(px - x);
        int c = h - d;
        this->add(py, px, -c);
      }
    }
    return;
  }

  void debug() {
    // debug
    cerr << "----------debug---------" << endl;
    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        cerr << this->get_value(i, j) << " ";
      }
      cerr << endl;
    }
  }
  int calc_score() {

    int score = BASE_SCORE;
    for (int i = 0; i < MAX_N; i++) {
      for (int j = 0; j < MAX_N; j++) {
        score -= abs(this->get_value(i, j));
      }
    }
    // cerr << "score = " << score << endl;
    return score;
  }
};

Board root_board;

struct Action {
  Action() {
    this->y = 0;
    this->x = 0;
    this->h = 0;
  }
  Action(int y, int x, int h) : y(y), x(x), h(h) {
    assert(y < MAX_N and x < MAX_N);
    assert(1 <= h and h <= MAX_N);
  }
  int y, x, h;
  void print() {
    assert(y < MAX_N and x < MAX_N);
    assert(1 <= h and h <= MAX_N);
    cout << x << " " << y << " " << h << endl;
  }
};

///////////////////////////////////////////////////////////////////////////////////

struct SearchState {
  SearchState(const Board &board) {
    this->board = board;
    this->score = this->board.calc_score();
    this->Q = 0;
    this->actions.resize(MAX_Q);
  }
  Board board;
  int score;
  int Q;
  vector<Action> actions;
  int action_size() {
    assert(Q >= 0 and Q <= MAX_Q);
    return Q;
  }
  void set_action(const int y, const int x, const int h) {
    assert(Q >= 0 and Q < MAX_Q);
    actions[Q] = Action(y, x, h);
    Q++;
  }
};

Board input() {
  Board board;
  for (int i = 0; i < MAX_N; i++) {
    for (int j = 0; j < MAX_N; j++) {
      int x;
      cin >> x;
      board.set_value(i, j, x);
    }
  }
  return board;
}

void init() { root_board = input(); }

void answer(SearchState &state) {
  int Q = state.action_size();
  cout << Q << endl;
  for (int i = 0; i < Q; i++) {
    state.actions[i].print();
  }
}

int safe_value(Board &board, const int y, const int x) {
  for (int h = MAX_N; h >= 2; h--) {
    bool ok = true;
    for (int py = max(0, y - h); py < min(MAX_N, y + h); py++) {
      int rest = h - abs(py - y);
      int rx = x + rest;
      int lx = x - rest;

      for (int px = max(0, lx); px <= min(MAX_N - 1, rx); px++) {
        int d = abs(py - y) + abs(px - x);
        int c = h - d;
        if (board.get_value(py, px) < c) {
          ok = false;
          break;
        }
      }
      if (not ok) {
        break;
      }
    }
    if (ok) {
      return h;
    }
  }
  return 1;
}

void run() {
  int all_max_score = 0;
  SearchState max_state(root_board);
  int seed = 810;
  int loop = 0;
  while (timer.get_duration() < 5600) {
    ++loop;
    XorShift rnd(seed);
    SearchState state(root_board);
    int cnt = 0;
    XorShift ann_rnd(seed);
    Annealing ann = Annealing(100 + rnd.next(1, 100), 5600, timer.get_duration(), ann_rnd);
    double curr_time = timer.get_duration();
    double left_val = 100;
    // double right_val = 100;
    while (curr_time < 5600) {
      // update
      if (cnt % 100 == 0) {
        curr_time = timer.get_duration();
      }
      if (state.action_size() >= MAX_Q) {
        break;
      }
      cnt++;
      const int prev_score = state.score;

      int max_val = 0;
      pii nxt = mp(-1, -1);
      vector<pair<int, pii>> values;

      for (int i = 0; i < MAX_N; i++) {
          for (int j = 0; j < MAX_N; j++) {
            int tmp_val = state.board.get_value(i, j);
            if (tmp_val <= 0){
              continue;
            }
            values.emplace_back(mp(tmp_val, mp(i, j)));
            if (tmp_val > max_val) {
              max_val = tmp_val;
              nxt = mp(i, j);
            }
        }
      }
      if (nxt.first == -1 or nxt.second == -1) {
        break;
      }
      int ny, nx, nh;
      sort(values.rbegin(), values.rend());
      int max_safe_val = 0;
      int max_curr_score = 0;
      for (int i = 0; i < min((int)values.size(), 10); i++){
        int y = values[i].second.first;
        int x = values[i].second.second;
        int tmp_safe_val = safe_value(state.board, y, x);

        Board next_board = state.board;
        next_board.simulate(ny, nx, nh);

        int next_score = next_board.calc_score();
        if (max_curr_score < next_score){
          max_curr_score = next_score;
          ny = y;
          nx = x;
          nh = tmp_safe_val;
        }
      }

      nh += rnd.next(1, rnd.next(17, 20));
      nh = max(1, nh);
      nh = min(100, nh);


      Board next_board = state.board;
      next_board.simulate(ny, nx, nh);
      int next_score = next_board.calc_score();

      if (ann.transition(prev_score, next_score)) {
        state.score = next_score;
        state.board = move(next_board);
        state.set_action(ny, nx, nh);
        if (all_max_score < next_score) {
          all_max_score = next_score;
          max_state = state;
        }
      } else {
        left_val -= left_val * 0.001;
        // cerr << "left_val = " << left_val << endl;
      }
      ann.cool_down(curr_time);
    }
    seed += rnd.next(1, 810);
    seed %= MOD;

  }
  answer(max_state);

  // state.board.debug();
  // max_state.board.debug();
  // eval_board.debug();
  cerr << "loop = " << loop << endl;
  cerr << "score = " << max_state.score << endl;
}

int main() {
  timer.start();
  init();
  run();

  // Board board;
  // const int d = 100;
  // board.simulate(0, 0, d);
  // for (int i = 0; i < d; i++)
  // {
  //     for (int j = 0; j < d; j++)
  //     {
  //         cout << board.get_value(i, j) << " ";
  //     }
  //     cout << endl;
  // }
  // board.debug();
  return 0;
}
