use std::collections::BinaryHeap;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read();
    let board: Vec<Vec<char>> = (0..h).map(|_| sc.chars()).collect();
    let mut que = BinaryHeap::new();
    if board[0][0] == '.' {
        que.push((0, (0, 0), false));
    } else {
        que.push((-1, (0, 0), true));
    }
    
    
    let mut visited = vec![vec![false; w]; h];
    let mut result = 1<<30;
    while let Some(p) = que.pop() {
        let (cost, pos, black) = p;
        let (y, x) = pos;
        if visited[y][x] {
            continue;
        }
        if y == h - 1 && x == w - 1 {
            result = std::cmp::min(result, -cost);
            continue;
        }
        visited[y][x] = true;
        if x + 1 < w {
            if board[y][x + 1] == '.' {
                if black {
                    que.push((cost, (y, x + 1), false));
                } else {
                    que.push((cost, (y, x + 1), false));
                }
            } else {
                if black {
                    que.push((cost, (y, x + 1), true));
                } else {
                    que.push((cost - 1, (y, x + 1), true));
                }
            }
        }
        if y + 1 < h {
            if board[y + 1][x] == '.' {
                if black {
                    que.push((cost, (y + 1, x), false));
                } else {
                    que.push((cost, (y + 1, x), false));
                }
            } else {
                if black {
                    que.push((cost, (y + 1, x), true));
                } else {
                    que.push((cost - 1, (y + 1, x), true));
                }
            }
        }
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
