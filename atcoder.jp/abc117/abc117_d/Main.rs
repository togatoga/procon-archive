const MAX_DIGIT: usize = 41;
fn f(k: u64, a: &[u64]) -> u64 {
    let res = a.iter().fold(0, |sum, &x| sum + (x ^ k));
    res
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: u64 = sc.read();
    let mut a: Vec<u64> = sc.vec(n);
    a.sort();

    let mut digits: Vec<usize> = vec![0; MAX_DIGIT];
    for &x in a.iter() {
        for i in 0..MAX_DIGIT {
            let bit = (x >> i) & 1;
            if bit == 1 {
                digits[i] += 1;
            }
        }
    }


    let mut pow2: Vec<u64> = vec![0; MAX_DIGIT];
    pow2[0] = 1;
    for x in 1..MAX_DIGIT {
        pow2[x] = 2u64 * pow2[x - 1];
    }


    let mut result: Vec<char> = format!("{:b}", k).chars().collect();
    while result.len() < MAX_DIGIT {
        result.insert(0, '0');
    }


    let mut ans: u64 = 0;
    for i in 0..result.len() {
        let mut tmp: u64 = 0;
        if result[i] == '1' {
            //101111
            //101110
            for x in 0..i {
                let d1 = digits[result.len() - 1 - x] as u64;//1
                let d2 = n as u64 - d1; //0
                if result[x] == '0' {
                    tmp += d1 * pow2[result.len() - 1 - x];
                } else {
                    tmp += d2 * pow2[result.len() - 1 - x];
                }
            }
            //0
            tmp += (digits[result.len() - 1 - i] as u64) * pow2[result.len() - 1 - i];
            //dbg!((i, tmp));
            for x in i + 1..result.len() {
                let d1 = digits[result.len() - 1 - x];
                let d2 = n - d1;
                let d = std::cmp::max(d1, d2) as u64;
                //dbg!((i, x, d));
                tmp += d * pow2[result.len() - 1 - x];
            }
        }
        //dbg!((i, tmp));
        ans = std::cmp::max(ans, tmp);
    }
    ans = std::cmp::max(ans, f(0, &a));
    ans = std::cmp::max(ans, f(k, &a));

    println!("{}", ans);
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
