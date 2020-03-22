use std::collections::HashSet;

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read();
    let k: i32 = sc.read();
    let board: Vec<Vec<char>> = (0..h).map(|_| sc.chars()).collect();
    let mut white: Vec<Vec<i32>> = vec![vec![0; w]; h];
    //white[0][0] = if board[0][0] == '0' { 1 } else { 0 };
    for i in 0..h {
        for j in 0..w {
            let c = if board[i][j] == '1' { 1 } else { 0 };
            let up = if i >= 1 { white[i - 1][j] } else { 0 };
            let left = if j >= 1 { white[i][j - 1] } else { 0 };
            let up_left = if i >= 1 && j >= 1 {
                white[i - 1][j - 1]
            } else {
                0
            };
            white[i][j] = c + up + left - up_left;
        }
    }
    let mut ans = 1 << 30;
    for bit in 0..(1 << h) {
        let mut cuts = vec![];

        for i in 0..h - 1 {
            if (bit >> i) & 1 > 0 {
                cuts.push(i);
            }
        }
        cuts.push(h - 1);
        let mut x_cuts: HashSet<usize> = HashSet::new();
        let mut result = 0;
        let mut pre_x: Option<usize> = None;
        let mut ok = true;
        for x in 0..w {
            let mut pre_y: Option<usize> = None;
            for &y in cuts.iter() {
                let mut sum_white = white[y][x];
                if let Some(pre_y) = pre_y {
                    sum_white -= white[pre_y][x];
                    if let Some(pre_x) = pre_x {
                        sum_white -= white[y][pre_x];
                        sum_white += white[pre_y][pre_x];
                    }
                } else {
                    if let Some(pre_x) = pre_x {
                        sum_white -= white[y][pre_x];
                    }
                }
                pre_y = Some(y);
                //eprintln!("{} {} {}", y, x, sum_white);
                if sum_white > k {
                    if x >= 1 {
                        pre_x = Some(x - 1);
                        x_cuts.insert(x - 1);
                    } else {
                        ok = false;
                    }
                    result += 1;
                    break;
                }
            }
        }
        if ok {
            ans = std::cmp::min(ans, result + cuts.len() - 1);
        }
    }
    println!("{}", ans);
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
