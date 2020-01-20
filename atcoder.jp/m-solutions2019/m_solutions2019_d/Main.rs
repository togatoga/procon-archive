use std::collections::BinaryHeap;
use std::collections::VecDeque;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut degrees = vec![0; n];
    let mut values = vec![0; n];
    let mut edges: Vec<Vec<usize>> = vec![vec![]; n];
    for i in 0..n - 1 {
        let a: usize = sc.read();
        let b: usize = sc.read();
        degrees[a - 1] += 1;
        degrees[b - 1] += 1;
        edges[a - 1].push(b - 1);
        edges[b - 1].push(a - 1);
    }
    let mut c: Vec<usize> = sc.vec(n);
    c.sort();
    c.reverse();
    let cost = c.iter().skip(1).fold(0, |sum, a| sum + a);
    let mut heap = BinaryHeap::new();
    for i in 0..n {
        heap.push((degrees[i], i));
    }
    let root = heap.peek().unwrap();
    let mut que = VecDeque::new();
    que.push_back(root.1);
    let mut c_idx = 0;
    while let Some(index) = que.pop_front() {
        //println!("{} {}", degree, index);
        if values[index] != 0 {
            continue;
        }
        values[index] = c[c_idx];
        c_idx += 1;
        for &x in edges[index].iter() {
            if values[x] != 0 {
                continue;
            }
            que.push_back(x);
        }
    }
    println!("{}", cost);
    for &i in values.iter() {
        print!("{} ", i);
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
