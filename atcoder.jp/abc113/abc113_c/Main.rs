fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let mut py = (0..m).map(|idx| {
        let p: usize = sc.read();
        let y: usize = sc.read();
        (p, y, idx)
    }).collect::<Vec<(usize, usize, usize)>>();
    py.sort_by(|x, y| x.1.cmp(&y.1));
    let mut cities_cnt = vec![0; n + 1];

    let mut result = py.iter().map(|x| {
        let p = x.0;
        let y = x.1;
        let idx = x.2;
        let upper = format!("{:06}", p);
        let bottom = format!("{:06}", cities_cnt[p] + 1);
        cities_cnt[p] += 1;
        (idx, upper + &bottom)
    }).collect::<Vec<(usize, String)>>();
    result.sort_by(|x, y| x.0.cmp(&y.0));

    for x in result {
        println!("{}", x.1);
    }
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
