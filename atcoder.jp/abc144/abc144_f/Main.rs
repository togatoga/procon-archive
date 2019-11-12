const MAX_N: usize = 600;
const MAX_M: usize = MAX_N * MAX_N / 2;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let mut edges = vec![vec![]; MAX_M];
    for _ in 0..m {
        let s: usize = sc.read::<usize>() - 1;
        let t: usize = sc.read::<usize>() - 1;
        edges[s].push(t);
    }
    let mut result = 1e10;
    for i in (0..n - 1).rev() {
        let mut dp = vec![1e10; n];
        dp[n - 1] = 0.0;
        for j in (0..n - 1).rev() {
            let mut sum = 0.0;
            let mut max_value = 0.0;
            for &x in edges[j].iter() {
                sum += (1.0 + dp[x]);
                assert!(j < x);
                // println!("x: {}", x);
                if max_value < 1.0 + dp[x] {
                    max_value = 1.0 + dp[x];
                }
            }
            let b = edges[j].len() as f32;
            //println!("{}", b);
            dp[j] = sum / b;
            if i == j && edges[j].len() > 1 {
                let tmp = (sum - max_value) / (b - 1.0);
                if dp[j] > tmp {
                    dp[j] = tmp;
                }
            }
            //println!("i: {}, j: {}, dp[{}]: {}, sum: {}", i, j, j, dp[j], sum);
        }
        if result > dp[0] {
            result = dp[0];
        }
    }
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
