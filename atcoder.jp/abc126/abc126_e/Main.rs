fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n = sc.read::<usize>();
    let m = sc.read::<usize>();
    let mut ut = UnionFind::new(n);
    let queries: Vec<(usize, usize, usize)> = (0..m).map(|_| {
        let x: usize = sc.read();
        let y: usize = sc.read();
        let z = sc.read();
        ut.unite(x - 1, y - 1);
        (x - 1, y - 1, z)
    }).collect();
    let mut cnt = 0;
    for i in 0..n {
        if ut.is_root(i) {
            cnt += 1;
        }
    }
    println!("{}", cnt);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve())
        .unwrap()
        .join()
        .unwrap();
}

pub struct UnionFind {
    parent: Vec<i32>,
    size: usize,
}

impl UnionFind {
    pub fn new(size: usize) -> UnionFind {
        let parent = vec![-1; size];
        UnionFind {
            parent: parent,
            size: size,
        }
    }
    pub fn unite(&mut self, x: usize, y: usize) {
        let x_root = self.root(x);
        let y_root = self.root(y);
        //different set
        if x_root != y_root {
            let size1 = self.parent[x_root];
            let size2 = self.parent[y_root];
            //merge smaller one for bigger one
            if size1 >= size2 {
                self.parent[x_root] += size2;
                //new parent
                self.parent[y_root] = x_root as i32;
            } else {
                self.parent[y_root] += size1;
                //new parent
                self.parent[x_root] = y_root as i32;
            }
            self.size -= 1;
        }
    }
    pub fn is_root(&mut self, x: usize) -> bool {
        return self.root(x) == x;
    }
    pub fn is_same_set(&mut self, x: usize, y: usize) -> bool {
        return self.root(x) == self.root(y);
    }
    pub fn root(&mut self, x: usize) -> usize {
        //x doesn't have a parent. x is the root
        if self.parent[x] < 0 {
            return x;
        }
        let parent = self.parent[x] as usize;
        let root = self.root(parent);
        self.parent[x] = root as i32;
        return root;
    }
    pub fn set_size(&mut self, x: usize) -> usize {
        let root = self.root(x);
        let set_size = -1 * self.parent[root];
        return set_size as usize;
    }
    pub fn size(&self) -> usize {
        return self.size;
    }
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
