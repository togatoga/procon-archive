fn factor(mut x: usize) -> Vec<usize> {
    let mut div = 2;
    let mut results = vec![];
    while x > 0 {
        while x % div == 0 {
            results.push(div);
            x /= div;
        }
        div += 1;
        if div * div > x {
            break;
        }
    }
    if x != 1 {
        results.push(x);
    }
    results
}

fn ok(x: usize, k: usize, a: &[usize]) -> bool {
    let mut b = vec![];
    for &v in a.iter() {
        b.push(v % x);
    }
    b.sort();
    let n = b.len();
    let mut left = vec![0; n + 1];
    for i in 0..n {
        left[i + 1] = left[i] + b[i];
    }
    let mut right = vec![0; n + 1];
    for i in (0..n).rev() {
        right[i] = x - b[i] + right[i + 1];
    }

    // println!("{} {:?} {:?} {:?}", x, left, right, b);
    for i in 0..n + 1 {
        if std::cmp::max(left[i], right[i]) <= k {
            return true;
        }
    }

    false
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let mut a: Vec<usize> = sc.vec(n);
    a.sort();
    let result = a.iter().fold(0, |sum, a| sum + a);
    let factors = factor(result);

    // println!("{:?}", factors);
    let mut result = 1;
    for bit in 0..(1usize << factors.len()) {
        let mut value = 1;
        for i in 0..factors.len() {
            if (bit >> i) & 1 != 0 {
                value *= factors[i];
            }
        }
        if ok(value, k, &a) {
            result = std::cmp::max(result, value);
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
