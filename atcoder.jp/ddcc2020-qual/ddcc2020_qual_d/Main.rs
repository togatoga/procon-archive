use std::collections::VecDeque;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let m: usize = sc.read();
    let dc: Vec<(usize, usize)> = (0..m)
        .map(|_| {
            let d: usize = sc.read();
            let c: usize = sc.read();
            (d, c)
        })
        .collect();
    let mut que: VecDeque<(usize, usize)> = VecDeque::from(dc);

    let mut values = vec![vec![(0, 0); 10]; 10];
    for i in 0..10 {
        for j in 0..10 {
            let mut tmp = i + j;
            let mut cnt = 1;
            while tmp >= 10 {
                let y1 = 1;
                let y2 = tmp - 10;
                tmp = y1 + y2;
                cnt += 1;
            }
            values[i][j] = (tmp, cnt);
        }
    }
    let mut result = 0;
    let mut remains = VecDeque::new();
    while let Some(value) = que.pop_front() {
        let (d, c) = value;
        if c == 1 {
            remains.push_back(d);
            continue;
        }
        if c % 2 == 0 {
            let (d1, cnt) = values[d][d];
            result += cnt * (c / 2);
            que.push_front((d1, c / 2));
        } else {
            let (d1, cnt) = values[d][d];
            result += cnt * (c / 2);
            que.push_front((d, 1));
            que.push_front((d1, c / 2));
        }
    }
    loop {
        if remains.len() <= 1 {
            break;
        }
        let x1 = remains.pop_front().unwrap();
        let x2 = remains.pop_front().unwrap();
        if x1 + x2 >= 10 {
            let y1 = 1;
            let y2 = x1 + x2 - 10;
            result += 1;
            remains.push_front(y2);
            remains.push_front(y1);
        } else {
            result += 1;
            remains.push_front(x1 + x2);
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
