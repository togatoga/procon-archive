fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let a: i32 = sc.read();
    let b: i32 = sc.read();
    let c: i32 = sc.read();
    let d: i32 = sc.read();
    let d1 = (a - b).abs();
    let d2 = (b - c).abs();
    let d3 = (a - c).abs();
    if d1 <= d && d2 <= d || d3 <= d {
        println!("Yes");
        return ;
    }
    println!("No");
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
    pub fn vec<T: std::str::FromStr>(&mut self, n: usize) -> Vec<T> {
        (0..n).map(|_| self.read()).collect()
    }
    pub fn chars(&mut self) -> Vec<char> {
        self.read::<String>().chars().collect()
    }
}
