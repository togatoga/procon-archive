const MOD: usize = 1e9 as usize + 7;
fn dp(pos: usize, module: usize, schars: &[char], memo: &mut Vec<Vec<Option<usize>>>) -> usize {
    if pos >= schars.len() {
        let res = if module == 5 { 1 } else { 0 };
        return res;
    }
    if let Some(value) = memo[pos][module] {
        return value;
    }
    let mut result = 0;
    if schars[pos] == '?' {
        for x in 0..10 {
            let next_module = (module * 10 + x) % 13;
            result += dp(pos + 1, next_module, schars, memo);
            result %= MOD;
        }
    } else {
        let next_module = (module * 10 + schars[pos].to_digit(10).unwrap() as usize) % 13;
        result += dp(pos + 1, next_module, schars, memo);
        result %= MOD;
    }
    memo[pos][module] = Some(result);
    return result;
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let schars = sc.chars();
    let mut memo = vec![vec![None; 13]; schars.len() + 1];
    let result = dp(0, 0, &schars, &mut memo);
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
