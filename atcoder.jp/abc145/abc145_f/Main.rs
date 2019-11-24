const MAX_N: usize = 310;
const INF: u64 = 1_u64 << 60;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let mut tmp_h: Vec<usize> = sc.vec(n);
    let mut h = vec![0];
    h.append(&mut tmp_h);
    h.push(0);
    let mut dp = vec![vec![INF; MAX_N]; MAX_N];
    dp[0][0] = 0;
    for i in 0..n + 2 {
        for j in 0..k + 1 {
            if dp[i][j] == INF {
                continue;
            }
            for x in i + 1..n + 2 {
                let cost = x - i - 1;
                let diff = if h[x] > h[i] { h[x] - h[i] } else { 0 };
                if cost + j <= k {
                    dp[x][cost + j] = std::cmp::min(dp[x][cost + j], dp[i][j] + diff as u64);
                }
            }
        }
    }
    let result = dp[n + 1].iter().min().unwrap();
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
