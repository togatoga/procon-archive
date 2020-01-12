use std::collections::HashSet;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let ps: Vec<(usize, String)> = (0..m)
        .map(|_| {
            let p: usize = sc.read();
            let s: String = sc.read();
            (p, s)
        })
        .collect();
    let mut ac = vec![0; n + 1];
    let mut wa = vec![0; n + 1];
    for ps in ps.iter() {
        if ps.1 == "AC" {
            ac[ps.0] = 1;
        } else if ps.1 == "WA" {
            if ac[ps.0] == 1 {
                continue;
            }
            wa[ps.0] += 1;
        }
    }
    let mut wa_cnt = 0;
    for i in 0..n + 1 {
        if ac[i] == 1 {
            wa_cnt += wa[i];
        }
    }
    println!("{} {}", ac.iter().fold(0, |sum, x| sum + x), wa_cnt);
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
