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

#[cfg(test)]
mod test {
    use super::*;
    #[test]
    fn test_mod_util() {
        const module: usize = 1e9 as usize + 7;
        let mod_util = ModUtil::new(1000, module);
        //fact
        assert_eq!(mod_util.fact(5), 120);
        assert_eq!(mod_util.fact(10), 3628800);
        assert_eq!(mod_util.fact(500), 688653593);
        assert_eq!(mod_util.fact(1000), 641419708);
        //combination
        assert_eq!(mod_util.combination(5, 3), 10);
        assert_eq!(mod_util.combination(10, 2), 45);
        assert_eq!(mod_util.combination(1000, 500), 159835829);
        //permutation
        assert_eq!(mod_util.permutation(5, 3), 60);
        assert_eq!(mod_util.permutation(10, 3), 720);
        assert_eq!(mod_util.permutation(1000, 999), 641419708);
    }
}

const MOD: usize = 1000000007;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let mut x: usize = sc.read();
    let mut y: usize = sc.read();
    if x > y {
        std::mem::swap(&mut x, &mut y);
    }
    if (2 * y - x) % 3 != 0 {
        println!("0");
        return;
    }
    let b = (2 * y - x) / 3;
    if y < 2 * b {
        println!("0");
        return ;
    }
    let a = y - 2 * b;
    let mod_util = ModUtil::new(2000010, MOD);
    let c_fact = mod_util.fact(a + b);
    let a_inv_fact = mod_util.inv_fact(a);
    let b_inv_fact = mod_util.inv_fact(b);
    println!("{}", c_fact % MOD * a_inv_fact % MOD * b_inv_fact % MOD);
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
