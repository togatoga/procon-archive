const MAX_H: usize = 10010;
const MAX_N: usize = 1010;

fn memo(
    x: usize,
    v: usize,
    h: usize,
    n: usize,
    ab: &Vec<(usize, usize)>,
    dp: &mut Vec<Vec<Option<usize>>>,
) -> usize {
    if v >= h {
        return 0;
    }
    if let Some(value) = dp[x][v] {
        return value;
    }
    let (attack, magic) = ab[x];
    let mut result = memo(x, v + attack, h, n, ab, dp) + magic;
    if x + 1 < n {
        result = std::cmp::min(result, memo(x + 1, v, h, n, ab, dp));
    }
    dp[x][v] = Some(result);
    result
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let n: usize = sc.read();
    let ab: Vec<(usize, usize)> = (0..n)
        .map(|_| {
            let a: usize = sc.read();
            let b: usize = sc.read();
            (a, b)
        })
        .collect();
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; MAX_H]; MAX_N];
    let result = memo(0, 0, h, n, &ab, &mut dp);
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
