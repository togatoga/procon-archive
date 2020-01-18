const MAX_N: usize = 200100;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let p: Vec<usize> = sc.vec(n);
    let mut a = vec![0; n];
    for i in 1..n {
        if p[i - 1] < p[i] {
            a[i] = 1;
        }
        a[i] += a[i - 1];
    }
    let mut st = std::collections::BTreeSet::new();
    for i in 0..k {
        st.insert(p[i]);
    }
    let mut cute = if a[k - 1] == k - 1 { 1 } else { 0 };
    let mut result = if cute == 1 { 0 } else { 1 };
    for i in 0..n - k {
        let mut ok = true;
        let min = *st.iter().next().unwrap();
        if min != p[i] {
            ok = false;
        }
        st.remove(&p[i]);
        st.insert(p[i + k]);
        let max = *st.iter().next_back().unwrap();
        if max != p[i + k] {
            ok = false;
        }
        if a[i + k] - a[i + 1] == k - 1 {
            cute = 1;
        } else if !ok {
            result += 1;
        }
    }
    println!("{}", result + cute);
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
