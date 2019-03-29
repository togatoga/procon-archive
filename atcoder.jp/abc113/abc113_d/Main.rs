const MOD: usize = 1_000_000_007;

fn memo(cur_h: usize, cur_w: usize, cur_goal: usize, dp: &mut Vec<Vec<Vec<Option<usize>>>>, limit_h: usize, limit_w: usize, target_goal: usize) -> usize {
    if cur_h >= limit_h {
        if cur_goal == target_goal {
            return 1;
        }
        return 0;
    }
    if let Some(memo_value) = dp[cur_h][cur_w][cur_goal] {
        return memo_value;
    }
    let mut result: usize = 0;
    //use
    {
        let mut next_w = cur_w + 2;
        let mut next_h = cur_h;
        let mut next_goal = cur_goal;
        if next_w >= limit_w {
            next_w = 0;
            next_h += 1;
        }
        let left = cur_w;
        let right = cur_w + 1;
        if left == cur_goal {
            next_goal = right;
        } else if right == cur_goal {
            next_goal = left;
        }

        result += memo(next_h, next_w, next_goal, dp, limit_h, limit_w, target_goal);
        result %= MOD;
    }
    //no use
    {
        let mut next_w = cur_w + 1;
        let mut next_h = cur_h;
        if next_w >= limit_w {
            next_w = 0;
            next_h += 1;
        }
        result += memo(next_h, next_w, cur_goal, dp, limit_h, limit_w, target_goal);
        result %= MOD;
    }
    dp[cur_h][cur_w][cur_goal] = Some(result);
    return result;
}

fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read::<usize>() - 1;
    let k: usize = sc.read::<usize>() - 1;
    //dp[h][w][goal]
    let mut dp: Vec<Vec<Vec<Option<usize>>>> = vec![vec![vec![None; 10]; 10]; 110];
    let mut res = 1;
    if w != 0 {
        res = memo(0, 0, 0, &mut dp, h, w, k);
    }
    println!("{}", res);
}

//snippet from kenkoooo
pub struct Scanner<R> {
    stdin: R,
}

impl<R: std::io::Read> Scanner<R> {
    pub fn read<T: std::str::FromStr>(&mut self) -> T {
        use std::io::Read;
        let buf = self.stdin
            .by_ref()
            .bytes()
            .map(|b| b.unwrap())
            .skip_while(|&b| b == b' ' || b == b'\n' || b == b'\r')
            .take_while(|&b| b != b' ' && b != b'\n' && b != b'\r')
            .collect::<Vec<_>>();
        unsafe { std::str::from_utf8_unchecked(&buf) }
            .parse()
            .ok()
            .expect("Parse error.")
    }
    pub fn read_line(&mut self) -> String {
        use std::io::Read;
        let buf = self.stdin
            .by_ref()
            .bytes()
            .map(|b| b.unwrap())
            .skip_while(|&b| b == b'\n' || b == b'\r')
            .take_while(|&b| b != b'\n' && b != b'\r')
            .collect::<Vec<_>>();
        unsafe { std::str::from_utf8_unchecked(&buf) }
            .parse()
            .ok()
            .expect("Parse error.")
    }
    pub fn vec<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.read()).collect()
    }

    pub fn chars(&mut self) -> Vec<char> {
        self.read::<String>().chars().collect()
    }
}
