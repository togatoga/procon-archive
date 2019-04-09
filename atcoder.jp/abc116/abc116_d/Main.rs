use std::collections::{BinaryHeap, HashMap};

fn f(x: usize) -> u64 {
    x as u64 * x as u64
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let k: usize = sc.read();
    let mut heap = BinaryHeap::new();
    let tks: Vec<(usize, i64)> = (0..n).map(|_| {
        let t: usize = sc.read();
        let d: i64 = sc.read();
        heap.push((d, t));
        (t, d)
    }).collect();
    let mut rest_heap = BinaryHeap::new();
    let mut state_heap = BinaryHeap::new();
    let mut state_kind = HashMap::new();

    let mut result: u64 = 0;
    let mut current_point: u64 = 0;

    while let Some((delicious, kind)) = heap.pop() {
        if state_heap.len() >= k || state_kind.contains_key(&kind) {
            rest_heap.push((delicious, kind));
        } else {
            current_point += delicious as u64;
            //println!("{} {}", current_point, delicious);
            *state_kind.entry(kind).or_insert(0) += 1;
            state_heap.push((-delicious, kind));
        }
    }
    while state_heap.len() < k {
        if let Some((delicious, kind)) = rest_heap.pop() {
            current_point += delicious as u64;
            *state_kind.entry(kind).or_insert(0) += 1;
            state_heap.push((-delicious, kind));
        }
    }
    //println!("{:?}", state_kind);
    result = std::cmp::max(result, current_point + f(state_kind.len()));
    //println!("{} {} {}", result, current_point, state_kind.len());
    for i in 0..n {
        if let Some((delicious, kind)) = state_heap.pop() {
            assert!(delicious < 0);
            let delicious = delicious * -1;
            *state_kind.entry(kind).or_insert(0) -= 1;
            current_point -= delicious as u64;

            rest_heap.push((delicious, kind));
            if *state_kind.get(&kind).unwrap() == 0 {
                state_kind.remove(&kind);
            }
        }
        if let Some((rest_delicious, rest_kind)) = rest_heap.pop() {
            current_point += rest_delicious as u64;
            *state_kind.entry(rest_kind).or_insert(0) += 1;
            state_heap.push((-rest_delicious, rest_kind));
        }
        //assert_eq!(state_heap.len(), k);


        result = std::cmp::max(result, current_point + f(state_kind.len()));
        //println!("{} {} {} {}", result, current_point + f(state_kind.len()), current_point, state_kind.len());
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
