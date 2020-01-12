use std::collections::VecDeque;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read();
    let s: Vec<Vec<char>> = (0..h)
        .map(|_| {
            let c: Vec<char> = sc.chars();
            c
        })
        .collect();
    let mut result = 0;
    for i in 0..h {
        for j in 0..w {
            let (sy, sx) = (i, j);
            if s[sy][sx] == '#' {
                continue;
            }
            let mut que = VecDeque::new();
            let mut visited = vec![vec![false; 22]; 22];
            que.push_back((sy, sx, 0));
            while let Some(pos) = que.pop_front() {
                let (y, x, cost) = pos;
                if visited[y][x] {
                    continue;
                }
                result = std::cmp::max(result, cost);
                visited[y][x] = true;
                for yy in -1..2 {
                    for xx in -1..2 {
                        let d = ((yy - xx) as i32).abs();
                        let dd = ((yy + xx) as i32).abs();
                        if d >= 2 || dd >= 2 {
                            continue;
                        }
                        let ny = y as i32 + yy;
                        let nx = x as i32 + xx;
                        if ny < 0 || ny >= h as i32 || nx < 0 || nx >= w as i32 {
                            continue;
                        }
                        if s[ny as usize][nx as usize] == '.' {
                            que.push_back((ny as usize, nx as usize, cost + 1));
                        }
                    }
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
