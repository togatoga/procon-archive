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
    pub fn union_size(&mut self, x: usize) -> usize {
        let root = self.root(x);
        let set_size = -1 * self.parent[root];
        return set_size as usize;
    }
    pub fn size(&self) -> usize {
        return self.size;
    }
}
use std::collections::HashSet;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let m: usize = sc.read();
    let k: usize = sc.read();
    let mut friends: Vec<HashSet<usize>> = (0..n).map(|_| HashSet::new()).collect();
    let mut blocks: Vec<HashSet<usize>> = (0..n).map(|_| HashSet::new()).collect();
    let mut edges: Vec<Vec<(usize, bool)>> = (0..n).map(|_| vec![]).collect();
    let mut ut = UnionFind::new(n);
    for _ in 0..m {
        let a: usize = sc.read();
        let b: usize = sc.read();
        friends[a - 1].insert(b - 1);
        friends[b - 1].insert(a - 1);
        edges[a - 1].push((b - 1, true));
        edges[b - 1].push((a - 1, true));
        ut.unite(a - 1, b - 1);
    }
    for _ in 0..k {
        let a: usize = sc.read();
        let b: usize = sc.read();
        blocks[a - 1].insert(b - 1);
        blocks[b - 1].insert(a - 1);
        edges[a - 1].push((b - 1, false));
        edges[b - 1].push((a - 1, false));
    }

    for i in 0..n {
        let mut result = ut.union_size(i) - 1;
        for &(x, friend) in edges[i].iter() {
            if friend {
                result -= 1;
            } else {
                //block
                if ut.is_same_set(x, i) {
                    result -= 1;
                }
            }
        }
        print!("{} ", result);
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
