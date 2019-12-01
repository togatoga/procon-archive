fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let t1: i64 = sc.read();
    let t2: i64 = sc.read();
    let mut a: Vec<i64> = sc.vec(2);
    let mut b: Vec<i64> = sc.vec(2);
    if a[0] < b[0] {
        std::mem::swap(&mut a, &mut b);
    }
    let a_sum = a[0] * t1 + a[1] * t2;
    let b_sum = b[0] * t1 + b[1] * t2;
    if a_sum == b_sum {
        println!("infinity");
        return;
    }
    // println!("{:?} {:?}", a, b);
    let c: Vec<i64> = vec![a[0] - b[0], a[1] - b[1]];
    let top = c[0] * t1;
    let down = top + c[1] * t2;
    if top > 0 && down < 0 {
        let d = down.abs();
        let cnt = top / d;
        let plus = if top % d == 0 { 1 } else { 0 };
        println!("{}", 2 * (cnt - plus) + plus + 1);
    } else {
        println!("0");
    }
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
