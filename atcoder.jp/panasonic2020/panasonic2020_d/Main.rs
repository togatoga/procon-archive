use std::collections::HashSet;
const ALPHA: [&'static str; 10] = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"];

fn dfs(pos: usize, values: &mut Vec<Option<usize>>, seq: &mut Vec<String>) {
    if pos == 0 {
        let mut idx = 0;
        let mut results = vec![];
        for value in values.iter() {
            if let Some(v) = value.as_ref() {
                if *v >= results.len() {
                    results.push(ALPHA[idx]);
                    idx += 1;
                } else {
                    let tmp = results[*v];
                    results.push(tmp);
                }
            } else {
                results.push(ALPHA[idx]);
                idx += 1;
            }
        }
        seq.push(results.join(""));
        return;
    }
    if values[pos].is_some() {
        dfs(pos - 1, values, seq);
        return;
    }
    for i in (0..pos + 1).rev() {
        values[pos] = Some(i);
        values[i] = Some(i);
        dfs(pos - 1, values, seq);
        values[pos] = None;
        values[i] = None;
    }
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut values = vec![None; n];
    // dfs(0, 0, &mut used, n, &mut dp);
    let mut results = vec![];
    dfs(n - 1, &mut values, &mut results);
    results.sort();
    results.dedup();
    for x in results.iter() {
        println!("{}", x);
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
