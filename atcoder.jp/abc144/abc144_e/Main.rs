fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: u64 = sc.read();
    let mut a: Vec<u64> = sc.vec(n);
    let sum = a.iter().fold(0, |sum, a| sum + a);
    if sum <= k {
        println!("{}", 0);
        return;
    }
    a.sort();
    a.reverse();
    let mut f: Vec<u64> = sc.vec(n);
    f.sort();

    let mut left = 0;
    let mut right = 1 << 60;
    while right - left > 1 {
        let med = (right + left) / 2;
        let mut tmp_k = k;
        let mut ok = true;
        for i in 0..n {
            if a[i] * f[i] > med {
                let tmp = a[i] - med / f[i];
                if tmp_k < tmp {
                    ok = false;
                    break;
                }
                tmp_k -= tmp;
            }
        }
        if ok {
            right = med;
        } else {
            left = med;
        }
    }
    println!("{}", right);
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
