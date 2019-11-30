use std::collections::HashMap;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let s = sc.chars();
    let t = sc.chars();
    let mut s_to_vec = HashMap::new();
    for i in 0..s.len() {
        s_to_vec.entry(s[i]).or_insert(Vec::new()).push(i);
    }
    let mut idx = 0;
    let mut result = 0;
    let mut diff = 0;
    for x in t.iter() {
        // println!("{} {}", idx, result);
        if let Some(v) = s_to_vec.get(&x) {
            if let Some(res) = v.lower_bound(&idx) {
                idx = v[res] + 1;
                diff = idx - 1;
            } else {
                result += 1;
                idx = v[v.lower_bound(&0).unwrap()] + 1;
                diff = idx - 1;
            }
        } else {
            println!("-1");
            return;
        }
    }
    println!("{}", s.len() * result + diff + 1);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve())
        .unwrap()
        .join()
        .unwrap();
}
use std::cmp::Ordering;

pub trait BinarySearch<T> {
    fn lower_bound(&self, x: &T) -> Option<usize>;
    fn upper_bound(&self, x: &T) -> Option<usize>;
}

impl<T: Ord> BinarySearch<T> for [T] {
    //greater than or equal
    fn lower_bound(&self, x: &T) -> Option<usize> {
        let mut left = 0;
        let mut right = self.len();
        let mut result = None;
        while left < right {
            let med = (left + right) / 2;
            match self[med].cmp(x) {
                Ordering::Less => {
                    left = med + 1;
                }
                Ordering::Equal | Ordering::Greater => {
                    result = Some(med);
                    right = med;
                }
            }
        }
        result
    }
    fn upper_bound(&self, x: &T) -> Option<usize> {
        let mut left = 0;
        let mut right = self.len();
        let mut result = None;
        while left < right {
            let med = (left + right) / 2;
            match self[med].cmp(x) {
                Ordering::Equal | Ordering::Less => {
                    left = med + 1;
                }
                Ordering::Greater => {
                    result = Some(med);
                    right = med;
                }
            }
        }
        result
    }
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
