fn memo(
    pos: usize,
    less: bool,
    cnt: usize,
    n: &[char],
    k: usize,
    dp: &mut Vec<Vec<Vec<Option<usize>>>>,
) -> usize {
    if cnt > k {
        return 0;
    }
    if pos >= n.len() {
        if cnt == k {
            return 1;
        }
        return 0;
    }
    if let Some(tmp) = dp[pos][less as usize][cnt] {
        return tmp;
    }
    let value = n[pos].to_digit(10).unwrap();
    //0
    let mut result = 0;
    if 0 < value {
        result += memo(pos + 1, true, cnt, n, k, dp);
    } else {
        result += memo(pos + 1, less, cnt, n, k, dp);
    }
    //1
    for x in 1..10 {
        if less {
            result += memo(pos + 1, less, cnt + 1, n, k, dp);
        } else {
            if x < value {
                result += memo(pos + 1, true, cnt + 1, n, k, dp);
            } else if x == value {
                result += memo(pos + 1, less, cnt + 1, n, k, dp);
            }
        }
    }
    dp[pos][less as usize][cnt] = Some(result);
    result
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n = sc.chars();
    let k: usize = sc.read();
    let mut dp = vec![vec![vec![None; 4]; 2]; 110];
    let result = memo(0, false, 0, &n, k, &mut dp);
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
