pub struct State {
    a: usize,
    c: Vec<usize>,
}
const INF: usize = 1 << 30;
impl State {
    pub fn new(a: usize, c: Vec<usize>) -> State {
        State { a: a, c: c }
    }
}

pub fn memo(
    p: usize,
    bit: usize,
    states: &Vec<State>,
    memos: &mut Vec<Vec<Option<usize>>>,
    n: usize,
) -> usize {
    let all_bit: usize = (1 << n) - 1;
    if bit == all_bit {
        return 0;
    }
    if p == states.len() {
        return INF;
    }
    if let Some(value) = memos[p][bit] {
        return value;
    }
    let mut result = INF;
    //not buy
    result = std::cmp::min(result, memo(p + 1, bit, states, memos, n));
    //buy
    let mut next_bit = bit;
    for c in states[p].c.iter() {
        next_bit |= (1 << (c - 1)) as usize;
    }
    result = std::cmp::min(
        result,
        memo(p + 1, next_bit, states, memos, n) + states[p].a,
    );
    memos[p][bit] = Some(result);
    return result;
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let mut states = vec![];
    for _ in 0..m {
        let a: usize = sc.read();
        let b: usize = sc.read();
        let c: Vec<usize> = sc.vec(b);
        states.push(State::new(a, c));
    }
    let mut memos = vec![vec![None; 1 << 13]; m + 1];
    let result = memo(0, 0, &states, &mut memos, n);
    if result >= INF {
        println!("-1");
        return;
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
