const MAX_HWAB: usize = 85;

// fn memo(
//     y: usize,
//     x: usize,
//     sum: usize,
//     dp: &mut Vec<Vec<Vec<Option<bool>>>>,
//     h: usize,
//     w: usize,
//     a: &Vec<Vec<i8>>,
//     b: &Vec<Vec<i8>>,
// ) -> bool {
//     if y == h && x == w {
//         dp[y][x][sum] = Some(true);
//         return true;
//     }
//     if let Some(cache) = dp[y][x][sum] {
//         return cache;
//     }
//     let a_red_sum = (sum as i64 + (a[y][x] - b[y][x]) as i64) as usize;
//     let b_red_sum = (sum as i64 + (-a[y][x] + b[y][x]) as i64) as usize;

//     if y + 1 <= h {
//         memo(y + 1, x, a_red_sum, dp, h, w, a, b);
//         memo(y + 1, x, b_red_sum, dp, h, w, a, b);
//     }
//     if x + 1 <= w {
//         memo(y, x + 1, a_red_sum, dp, h, w, a, b);
//         memo(y, x + 1, b_red_sum, dp, h, w, a, b);
//     }
//     dp[y][x][sum] = Some(true);
//     true
// }

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read();
    let a: Vec<Vec<usize>> = (0..h)
        .map(|_| {
            let a = sc.vec(w);
            a
        })
        .collect();
    let b: Vec<Vec<usize>> = (0..h)
        .map(|_| {
            let b = sc.vec(w);
            b
        })
        .collect();
    // println!("{:?} {:?}", a, b);
    //dp[h][w][sum]
    let mut dp: Vec<Vec<Vec<Option<bool>>>> =
        vec![vec![vec![None; 4 * MAX_HWAB * MAX_HWAB + 10]; MAX_HWAB]; 2];

    let max_sum: usize = 4 * MAX_HWAB * MAX_HWAB;
    let geta: usize = 2 * MAX_HWAB * MAX_HWAB;
    dp[0][0][geta] = Some(true);
    let mut result = 1 << 30;
    for y in 0..h {
        let curr_y = y % 2;
        let next_y = (y + 1) % 2;

        for x in 0..w {
            for sum in 0..max_sum + 1 {
                if dp[curr_y][x][sum].is_none() {
                    continue;
                }
                let a_red_sum = sum + a[y][x] - b[y][x];
                let b_red_sum = sum + b[y][x] - a[y][x];
                // println!("{} {} {} {} {}", y, x, sum, a_red_sum, b_red_sum);
                if y + 1 < h {
                    dp[next_y][x][a_red_sum] = Some(true);
                    dp[next_y][x][b_red_sum] = Some(true);
                }
                if x + 1 < w {
                    dp[curr_y][x + 1][a_red_sum] = Some(true);
                    dp[curr_y][x + 1][b_red_sum] = Some(true);
                }
                if y == h - 1 && x == w - 1 {
                    let tmp1 = if a_red_sum >= geta {
                        a_red_sum - geta
                    } else {
                        geta - a_red_sum
                    };
                    let tmp2 = if b_red_sum >= geta {
                        b_red_sum - geta
                    } else {
                        geta - b_red_sum
                    };

                    result = std::cmp::min(result, tmp1);
                    result = std::cmp::min(result, tmp2);
                }
            }
        }
        for x in 0..w {
            for sum in 0..max_sum + 1 {
                dp[curr_y][x][sum] = None;
            }
        }
    }

    println!("{}", result);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(640 * 1024 * 1024) // 64MB
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
