const MAX_N: usize = 100010;

fn dfs(pos: usize, colors: &mut Vec<i32>, edges: &Vec<Vec<(usize, usize)>>) -> bool {
    for &(nxt, weight) in edges[pos].iter() {
        if colors[nxt] != -1 {
            continue;
        }
        if weight % 2 == 0 {
            colors[nxt] = colors[pos];
            dfs(nxt, colors, edges);
        } else {
            if colors[pos] == 0 {
                colors[nxt] = 1;
            } else {
                colors[nxt] = 0;
            }
            dfs(nxt, colors, edges);
        }
    }
    true
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut edges: Vec<Vec<(usize, usize)>> = vec![Vec::new(); MAX_N];
    for _ in 0..n - 1 {
        let u: usize = sc.read::<usize>() - 1;
        let v: usize = sc.read::<usize>() - 1;
        let w: usize = sc.read();
        edges[u].push((v, w));
        edges[v].push((u, w));
    }
    let mut colors = vec![-1; MAX_N];
    colors[0] = 0;
    dfs(0, &mut colors, &edges);
    for i in 0..n {
        println!("{}", colors[i]);
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
