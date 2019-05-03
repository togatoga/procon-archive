fn gcd(a: u64, b: u64) -> u64 {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let a: Vec<u64> = sc.vec(n);
    let mut pre_gcd: Vec<u64> = vec![0; n];
    let mut post_gcd: Vec<u64> = vec![0; n];
    pre_gcd[0] = a[0];
    for i in 1..n {
        pre_gcd[i] = gcd(pre_gcd[i - 1], a[i]);
    }
    post_gcd[n - 1] = a[n - 1];
    for i in (0..n - 1).rev() {
        post_gcd[i] = gcd(post_gcd[i + 1], a[i]);
    }
    let mut result = 1;
    assert_eq!(pre_gcd[n - 1], post_gcd[0]);
    result = std::cmp::max(result, pre_gcd[n - 2]);
    result = std::cmp::max(result, pre_gcd[n - 1]);
    result = std::cmp::max(result, post_gcd[0]);
    result = std::cmp::max(result, post_gcd[1]);
    for i in 1..n-1 {
        result = std::cmp::max(result, gcd(pre_gcd[i - 1], post_gcd[i + 1]));
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
