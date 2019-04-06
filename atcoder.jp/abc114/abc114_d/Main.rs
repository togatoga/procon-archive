fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut degs = vec![0; 101];
    for i in 2..n + 1 {
        let mut div = 2;
        let mut tmp = i;
        while div * div <= tmp {
            while tmp % div == 0 {
                tmp /= div;
                degs[div] += 1;
            }
            div += 1;
        }
        if tmp != 1 {
            degs[tmp] += 1;
        }
    }

    let degs: Vec<i32> = degs.iter().filter(|&&x| x > 0).cloned().collect();
    let m = degs.len();
    
    let mut result = 0;
    //355
    for i in 0..m {
        for j in i + 1..m {
            for k in j + 1..m {
                let a = degs[i];
                let b = degs[j];
                let c = degs[k];
                let mut tmp = vec![a, b, c];
                tmp.sort();
                //355
                if tmp[0] >= 2 && tmp[1] >= 4 && tmp[2] >= 4 {
                    result += 1;
                }
                if tmp[0] >= 4 && tmp[1] >= 2 && tmp[2] >= 4 {
                    result += 1;
                }
                if tmp[0] >= 4 && tmp[1] >= 4 && tmp[2] >= 2 {
                    result += 1;
                }
            }
        }
    }
    //5 x 15
    for i in 0..m {
        for j in i + 1..m {
            let a = degs[i];
            let b = degs[j];
            let mut tmp = vec![a, b];
            tmp.sort();
            //5 x 15
            if tmp[0] >= 4 && tmp[1] >= 14 {
                result += 1;
            }
            if tmp[1] >= 4 && tmp[0] >= 14 {
                result += 1;
            }
        }
    }
    //25 x 3
    for i in 0..m {
        for j in i + 1..m {
            let a = degs[i];
            let b = degs[j];
            let mut tmp = vec![a, b];
            tmp.sort();
            //3 x 25
            if tmp[0] >= 2 && tmp[1] >= 24 {
                result += 1;
            }
            if tmp[1] >= 2 && tmp[0] >= 24 {
                result += 1;
            }
        }
    }
    for i in 0..m {
        if degs[i] >= 74 {
            result += 1;
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
        let buf = self.stdin
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
        let buf = self.stdin
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
