pub struct ModUtil {
    fact: Vec<usize>,
    inv_fact: Vec<usize>,
    module: usize,
}

#[allow(dead_code)]
impl ModUtil {
    pub fn new(size: usize, module: usize) -> ModUtil {
        let mut fact = vec![0; size + 1];
        let mut inv_fact = vec![0; size + 1];
        fact[0] = 1;
        for i in 1..size + 1 {
            fact[i] = i * fact[i - 1] % module;
        }
        inv_fact[0] = 1;
        for i in 1..size + 1 {
            inv_fact[i] = ModUtil::mod_pow(fact[i], module - 2, module);
        }
        ModUtil {
            fact: fact,
            inv_fact: inv_fact,
            module: module,
        }
    }

    pub fn permutation(&self, n: usize, k: usize) -> usize {
        assert!(n >= k);
        self.fact[n] % self.module * self.inv_fact(n - k) % self.module
    }
    pub fn combination(&self, n: usize, k: usize) -> usize {
        assert!(n >= k);
        self.fact[n] * self.inv_fact[k] % self.module * self.inv_fact[n - k] % self.module
    }

    pub fn fact(&self, x: usize) -> usize {
        self.fact[x]
    }
    pub fn inv(&self, x: usize) -> usize {
        ModUtil::mod_pow(x, self.module - 2, self.module)
    }
    pub fn inv_fact(&self, x: usize) -> usize {
        self.inv_fact[x]
    }

    fn mod_pow(x: usize, n: usize, module: usize) -> usize {
        if n == 0 {
            return 1;
        }
        let mut res: usize = ModUtil::mod_pow(x, n >> 1, module) % module;
        res = (res * res) % module;
        if n & 1 == 1 {
            res *= x;
        }
        res % module
    }
}

const MOD: usize = 1e9 as usize + 7;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let mut a: Vec<i64> = sc.vec(n);

    a.sort();
    if k == 1 {
        let result = a.iter().fold(0, |sum, x| sum + x);
        println!("{}", 0);
        return;
    }
    //max
    let mut max_cnt: Vec<usize> = vec![0; n];
    let mut min_cnt: Vec<usize> = vec![0; n];
    let mut mod_util = ModUtil::new(100010, MOD);
    for i in 0..n {
        let rest = i;
        if rest >= k - 1 {
            max_cnt[i] = mod_util.combination(rest, k - 1);
        }
        let rest1 = n - i - 1;
        if rest1 >= k - 1 {
            min_cnt[i] = mod_util.combination(rest1, k - 1);
        }
    }
    // println!("{:?} {:?}", max_cnt, min_cnt);
    let mut result = 0;
    for i in 0..n {
        result += max_cnt[i] as i64 * a[i];
        result %= MOD as i64;
        result -= min_cnt[i] as i64 * a[i];
        while result < 0 {
            result += MOD as i64;
        }
        result %= MOD as i64;
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
