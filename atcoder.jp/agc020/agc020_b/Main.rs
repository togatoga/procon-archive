fn f(x: usize, a: &[usize]) -> usize {
    let mut rest = x;
    for &v in a.iter() {
        rest = rest / v * v;
    }
    rest
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let k: usize = sc.read();
    let a: Vec<usize> = sc.vec(k);
    let min_val = {
        let mut left = 0;
        let mut right = 1usize << 60;
        let mut result = None;
        while right - left > 1 {
            let med = (right + left) / 2;
            let tmp = f(med, &a);
            if tmp >= 2 {
                right = med;
            } else {
                left = med;
            }
            if tmp == 2 {
                if result.is_none() {
                    result = Some(med);
                } else {
                    if result.unwrap() >= med {
                        result = Some(med);
                    }
                }
            }
        }
        result
    };
    let max_val = {
        let mut left = 0;
        let mut right = 1usize << 60;
        let mut result = None;
        while right - left > 1 {
            let med = (right + left) / 2;
            let tmp = f(med, &a);
            if tmp <= 2 {
                left = med;
            } else {
                right = med;
            }
            if tmp == 2 {
                if result.is_none() {
                    result = Some(med);
                } else {
                    if result.unwrap() <= med {
                        result = Some(med);
                    }
                }
            }
        }
        result
    };
    if min_val.is_none() || max_val.is_none() {
        println!("{}", -1);
        return;
    }
    println!("{} {}", min_val.unwrap(), max_val.unwrap());
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
