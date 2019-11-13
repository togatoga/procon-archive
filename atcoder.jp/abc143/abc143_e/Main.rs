const INF: usize = 1 << 30;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let l: usize = sc.read();

    let mut dist = vec![vec![INF; n]; n];
    for _ in 0..m {
        let a: usize = sc.read::<usize>() - 1;
        let b: usize = sc.read::<usize>() - 1;
        let c: usize = sc.read::<usize>();
        dist[a][b] = c;
        dist[b][a] = c;
    }
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                if dist[i][k] + dist[k][j] < dist[i][j] {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    let mut v_dist = vec![vec![INF; n]; n];

    for i in 0..n {
        for j in 0..n {
            if dist[i][j] <= l {
                v_dist[i][j] = 1;
            }
        }
    }

    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                if v_dist[i][k] + v_dist[k][j] < v_dist[i][j] {
                    v_dist[i][j] = v_dist[i][k] + v_dist[k][j];
                }
            }
        }
    }

    let q: usize = sc.read();
    for _ in 0..q {
        let s: usize = sc.read::<usize>() - 1;
        let t: usize = sc.read::<usize>() - 1;
        if v_dist[s][t] >= INF {
            println!("-1");
        } else {
            println!("{}", v_dist[s][t] - 1);
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
