const MAX_DIGIT: usize = 11;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut pow3: Vec<usize> = vec![0; MAX_DIGIT];
    pow3[0] = 1;
    for x in 1..pow3.len() {
        pow3[x] = 3 * pow3[x - 1];
    }
    let mut result = 0;
    for d in 0..MAX_DIGIT {
        for bit in 0..pow3[d]+1 {
            let mut tmp_bit = bit;
            let mut res = 0;
            for i in 0..d {
                match tmp_bit % 3 {
                    0 => res = 10 * res + 3,
                    1 => res = 10 * res + 5,
                    _ => res = 10 * res + 7,
                }
                tmp_bit /= 3;
                if res > n {
                    break;
                }
            }
            if res <= n {
                let mut cnts = std::collections::HashSet::new();
                while res > 0 {
                    cnts.insert(res % 10);
                    res /= 10;
                }
                if cnts.len() == 3 {
                    result += 1;
                }
            }
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
