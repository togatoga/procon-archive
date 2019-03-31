const MAX_N: usize = 100_000;
const MAX_P: usize = 40;
const MOD: usize = 1_000_000_000 + 7;

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
            inv_fact[i] = mod_pow(fact[i], module - 2, module);
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
        mod_pow(x, self.module - 2, self.module)
    }
    pub fn inv_fact(&self, x: usize) -> usize {
        self.inv(self.fact[x])
    }
}

fn mod_pow(x: usize, n: usize, module: usize) -> usize {
    if n == 0 {
        return 1;
    }
    let mut res: usize = mod_pow(x, n / 2, module);
    res = (res % module * res % module) % module;
    if n % 2 == 1 {
        res *= x;
    }
    res % module
}


fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let mut primes = vec![];

    let mut p = 2;
    let mut value = m;

    while p * p <= value {
        let mut count = 0;
        if value % p == 0 {
            while value % p == 0 {
                value /= p;
                count += 1;
            }
            primes.push((p, count));
        }
        p += 1;
    }
    if value != 1 {
        primes.push((value, 1));
    }

    let mod_util = ModUtil::new(MAX_N + 100, MOD);
    let mut ans: usize = 1;
    for x in primes {
        ans *= mod_util.combination(n + x.1 - 1, x.1);
        ans %= MOD;
    }
    println!("{}", ans);
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
