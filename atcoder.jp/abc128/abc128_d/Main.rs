fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let v: Vec<i32> = sc.vec(n);
    let mut result = 0;
    for left in 0..n + 1 {
        for right in (0..n + 1).rev() {
            let cnt = left + right;
            if cnt > k {
                continue;
            }
            if left >= 1 {
                if n - right <= left - 1 {
                    continue;
                }
            }
            let mut tmp = vec![];
            for i in 0..left {
                tmp.push(v[i]);
            }
            for i in (n - right..n).rev() {
                tmp.push(v[i]);
            }
            tmp.sort();
            let mut rest = k - cnt;
            for i in 0..tmp.len() {
                if rest <= 0 {
                    break;
                }
                if tmp[i] >= 0 {
                    break;
                }
                if tmp[i] < 0 {
                    tmp[i] = 0;
                    rest -= 1;
                }
            }
            result = std::cmp::max(result, tmp.iter().fold(0, |sum, x| sum + x));
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
