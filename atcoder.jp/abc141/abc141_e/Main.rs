use std::collections::{HashMap, HashSet};
use std::default::Default;
use std::hash::{BuildHasherDefault, Hasher};
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let s: Vec<char> = sc.chars();
    let s = s.as_slice();
    let mut hash_array = Vec::with_capacity(n * n);
    let seq: Vec<u64> = s.iter().map(|&c| c as u64).collect();
    let rh = rolling_hash::RollingHash::new(&seq);

    let mut ok = 0;
    let mut ng = n;
    while ng - ok > 1 {
        // println!("{} {}", ng, ok);
        let length = (ng + ok) / 2;
        for i in 0..(n - length + 1) {
            let hash = rh.hash(i, i + length);
            hash_array.push((hash, (i, i + length - 1)));
        }
        hash_array.sort();
        let mut result = 0;
        let mut i = 0;
        while i < hash_array.len() {
            let hash_value = hash_array[i].0;
            let mut lr = vec![hash_array[i].1];
            let mut j = i + 1;
            while j < hash_array.len() {
                if hash_array[j].0 == hash_value {
                    lr.push(hash_array[j].1);
                } else {
                    break;
                }
                j += 1;
            }
            lr.sort();
            let (mut left, mut right) = lr[0];
            // println!("{:?} {}", lr, hash_value);
            for i in 1..lr.len() {
                let (l, r) = lr[i];
                if right < l || r < left {
                    result = std::cmp::max(result, r - l + 1);
                    break;
                }
                right = std::cmp::min(right, r);
                left = std::cmp::max(left, l);
            }
            i = j;
        }
        if result >= length {
            ok = length;
        } else {
            ng = length;
        }
    }
    println!("{}", ok);
    // for (st, pos) in string_to_pos.iter() {
    //     if pos.is_empty() {
    //         continue;
    //     }
    //     let (mut left, mut right) = pos[0];
    //     for i in 1..pos.len() {
    //         let (l, r) = pos[i];
    //         if right < l || r < left {
    //             result = std::cmp::max(result, r - l + 1);
    //             break;
    //         }
    //         right = std::cmp::min(right, r);
    //         left = std::cmp::max(left, l);
    //     }
    // }
    // println!("{}", result);
}

fn main() {
    std::thread::Builder::new()
        .stack_size(64 * 1024 * 1024) // 64MB
        .spawn(|| solve())
        .unwrap()
        .join()
        .unwrap();
}
pub struct FnvHasher(u64);

impl Default for FnvHasher {
    #[inline]
    fn default() -> FnvHasher {
        FnvHasher(0xcbf29ce484222325)
    }
}

impl FnvHasher {
    /// Create an FNV hasher starting with a state corresponding
    /// to the hash `key`.
    #[inline]
    pub fn with_key(key: u64) -> FnvHasher {
        FnvHasher(key)
    }
}

impl Hasher for FnvHasher {
    #[inline]
    fn finish(&self) -> u64 {
        self.0
    }

    #[inline]
    fn write(&mut self, bytes: &[u8]) {
        let FnvHasher(mut hash) = *self;

        for byte in bytes.iter() {
            hash = hash ^ (*byte as u64);
            hash = hash.wrapping_mul(0x100000001b3);
        }

        *self = FnvHasher(hash);
    }
}

/// A builder for default FNV hashers.
pub type FnvBuildHasher = BuildHasherDefault<FnvHasher>;

/// A `HashMap` using a default FNV hasher.
pub type FnvHashMap<K, V> = HashMap<K, V, FnvBuildHasher>;

/// A `HashSet` using a default FNV hasher.
pub type FnvHashSet<T> = HashSet<T, FnvBuildHasher>;

pub mod rolling_hash {
    const MASK_SIZE: usize = 2;
    static MOD: [u64; MASK_SIZE] = [999999937u64, 1000000007u64];
    const BASE: [u64; MASK_SIZE] = [9973, 10007];
    pub struct RollingHash {
        hash: Vec<Vec<u64>>,
        pow: Vec<Vec<u64>>,
    }

    impl RollingHash {
        pub fn new(s: &[u64]) -> RollingHash {
            let n = s.len();
            let mut hash: Vec<Vec<u64>> = vec![vec![0u64; n + 1]; MASK_SIZE];
            let mut pow: Vec<Vec<u64>> = vec![vec![0u64; n + 1]; MASK_SIZE];
            for i in 0..MASK_SIZE {
                pow[i][0] = 1;
                for j in 0..n {
                    pow[i][j + 1] = pow[i][j] * BASE[i] % MOD[i];
                    hash[i][j + 1] = ((hash[i][j] + s[j]) * BASE[i]) % MOD[i];
                }
            }
            RollingHash {
                hash: hash,
                pow: pow,
            }
        }

        //[l, r)
        pub fn hash1(&self, l: usize, r: usize) -> u64 {
            (self.hash[0][r] + MOD[0] - self.hash[0][l] * self.pow[0][r - l] % MOD[0]) % MOD[0]
        }
        //[l, r)
        pub fn hash2(&self, l: usize, r: usize) -> u64 {
            (self.hash[1][r] + MOD[1] - self.hash[1][l] * self.pow[1][r - l] % MOD[1]) % MOD[1]
        }
        //[l, r)
        pub fn hash(&self, l: usize, r: usize) -> (u64, u64) {
            (self.hash1(l, r), self.hash2(l, r))
        }
        pub fn equal(&self, l1: usize, r1: usize, l2: usize, r2: usize) -> bool {
            self.hash1(l1, r1) == self.hash1(l2, r2) && self.hash2(l1, r1) == self.hash2(l2, r2)
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
