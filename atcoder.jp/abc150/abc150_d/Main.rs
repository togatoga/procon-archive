use std::collections::HashSet;
fn f(x: usize) -> usize {
    let mut cnt = 0;
    let mut tmp = x;
    while tmp > 0 {
        if tmp % 2 == 0 {
            cnt += 1;
        } else {
            break;
        }
        tmp /= 2;
    }
    cnt
}

fn gcd(x: usize, y: usize) -> usize {
    if y == 0 {
        x
    } else {
        gcd(y, x % y)
    }
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let a: Vec<usize> = sc.vec::<usize>(n).iter().map(|x| x / 2).collect();
    let b: HashSet<usize> = a.iter().map(|x| f(*x)).collect();
    if b.len() != 1 {
        println!("0");
        return;
    }

    let t = f(a[0]);
    let a: Vec<usize> = a.iter().map(|x| x >> t).collect();
    let m = m >> t;
    let mut lcm = a[0];
    for i in 1..n {
        lcm = lcm / gcd(lcm, a[i]) * a[i];
        if lcm > m {
            println!("0");
            return;
        }
    }
    let m = m / lcm;
    let result = (m + 1) / 2;
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
