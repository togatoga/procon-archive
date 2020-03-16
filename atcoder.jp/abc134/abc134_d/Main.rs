use std::collections::HashMap;
use std::collections::HashSet;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let a: Vec<u64> = sc.vec(n);
    let mut cnts: HashMap<u64, u64> = HashMap::new();
    let mut results = Vec::new();
    for (idx, x) in a.iter().enumerate().rev() {
        let num = (idx + 1) as u64;
        let cnt = (cnts.get(&num).unwrap_or(&0) + *x) % 2;
        if cnt == 1 {
            results.push(idx);
            let mut y = num;
            let mut div: u64 = 1;
            let mut values = HashSet::new();

            while div * div <= y {
                if y % div == 0 {
                    values.insert(y / div);
                    values.insert(div);
                }
                div += 1;
            }
            //eprintln!("{} {:?}", num, values);
            for value in values.iter() {
                *cnts.entry(*value).or_insert(0) += 1;
            }
        }
    }
    // for (idx, x) in a.iter().enumerate().take(half) {
    //     let num = (idx + 1) as u32;
    //     let cnt = (cnts.get(&num).unwrap_or(&0) + *x) % 2;
    //     if cnt == 1 {}
    // }
    results.sort();
    println!("{}", results.len());
    for x in results.iter() {
        print!("{} ", x + 1);
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
