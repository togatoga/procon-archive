use std::collections::VecDeque;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let s: Vec<Vec<char>> = (0..n).map(|_| sc.chars()).collect();
    let mut degrees = vec![0; n];
    for i in 0..n {
        for j in i..n {
            if s[i][j] == '1' {
                degrees[i] += 1;
                degrees[j] += 1;
            }
        }
    }
    let min_value = degrees.iter().min().unwrap();
    let idx = degrees.iter().position(|x| x == min_value).unwrap();

    let mut result = None;
    for src in 0..n {
        let mut ok = true;
        let mut v = vec![None; n];
        let mut que = VecDeque::new();
        que.push_back((src, 1));
        while let Some(value) = que.pop_front() {
            let (pos, idx) = value;
            // println!("{} {}", pos, idx);
            if let Some(p) = v[pos] {
                if p != idx {
                    ok = false;
                    break;
                }
                continue;
            }
            v[pos] = Some(idx);
            for i in 0..n {
                if s[pos][i] == '1' {
                    if let Some(p) = v[i] {
                        if p == idx + 1 || p + 1 == idx {
                            continue;
                        } else {
                            ok = false;
                            break;
                        }
                    } else {
                        que.push_back((i, idx + 1));
                    }
                }
            }
        }
        if !ok {
            continue;
        }
        if let Some(tmp) = v.iter().max() {
            result = Some(std::cmp::max(result.unwrap_or(0), tmp.unwrap()));
        }
    }
    println!("{}", result.unwrap_or(-1));
    // println!("{:?}", result);
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
