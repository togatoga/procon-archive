pub mod fenwick_tree {
    use std::ops::AddAssign;
    use std::ops::Sub;
    //Binary Indexed Tree
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

        pub fn add(&mut self, i: usize, x: &T) {
            let mut index = i;
            while index < self.values.len() {
                self.values[index] += *x;
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
            bit.add(k, &value);

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

#[cfg(test)]
mod tests {
    use super::*;
    use rand::{thread_rng, Rng};
    #[test]
    fn test_binary_search() {
        let vec = vec![-100, 0, 1, 2, 10, 100, 1000];
        assert_eq!(vec.lower_bound(&1), Some(2));
        assert_eq!(vec.lower_bound(&100), Some(5));
        assert_eq!(vec.lower_bound(&-5000), Some(0));
        assert_eq!(vec.lower_bound(&999), Some(6));
        assert_eq!(vec.lower_bound(&1001), None);

        assert_eq!(vec.upper_bound(&-101), Some(0));
        assert_eq!(vec.upper_bound(&0), Some(2));
        assert_eq!(vec.upper_bound(&100), Some(6));
        assert_eq!(vec.upper_bound(&1000), None);
    }

    #[test]
    fn test_random_binary_search() {
        let test_case = 50;
        let max_value = 200;
        let query_num = 100;
        let mut rng = thread_rng();
        for _ in 0..test_case {
            let mut seq: Vec<i32> = (0..500).map(|_| rng.gen_range(0, max_value)).collect();
            seq.sort();

            for _ in 0..query_num {
                let query = rng.gen_range(0, max_value + 100);
                let result = (seq.lower_bound(&query), seq.upper_bound(&query));
                //sequential search
                let naive_search = |x: i32| {
                    let mut lower_result = None;
                    let mut upper_result = None;
                    for i in 0..seq.len() {
                        if lower_result.is_none() && x <= seq[i] {
                            lower_result = Some(i);
                        }
                        if upper_result.is_none() && x < seq[i] {
                            upper_result = Some(i);
                        }
                    }
                    (lower_result, upper_result)
                };

                assert_eq!(result, naive_search(query));
            }
        }
    }
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let d: usize = sc.read();
    let a: usize = sc.read();
    let mut xh: Vec<(usize, usize)> = (0..n)
        .map(|_| {
            let x: usize = sc.read();
            let h: usize = sc.read();
            (x, (h + (a - 1)) / a)
        })
        .collect();
    xh.sort();
    let mut xx = vec![0; n];
    for i in 0..n {
        xx[i] = (xh[i].0) as i64;
    }
    //println!("{:?}", xh);
    let mut bit = fenwick_tree::FenwickTree::new(n + 10, &0);
    let mut result = 0;
    for i in 0..n {
        let (x, cnt) = xh[i];
        // let p = {
        //     let mut left = 0;
        //     let mut right = n;
        //     while right - left > 1 {
        //         let med = (right + left) / 2;
        //         if x <= xh[med].0 {
        //             left = med;
        //         } else {
        //             right = med;
        //         }
        //     }
        //     left
        // };
        let res = bit.query(i, n + 1);
        if res >= cnt {
            continue;
        }
        let diff = cnt - res;
        let point = (x + 2 * d) as i64;
        // let idx = {
        //     let mut left = 0;
        //     let mut right = n;
        //     while right - left > 1 {
        //         let med = (right + left) / 2;
        //         // println!("{} {} {} {} {}", left, right, med, point, xh[med].0);
        //         if xh[med].0 <= point {
        //             left = med + 1;
        //         } else {
        //             right = med;
        //         }
        //     }
        //     right
        // };
        let idx = if let Some(tmp) = xx.upper_bound(&point) {
            tmp - 1
        } else {
            n
        };
        // println!("{} {} {}", point, idx, diff);
        bit.add(idx, &diff);
        result += diff;
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
