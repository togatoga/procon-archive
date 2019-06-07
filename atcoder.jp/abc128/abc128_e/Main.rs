use std::cmp::Ordering;

#[derive(Eq, PartialEq, Clone, Debug)]
pub struct Rev<T>(pub T);

impl<T: PartialOrd> PartialOrd for Rev<T> {
    fn partial_cmp(&self, other: &Rev<T>) -> Option<Ordering> {
        other.0.partial_cmp(&self.0)
    }
}

impl<T: Ord> Ord for Rev<T> {
    fn cmp(&self, other: &Rev<T>) -> Ordering {
        other.0.cmp(&self.0)
    }
}
fn is_left(position: i64, s: i64, x: i64) -> bool {
    if position + s <= x {
        true
    } else {
        false
    }
}
fn is_right(position: i64, t: i64, x: i64) -> bool {
    if position + t > x {
        true
    } else {
        false
    }
}
const INF: i32 = 1000000000;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let q: usize = sc.read();
    let mut obstacles: Vec<(i64, i64, i64)> = (0..n)
        .map(|_| {
            let s: i64 = sc.read();
            let t: i64 = sc.read();
            let x: i64 = sc.read();
            (s, t, x)
        })
        .collect();
    obstacles.sort_by(|a, b| a.2.cmp(&b.2));

    let walkers: Vec<i64> = (0..q)
        .map(|_| {
            let d: i64 = sc.read();
            -d
        })
        .collect();
    let mut answers = vec![INF; q];
    let mut left_values = vec![vec![]; q];
    let mut right_values = vec![vec![]; q];
    for &obstacle in obstacles.iter() {
        let s = obstacle.0;
        let t = obstacle.1;
        let x = obstacle.2;
        let mut left_value = None;
        let mut right_value = None;
        //left
        {
            let mut left = -1;
            let mut right = (q + 1) as i32;
            while right - left > 1 {
                let med = (right + left) / 2;
                if med < 0 {
                    left = med;
                    continue;
                }
                if med >= q as i32 {
                    right = med;
                    continue;
                }
                let med = med as usize;
                if is_left(walkers[med], s, x) {
                    right = med as i32;
                    right_value = Some(med);
                } else {
                    left = med as i32;
                }
            }
        }
        //right
        {
            let mut left = -1;
            let mut right = (q + 1) as i32;
            while right - left > 1 {
                let med = (right + left) / 2;
                if med < 0 {
                    left = med;
                    continue;
                }
                if med >= q as i32 {
                    right = med;
                    continue;
                }
                let med = med as usize;

                if is_right(walkers[med], t, x) {
                    left = med as i32;
                    left_value = Some(med);
                } else {
                    right = med as i32;
                }
            }
        }

        if left_value.is_none() || right_value.is_none() {
            continue;
        }

        let left_value = left_value.unwrap();
        let right_value = right_value.unwrap();
        left_values[left_value].push(x);
        right_values[right_value].push(x);
    }
    let mut heap: std::collections::BinaryHeap<Rev<i64>> = vec![].into_iter().map(Rev).collect();
    let mut degrees: std::collections::HashMap<i64, i32> = std::collections::HashMap::new();
    for i in 0..q {
        while let Some(value) = right_values[i].pop() {
            heap.push(Rev(value));
            *degrees.entry(value).or_insert(0) += 1;
        }
        while let Some(&Rev(value)) = heap.peek() {
            if *degrees.get(&value).unwrap() > 0 {
                break;
            } else {
                heap.pop();
            }
        }
        if let Some(&Rev(val)) = heap.peek() {
            assert!(*degrees.get(&val).unwrap() > 0);
            answers[i] = std::cmp::min(answers[i], val as i32);
        }

        while let Some(value) = left_values[i].pop() {
            *degrees.entry(value).or_insert(0) -= 1;
        }

        //pop
        while let Some(&Rev(value)) = heap.peek() {
            if *degrees.get(&value).unwrap() > 0 {
                break;
            } else {
                heap.pop();
            }
        }
        // println!("");
    }

    for ans in answers {
        let ans = if ans == INF { -1 } else { ans };
        println!("{}", ans);
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
