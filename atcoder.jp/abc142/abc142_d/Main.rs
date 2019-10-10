use std::collections::BTreeSet;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let a: u64 = sc.read();
    let b: u64 = sc.read();
    let mut s = BTreeSet::new();
    let mut t = BTreeSet::new();
    {
        let mut div: u64 = 2;
        let mut tmp_a = a;
        while div * div <= tmp_a {
            if tmp_a % div == 0 {
                tmp_a /= div;
                s.insert(div);
            } else {
                div += 1;
            }
        }
        s.insert(tmp_a);
        s.insert(1);
    }
    {
        let mut div: u64 = 2;
        let mut tmp_a = b;
        while div * div <= tmp_a {
            if tmp_a % div == 0 {
                tmp_a /= div;
                t.insert(div);
            } else {
                div += 1;
            }
        }
        t.insert(tmp_a);
        t.insert(1);
    }
    println!("{}", t.intersection(&s).count());
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
