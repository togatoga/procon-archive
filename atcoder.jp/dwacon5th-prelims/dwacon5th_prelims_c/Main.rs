use std::collections::VecDeque;

fn dmc(k: usize, s: &[char]) -> usize {
    let mut m_cnt = vec![0; s.len() + 1];
    {
        let mut m = 0;
        for (idx, &x) in s.iter().enumerate().rev() {
            if x == 'D' {
                m_cnt[idx] = m;
                m = 0;
            }
            if x == 'M' {
                m += 1;
            }
        }
    }

    let mut d: VecDeque<(usize, usize)> = VecDeque::new();
    let mut cnt = 0;
    let mut m_sum = 0;
    let mut m = 0;
    let mut result = 0;
    for (idx, &x) in s.iter().enumerate() {
        while let Some(&y) = d.front() {
            let diff = idx - y.0;
            if diff >= k {
                //    println!("{} {}", cnt, m_sum);
                cnt -= m_sum;
                m_sum -= m_cnt[y.0];
                d.pop_front();
            } else {
                break;
            }
        }
        if x == 'D' {
            d.push_back((idx, m_cnt[idx]));
            cnt += d.len() * m_cnt[idx];
            m_sum += m_cnt[idx];
            m = 0;
        }
        if x == 'M' {
            m += 1;
        }
        if x == 'C' {
            if d.len() > 0 {
                let c = d.back().unwrap();
                if c.1 != m {
                    let mut tmp = cnt - d.len() * c.1;
                    tmp += d.len() * m;
                    result += tmp;
                } else {
                    result += cnt;
                }
            } else {
                result += cnt;
            }
        }
    }
    result
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let s = sc.chars();
    let q: usize = sc.read();
    let results: Vec<usize> = (0..q)
        .map(|_| {
            let k: usize = sc.read();
            dmc(k, &s)
        })
        .collect();
    for result in results {
        println!("{}", result);
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
