const MAX_V: usize = 51;

fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let a: Vec<usize> = sc.vec(n);
    let b: Vec<usize> = sc.vec(n);
    let mut result = None;
    for bit in 0..(1 << n + 1) {
        let mut colors = vec![(0, 0, 0); n]; //0: read, 1: white
        let mut values = vec![0; n];
        for i in 0..n {
            if ((bit >> i) & 1) == 1 {
                //white
                colors[i] = (b[i], 0, 1);
                values[i] = b[i];
            } else {
                colors[i] = (a[i], 0, 0);
                values[i] = a[i];
            }
        }
        values.sort();
        let mut tmp = a.clone();
        let mut cnt = 0;
        for i in 0..n {
            let mut ok = false;
            let target_value = values[i];
            for j in i..n {
                let (value, current_color, target_color) = colors[j];
                if value == target_value {
                    let required_color = current_color ^ target_color;
                    let color = (j - i) % 2;
                    if required_color != color {
                        continue;
                    }
                    ok = true;
                    let mut k = j;
                    while k > i {
                        //pre
                        let tmp = colors[k - 1];
                        colors[k - 1] = (value, current_color ^ 1, target_color);
                        colors[k] = (tmp.0, tmp.1 ^ 1, tmp.2);
                        k -= 1;
                        cnt += 1;
                    }
                    break;
                }
            }
            if !ok {
                cnt = -1;
                break;
            }
        }
        if cnt >= 0 {
            //            println!("{} {:?}", cnt, colors);
            if result.is_none() {
                result = Some(cnt);
            } else if cnt < result.unwrap() {
                result = Some(cnt);
            }
        }
    }
    println!("{}", result.unwrap_or(-1));
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
