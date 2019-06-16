const MOD: i64 = 1000000000 + 7;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let l = sc.chars();
    let mut dp: Vec<Vec<i64>> = vec![vec![0; 2]; l.len() + 1];

    dp[0][0] = 1;

    for i in 0..l.len() {
        let d = l[i];
        for j in 0..2 {
            if d == '1' {
                //0 0
                dp[i + 1][1] += dp[i][j];
                dp[i + 1][1] %= MOD;

                //0 1
                //1 0
                dp[i + 1][j] += 2 * dp[i][j];
                dp[i + 1][j] %= MOD;
            } else {
                //0 0
                dp[i + 1][j] += dp[i][j];
                dp[i + 1][j] %= MOD;

                //0 1
                //1 0
                if j == 1 {
                    dp[i + 1][j] += 2 * dp[i][j];
                    dp[i + 1][j] %= MOD;
                }
            }

        }
    }
    let result = (dp[l.len()][0] + dp[l.len()][1]) % MOD;
    println!("{}", result);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve())
        .unwrap()
        .join()
        .unwrap();
}

//snippet from kenkoooo
pub struct Scanner<R> {
    stdin: R,
}

impl<R: std::io::Read> Scanner<R> {
    pub fn read<T: std::str::FromStr>(&mut self) -> T {
        use std::io::Read;
        let buf = self
            .stdin
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
        let buf = self
            .stdin
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
