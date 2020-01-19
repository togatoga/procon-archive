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

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let p: Vec<usize> = sc.vec(n);
    let mut bit = fenwick_tree::FenwickTree::new(200010, &0);
    let mut result = 0;
    for (idx, x) in p.iter().enumerate() {
        bit.add(*x, &1);
        if bit.sum(200009) - bit.sum(*x) == idx + 1 {
            result += 1;
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
