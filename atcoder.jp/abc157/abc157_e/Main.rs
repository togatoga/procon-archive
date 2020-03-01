pub mod fenwick_tree {
    //Binary Indexed Tree
    use std::ops::*;
    pub struct FenwickTree<T> {
        values: Vec<T>,
        init_value: T,
    }

    impl<T: Copy + Clone + AddAssign + Sub<Output = T>> FenwickTree<T> {
        pub fn new(n: usize, init_value: &T) -> FenwickTree<T> {
            FenwickTree {
                values: vec![init_value.clone(); n + 1],
                init_value: init_value.clone(),
            }
        }
        //[l, r)
        pub fn query(&self, l: usize, r: usize) -> T {
            self.sum(r) - self.sum(l)
        }
        //[0, i)
        pub fn sum(&self, i: usize) -> T {
            let mut result = self.init_value;
            let mut x = i as i32 - 1;
            while x >= 0 {
                result += self.values[x as usize];
                x = (x & (x + 1)) - 1;
            }
            result
        }

        pub fn add(&mut self, i: usize, x: T) {
            let mut index = i;
            while index < self.values.len() {
                self.values[index] += x;
                index |= index + 1;
            }
        }
    }
}
#[cfg(test)]
mod test {
    use super::fenwick_tree::FenwickTree;
    use rand::{thread_rng, Rng};
    #[test]
    fn random_array() {
        let n = 1000;
        let mut bit = FenwickTree::new(n, &0);
        let mut v = vec![0; n];
        for _ in 0..10000 {
            let value = thread_rng().gen_range(0, 1000);
            let k = thread_rng().gen_range(0, n);
            v[k] += value;
            bit.add(k, value);

            let mut sum = 0;
            for i in 0..n {
                sum += v[i];
                assert_eq!(sum, bit.sum(i + 1));
            }

            let l = thread_rng().gen_range(0, n);
            let r = thread_rng().gen_range(l, n);
            sum = 0;
            for i in l..r {
                sum += v[i];
                assert_eq!(sum, bit.query(l, i + 1));
            }
        }
    }
}

use std::collections::HashMap;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut s = sc.chars();
    let q: usize = sc.read();
    let mut char_to_idx = HashMap::new();
    for (idx, c) in "abcdefghijklmnopqrstuvwxyz".chars().enumerate() {
        char_to_idx.insert(c, idx);
        //println!("{}", idx);
    }
    let mut bits: Vec<fenwick_tree::FenwickTree<i32>> = (0..30)
        .map(|_| fenwick_tree::FenwickTree::new(n + 10, &0))
        .collect();
    for (i, x) in s.iter().enumerate() {
        let idx: usize = *char_to_idx.get(x).unwrap();
        bits[idx].add(i, 1);
    }
    for _ in 0..q {
        let t: usize = sc.read();
        if t == 1 {
            let i: usize = sc.read();
            let c: char = sc.chars()[0];
            //println!("{} {}", i, c);
            let idx: usize = *char_to_idx.get(&c).unwrap();
            let pre_idx = *char_to_idx.get(&s[i - 1]).unwrap();
            s[i - 1] = c;
            bits[pre_idx].add(i - 1, -1);
            bits[idx].add(i - 1, 1);
        } else {
            let mut result = 0;
            let l: usize = sc.read();
            let r: usize = sc.read();
            for i in 0..30 {
                let sum = bits[i].query(l - 1, r);
                if sum > 0 {
                    result += 1;
                }
            }
            println!("{}", result);
        }
    }
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve())
        .unwrap()
        .join()
        .unwrap();
}
pub mod utils {
    const DYX: [(isize, isize); 8] = [
        (0, 1),   //right
        (1, 0),   //down
        (0, -1),  //left
        (-1, 0),  //top
        (1, 1),   //down right
        (-1, 1),  //top right
        (1, -1),  //down left
        (-1, -1), //top left
    ];

    pub fn try_adj(y: usize, x: usize, dir: usize, h: usize, w: usize) -> Option<(usize, usize)> {
        let ny = y as isize + DYX[dir].0;
        let nx = x as isize + DYX[dir].1;
        if ny >= 0 && nx >= 0 {
            let ny = ny as usize;
            let nx = nx as usize;
            if ny < h && nx < w {
                Some((ny, nx))
            } else {
                None
            }
        } else {
            None
        }
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
