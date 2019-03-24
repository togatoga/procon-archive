const MOD: i32 = 1000000007;

fn main() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut dp = vec![vec![vec![vec![0; 4]; 4]; 4]; n + 1];
    //0 -> other
    //1 -> A
    //2 -> G
    //3 -> C
    let p = vec!['T', 'A', 'G', 'C'];
    let agc = "AGC".to_string();
    dp[0][0][0][0] = 1;

    for i in 0..n {
        for j in 0..4 {
            for k in 0..4 {
                for l in 0..4 {
                    if dp[i][j][k][l] == 0 {
                        continue;
                    }
                    for m in 0..4 {
                        let tmp = format!("{}{}{}{}", p[j], p[k], p[l], p[m]);
                        let mut ok = true;
                        if tmp.contains(&agc) {
                            ok = false;
                        }
                        for o in 0..tmp.len() - 1 {
                            let mut tmp1 = tmp.clone().chars().collect::<Vec<char>>();
                            tmp1.swap(o, o + 1);
                            let tmp2: String = tmp1.into_iter().collect();
                            if tmp2.contains(&agc) {
                                ok = false;
                                break;
                            }
                        }

                        if ok {
                            dp[i + 1][k][l][m] += dp[i][j][k][l];
                            dp[i + 1][k][l][m] %= MOD;
                        }
                    }
                }
            }
        }
    }
    let mut res = 0;
    for i in 0..4 {
        for j in 0..4 {
            for k in 0..4 {
                let tmp = format!("{}{}{}", p[i], p[j], p[k]);
                if tmp.contains(&agc) {
                    continue;
                }
                let mut ok = true;
                for o in 0..tmp.len() - 1 {
                    let mut tmp1 = tmp.clone().chars().collect::<Vec<char>>();
                    tmp1.swap(o, o + 1);
                    let tmp2: String = tmp1.into_iter().collect();
                    if tmp2.contains(&agc) {
                        ok = false;
                        break;
                    }
                }
                if ok {
                    res += dp[n][i][j][k];
                    res %= MOD;
                }
            }
        }
    }
    println!("{}", res);
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
















