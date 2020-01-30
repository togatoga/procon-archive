fn dfs(
    pos: usize,
    pre: usize,
    color: usize,
    edges: &Vec<Vec<usize>>,
    result: &mut Vec<(usize, usize, usize)>,
) {
    let mut next_color = if color == 0 { 1 } else { 0 };
    for &nxt in edges[pos].iter() {
        if nxt == pre {
            continue;
        }
        result.push((pos, nxt, next_color));
        dfs(nxt, pos, next_color, edges, result);
        next_color += 1;
        if next_color == color {
            next_color += 1;
        }
    }
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut edges: Vec<Vec<usize>> = vec![vec![]; n];
    let mut degrees: Vec<usize> = vec![0; n];
    let ab: Vec<(usize, usize)> = (0..n - 1)
        .map(|_| {
            let a: usize = sc.read();
            let b: usize = sc.read();
            edges[a - 1].push(b - 1);
            edges[b - 1].push(a - 1);
            degrees[a - 1] += 1;
            degrees[b - 1] += 1;
            if a >= b {
                (b - 1, a - 1)
            } else {
                (a - 1, b - 1)
            }
        })
        .collect();

    let k = degrees.iter().max().unwrap();
    println!("{}", k);
    let mut result = vec![];
    dfs(0, 0, 123456, &edges, &mut result);
    let mut indices = std::collections::HashMap::new();
    for &(a, b, color) in result.iter() {
        if a >= b {
            indices.insert((b, a), color);
        } else {
            indices.insert((a, b), color);
        }
    }
    // println!("{:?}", indices);
    for x in ab.iter() {
        println!("{}", indices.get(x).unwrap() + 1);
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
