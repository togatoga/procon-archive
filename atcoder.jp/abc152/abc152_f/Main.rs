const MAX_N: usize = 51;
fn dfs(pos: usize, pre: usize, v: usize, edges: &Vec<Vec<usize>>, paths: &mut Vec<usize>) -> bool {
    if pos == v {
        return true;
    }
    for &nxt in edges[pos].iter() {
        if nxt == pre {
            continue;
        }
        paths.push(nxt);
        let ok = dfs(nxt, pos, v, edges, paths);
        if ok {
            return true;
        }
        paths.pop();
    }
    return false;
}
fn build_path(u: usize, v: usize, edges: &Vec<Vec<usize>>) -> Vec<usize> {
    let mut paths = vec![];
    paths.push(u);
    dfs(u, u, v, edges, &mut paths);
    paths
}
fn memo(
    idx: usize,
    bit: usize,
    m: usize,
    bits: &Vec<Vec<usize>>,
    edges: &Vec<(usize, usize)>,
    dp: &mut Vec<Vec<Option<usize>>>,
) -> usize {
    if idx == edges.len() {
        if bit == (1 << m) - 1 {
            return 1;
        }
        return 0;
    }
    if let Some(value) = dp[idx][bit] {
        return value;
    }
    let mut result = 0;
    let (a, b) = edges[idx];
    //fill
    result += memo(idx + 1, bit | bits[a][b], m, bits, edges, dp);
    result += memo(idx + 1, bit, m, bits, edges, dp);
    dp[idx][bit] = Some(result);
    result
}

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut edges = vec![vec![]; n];
    let mut n_edges = vec![];
    for _ in 0..n - 1 {
        let a: usize = sc.read();
        let b: usize = sc.read();
        edges[a - 1].push(b - 1);
        edges[b - 1].push(a - 1);
        n_edges.push((a - 1, b - 1));
    }
    let m: usize = sc.read();
    let mut bits = vec![vec![0; MAX_N]; MAX_N];
    for i in 0..m {
        let u: usize = sc.read();
        let v: usize = sc.read();
        let path = build_path(u - 1, v - 1, &edges);
        for x in path.windows(2) {
            bits[x[0]][x[1]] |= 1 << i;
            bits[x[1]][x[0]] |= 1 << i;
        }
    }
    let mut dp = vec![vec![None; 1 << m]; MAX_N];
    let result = memo(0, 0, m, &bits, &n_edges, &mut dp);
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
