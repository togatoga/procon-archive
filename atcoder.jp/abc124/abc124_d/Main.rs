const MAX_N: usize = 100100;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: u32 = sc.read();
    let ss: Vec<char> = sc.chars();
    let mut sum : Vec<u32> = vec![0; n];



    for i in 1..n {
        if ss[i - 1] == '1' && ss[i] == '0' {
            sum[i] = 1;
        }
    }
    for i in 0..n - 1 {
        sum[i + 1] += sum[i];
    }
    let mut result = 1;
    for i in 0..n {
        let mut left = 0;
        let mut right = n + 10;
        while right - left > 1 {
            let med = (right + left) / 2;
            if i + med >= n {
                right = med;
                continue;
            }
            let mut cost = sum[i + med];
            if i >= 1 {
                cost -= sum[i - 1];
            }
            if ss[i] == '0' {
                cost += 1;
            }
            if cost <= k {
                left = med;
            } else {
                right = med;
            }
        }
        result = std::cmp::max(result, left + 1);
    }
    println!("{}", result);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(256 * 1024 * 1024) // 64MB
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