fn print(results: &[(i64, i64)]) {
    println!(
        "{}",
        results[results.len() - 1].0 - results[results.len() - 1].1
    );
    for &(x, y) in results.iter() {
        println!("{} {}", x, y);
    }
}
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let mut a: Vec<i64> = sc.vec(n);
    a.sort();
    if n == 2 {
        if a[0] - a[1] > a[1] - a[0] {
            println!("{}", a[0] - a[1]);
            println!("{} {}", a[0], a[1]);
        } else {
            println!("{}", a[1] - a[0]);
            println!("{} {}", a[1], a[0]);
        }
        return;
    }

    let mut results = vec![];
    if a[0] <= 0 && a[n - 1] <= 0 {
        results.push((a[n - 1], a[0]));
        let mut sum = a[n - 1] - a[0];
        for i in 1..n - 1 {
            results.push((sum, a[i]));
            sum -= a[i];
        }
        print(&results);
        return;
    }
    if a[0] <= 0 && a[n - 1] >= 0 {
        let mut sum = a[0];
        for i in (0..n - 1).rev() {
            if a[i] <= 0 {
                break;
            }
            results.push((sum, a[i]));
            sum -= a[i];
        }
        let mut sum1 = a[n - 1];
        for i in 1..n - 1 {
            if a[i] >= 0 {
                break;
            }
            results.push((sum1, a[i]));
            sum1 -= a[i];
        }
        results.push((sum1, sum));
        while results.len() < n - 1 {
            results.push((sum1 - sum, 0));
        }
        print(&results);
        return;
    }
    if a[0] >= 0 && a[n - 1] >= 0 {
        let mut sum = a[0];
        for i in 1..n - 1 {
            results.push((sum, a[i]));
            sum -= a[i];
        }
        results.push((a[n - 1], sum));
        print(&results);
        return;
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
