fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let h: usize = sc.read();
    let w: usize = sc.read();
    let s: Vec<Vec<char>> = (0..h).map(|_| sc.chars()).collect();
    let mut ut = UnionFind::new(h * w);
    for i in 0..h {
        for j in 0..w {
            if s[i][j] == '#' {
                for k in 0..4 {
                    if let Some((ny, nx)) = utils::try_adj(i, j, k, h, w) {
                        if s[ny][nx] == '.' {
                            ut.unite(i * w + j, ny * w + nx);
                        }
                    }
                }
            }
        }
    }
    let mut cnts: Vec<(usize, usize)> = vec![(0, 0); h * w];
    for i in 0..h {
        for j in 0..w {
            let root = ut.root(i * w + j);
            if s[i][j] == '#' {
                cnts[root].0 += 1;
            } else {
                cnts[root].1 += 1;
            }
        }
    }
    let mut result = 0;
    for i in 0..h {
        for j in 0..w {
            if ut.is_root(i * w + j) {
                result += cnts[i * w + j].0 * cnts[i * w + j].1;
            }
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

pub mod utils {

    const DYX: [(isize, isize); 8] = [
        (0, 1),   //right
        (1, 0),   //top
        (0, -1),  //left
        (-1, 0),  //down
        (1, 1),   //top right
        (-1, 1),  //down right
        (1, -1),  //top left
        (-1, -1), //down left
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
