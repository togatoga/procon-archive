use std::collections::BTreeMap;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let a: Vec<usize> = sc.vec(n);
    let mut aa = vec![];
    for i in 0..n {
        let mut sum = 0;
        for j in i..n {
            sum += a[j];
            aa.push(sum);
        }
    }
    aa.sort();
    let mut candidates = BTreeMap::new();
    for x in aa.iter() {
        *candidates.entry(x).or_insert(0) += 1;
    }
    let mut result = 0;
    for bit in (0..60).rev() {
        let mut cnt_k = 0;
        let mut next_candidates = BTreeMap::new();
        let bit_v: usize = 1usize << bit;
        for (v, cnt) in candidates.iter() {
            if (*v & bit_v) != 0 {
                cnt_k += *cnt;
                next_candidates.insert(*v, *cnt);
            }
        }
        if cnt_k >= k {
            result |= bit_v;
            candidates = next_candidates;
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
