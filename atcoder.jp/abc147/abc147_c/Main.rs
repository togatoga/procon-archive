use std::collections::HashSet;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let inputs: Vec<Vec<(usize, usize)>> = (0..n)
        .map(|_| {
            let a: usize = sc.read();
            (0..a)
                .map(|_| {
                    let x: usize = sc.read();
                    let y: usize = sc.read();
                    (x - 1, y)
                })
                .collect()
        })
        .collect();

    let mut result = None;
    for bit in 0..(1 << n) {
        let mut honests = HashSet::new();
        let mut dishonests = HashSet::new();
        for i in 0..n {
            if (bit >> i) & 1 > 0 {
                honests.insert(i);
            } else {
                dishonests.insert(i);
            }
        }
        let mut ok = true;
        for (idx, testimony) in inputs.iter().enumerate() {
            if honests.contains(&idx) {
                for &(x, y) in testimony.iter() {
                    if y == 1 { //honest
                        if !honests.contains(&x) {
                            ok = false;
                            break;
                        }
                    } else {
                        if !dishonests.contains(&x) {
                            ok = false;
                            break;
                        }
                    }
                }
            }
        }
        if ok {
            result = Some(std::cmp::max(honests.len(), result.unwrap_or(0)));
        }
    }
    println!("{}", result.unwrap_or(0));
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
