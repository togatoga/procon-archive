const MAX_NTAB: usize = 3010;

fn memo(
    pos: usize,
    total: usize,
    dp: &mut Vec<Vec<Option<usize>>>,
    ab: &Vec<(usize, usize)>,
    n: usize,
    t: usize,
) -> usize {
    if pos >= n || total >= t {
        return 0;
    }
    if let Some(value) = dp[pos][total] {
        return value;
    }
    let mut result = 0;
    //eat
    let (time, taste) = ab[pos];
    result = std::cmp::max(result, memo(pos + 1, total + time, dp, ab, n, t) + taste);

    //not eat
    result = std::cmp::max(result, memo(pos + 1, total, dp, ab, n, t));
    dp[pos][total] = Some(result);
    result
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let t: usize = sc.read();
    let mut ab: Vec<(usize, usize)> = (0..n)
        .map(|_| {
            let a: usize = sc.read();
            let b: usize = sc.read();
            (a, b)
        })
        .collect();
    ab.sort();
    let mut dp: Vec<Vec<Option<usize>>> = vec![vec![None; MAX_NTAB]; MAX_NTAB];
    let result = memo(0, 0, &mut dp, &ab, n, t);
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
