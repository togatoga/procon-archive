fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let x: usize = sc.read();
    let a: Vec<usize> = sc.vec::<usize>(m);


    let mut result = 1 << 30;
    {
        //for zero
        let mut pos = x;
        let mut sum = 0;
        while pos != 0 {
            pos = pos - 1;
            for v in &a {
                if pos == *v {
                    sum += 1;
                }
            }
        }
        result = std::cmp::min(result, sum);
    }
    {
        //for N
        let mut pos = x;
        let mut sum = 0;
        while pos != n{
            pos = pos + 1;
            for v in &a {
                if pos == *v {
                    sum += 1;
                }
            }
        }
        result = std::cmp::min(result, sum);
    }
    println!("{}", result);
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
