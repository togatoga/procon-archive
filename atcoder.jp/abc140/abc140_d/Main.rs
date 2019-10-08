fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let mut s = sc.chars();
    let mut pre = s[0];
    let mut cnt = 1;

    let mut s1 = s.clone(); //R
    let mut s2 = s.clone(); //L
    let mut k1 = k;
    let mut k2 = k;
    for i in 1..n {
        if pre != s[i] {
            if pre == 'L' {
                if k1 > 0 {
                    k1 -= 1;
                    for j in i - cnt..i {
                        s1[j] = 'R';
                    }
                }
            } else {
                if k2 > 0 {
                    k2 -= 1;
                    for j in i - cnt..i {
                        s2[j] = 'L';
                    }
                }
            }
            cnt = 1;
        } else {
            cnt += 1;
        }
        pre = s[i];
    }
    if pre == 'L' {
        if k1 > 0 {
            k1 -= 1;
            for j in n - cnt..n {
                s1[j] = 'R';
            }
        }
    } else {
        if k2 > 0 {
            k2 -= 1;
            for j in n - cnt..n {
                s2[j] = 'L';
            }
        }
    }
    let mut res1 = 0;
    let mut res2 = 0;
    for i in 0..n {
        if s1[i] == 'L' {
            if i >= 1 && s1[i - 1] == 'L' {
                res1 += 1;
            }
        } else {
            if i + 1 < n && s1[i + 1] == 'R' {
                res1 += 1;
            }
        }

        if s2[i] == 'L' {
            if i >= 1 && s2[i - 1] == 'L' {
                res2 += 1;
            }
        } else {
            if i + 1 < n && s2[i + 1] == 'R' {
                res2 += 1;
            }
        }
    }
    println!("{}", std::cmp::max(res1, res2));
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
