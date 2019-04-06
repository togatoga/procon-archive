fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let x: usize = sc.read();
    let y: usize = sc.read();
    let z: usize = sc.read();
    let k: usize = sc.read();
    let mut a_values: Vec<u64> = sc.vec(x);
    a_values.sort_by(|x, y| y.cmp(x));
    let mut b_values: Vec<u64> = sc.vec(y);
    b_values.sort_by(|x, y| y.cmp(x));
    let mut c_values: Vec<u64> = sc.vec(z);
    c_values.sort_by(|x, y| y.cmp(x));
    let mut ab_values: Vec<u64> = Vec::new();
    for &a in a_values.iter() {
        for &b in b_values.iter() {
            ab_values.push(a + b);
        }
    }
    ab_values.sort_by(|x, y| y.cmp(x));
    ab_values.resize(k, 0);
    let mut abc_values: Vec<u64> = Vec::new();
    for &ab in ab_values.iter() {
        for &c in c_values.iter() {
            abc_values.push(ab + c);
        }
    }
    abc_values.sort_by(|x, y| y.cmp(x));
    for i in 0..k {
        println!("{}", abc_values[i]);
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
