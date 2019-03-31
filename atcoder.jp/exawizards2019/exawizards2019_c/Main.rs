fn escape(src: usize, n: usize, s: &Vec<char>, q: &Vec<(char, char)>) -> (bool, char) {
    let mut pos = src as i32;
    for &(t, d) in q.into_iter() {
        let p = s[pos as usize];
        if t == p {
            if d == 'L' {
                pos -= 1;
            } else {
                pos += 1;
            }
        }
        if pos < 0 {
            return (true, 'L');
        }
        if pos >= n as i32 {
            return (true, 'R');
        }
    }
    return (false, 'N');
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let q: usize = sc.read();
    let s = sc.chars();
    let td = (0..q).map(|_| {
        let t = sc.chars();
        let d = sc.chars();
        (t[0], d[0])
    }).collect::<Vec<(char, char)>>();

    let mut result = 0;
    {
        let mut left: i32 = -10;
        let mut right: i32 = n as i32 + 10;
        let mut tmp = 0;
        while right - left > 1 {
            let mut med = (right + left) / 2;
            if med < 0 {
                left = med;
                continue;
            }
            if med >= n as i32 {
                right = med;
                continue;
            }

            let res = escape(med as usize, n, &s, &td);
            if res.0 && res.1 == 'L' {
                left = med;
                tmp = (med + 1) as usize;
            } else {
                right = med;
            }
        }
        result += tmp;
    }

    {
        let mut left: i32 = -10;
        let mut right: i32 = n as i32 + 10;
        let mut tmp = 0;
        while right - left > 1 {
            let mut med = (right + left) / 2;
            if med < 0 {
                left = med;
                continue;
            }
            if med >= n as i32 {
                right = med;
                continue;
            }

            let res = escape(med as usize, n, &s, &td);
            if res.0 && res.1 == 'R' {
                right = med;
                tmp = (n as i32 - med) as usize;
            } else {
                left = med;
            }
        }
        result += tmp;
    }
    println!("{}", n - result);
}


fn main() {
    let thd = std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve()).unwrap().join().unwrap();
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
