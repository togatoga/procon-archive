fn g(x: f64, xy: &[(f64, f64)]) -> f64 {
    let mut left: f64 = 0.0;
    let mut right: f64 = 1000.0;
    let f = |qx: f64, qy: f64| -> f64 {
        let mut result = 0.0;

        for &(px, py) in xy.iter() {
            let dx = qx - px;
            let dy = qy - py;
            let d = (dx * dx + dy * dy).sqrt();
            if result < d {
                result = d;
            }
        }
        result
    };
    for i in 0..100 {
        let m1: f64 = (left * 2.0 + right) / 3.0;
        let m2: f64 = (left + 2.0 * right) / 3.0;
        if f(x, m1) > f(x, m2) {
            left = m1;
        } else {
            right = m2;
        }
    }
    f(x, left)
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let xy: Vec<(f64, f64)> = (0..n)
        .map(|_| {
            let x: f64 = sc.read();
            let y: f64 = sc.read();
            (x, y)
        })
        .collect();
    let mut left = 0.0;
    let mut right = 1000.0;
    for i in 0..100 {
        let m1 = (left * 2.0 + right) / 3.0;
        let m2 = (left + 2.0 * right) / 3.0;
        if g(m1, &xy) > g(m2, &xy) {
            left = m1;
        } else {
            right = m2;
        }
    }
    println!("{}", g(left, &xy));
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
