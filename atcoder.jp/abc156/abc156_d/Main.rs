pub mod mod_int {
    use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign};

    //we may need to change this value
    const MOD: i64 = 1e9 as i64 + 7;

    #[derive(Clone, Copy, Debug)]
    pub struct ModInt<T: Copy + Clone + Add + AddAssign + Mul + MulAssign + Sub + SubAssign>(pub T);

    #[warn(unused_macros)]
    macro_rules! mod_int_impl {
        ($($t:ty)*) => ($(
            impl Add<ModInt<$t>> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn add(self, other: ModInt<$t>) -> ModInt<$t> {
                    self + other.0
                }
            }
            impl Add<$t> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn add(self, rhs: $t) -> ModInt<$t> {
                    let mut tmp = rhs + self.0;
                    if tmp >= self::MOD as $t {
                        tmp = tmp - self::MOD as $t;
                    }
                    ModInt(tmp)
                }
            }
            impl Sub<ModInt<$t>> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn sub(self, rhs: ModInt<$t>) -> ModInt<$t> {
                    self - rhs.0
                }
            }
            impl Sub<$t> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn sub(self, rhs: $t) -> ModInt<$t> {
                    let rhs = if rhs >= self::MOD as $t { rhs % self::MOD as $t} else { rhs };
                    let value = if self.0 < rhs { self.0 + self::MOD as $t} else { self.0 };
                    ModInt(value - rhs)
                }
            }
            impl AddAssign<ModInt<$t>> for ModInt<$t> {
                fn add_assign(&mut self, rhs: ModInt<$t>) {
                    *self = *self + rhs;
                }
            }
            impl AddAssign<$t> for ModInt<$t> {
                fn add_assign(&mut self, rhs: $t) {
                    *self = *self + rhs;
                }
            }
            impl SubAssign<ModInt<$t>> for ModInt<$t> {
                fn sub_assign(&mut self, rhs: ModInt<$t>) {
                    *self = *self - rhs;
                }
            }

            impl SubAssign<$t> for ModInt<$t> {
                fn sub_assign(&mut self, rhs: $t) {
                    *self = *self - rhs;
                }
            }

            impl Div<$t> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn div(self, mut rhs: $t) -> ModInt<$t> {
                    if rhs >= MOD as $t {
                        rhs %= MOD as $t;
                    }
                    self * ModInt(rhs).pow((MOD - 2) as usize)
                }
            }
            impl Div<ModInt<$t>> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn div(self, rhs: ModInt<$t>) -> ModInt<$t> {
                    self / rhs.0
                }
            }
            impl DivAssign<$t> for ModInt<$t> {
                fn div_assign(&mut self, rhs: $t) {
                    *self = *self / rhs
                }
            }
            impl DivAssign<ModInt<$t>> for ModInt<$t> {
                fn div_assign(&mut self, rhs: ModInt<$t>) {
                    *self = *self / rhs
                }
            }

            impl Mul<ModInt<$t>> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn mul(self, rhs: ModInt<$t>) -> ModInt<$t> {
                    self * rhs.0
                }
            }
            impl Mul<$t> for ModInt<$t> {
                type Output = ModInt<$t>;
                fn mul(self, rhs: $t) -> ModInt<$t> {
                    ModInt(self.0 * rhs % self::MOD as $t)
                }
            }
            impl MulAssign<ModInt<$t>> for ModInt<$t> {
                fn mul_assign(&mut self, rhs: ModInt<$t>) {
                    *self = *self * rhs;
                }
            }

            impl MulAssign<$t> for ModInt<$t> {
                fn mul_assign(&mut self, rhs: $t) {
                    *self = *self * rhs;
                }
            }
            impl ModInt<$t> {
                pub fn new(x: $t) -> Self {
                    ModInt(x % self::MOD as $t)
                }
                pub fn pow(self, e: usize) -> ModInt<$t> {
                    let mut result = ModInt::<$t>::new(1);
                    let mut cur = self;
                    let mut e = e;
                    while e > 0 {
                        if e & 1 == 1 {
                            result *= cur;
                        }
                        cur *= cur;
                        e >>= 1;
                    }
                    result
                }
            }
            )*)
    }
    mod_int_impl!(usize i32 i64 u32 u64);
}

#[cfg(test)]
mod test {
    use super::mod_int;
    type ModInt = mod_int::ModInt<usize>;

    #[test]
    fn test_zero() {
        let a = ModInt::new(1_000_000_000);
        let b = ModInt::new(7);
        let c = a + b;

        assert_eq!(c.0, 0);
    }

    #[test]
    fn test_mul() {
        let a = ModInt::new(1000);
        let b = ModInt::new(1234);
        let c = a * b;
        assert_eq!(c.0, 1234000);
    }
    #[test]
    fn test_new() {
        let x = ModInt::new((1e9 as i64 + 7) as usize);
        assert_eq!(x.0, 0);
        let x = ModInt::new((1e9 as i64 + 8) as usize);
        assert_eq!(x.0, 1);
    }

    #[test]
    fn test_pow() {
        let a = ModInt::new(2);
        let b = a.pow(10).0;
        assert_eq!(b, 1024);
    }
}
type ModInt = mod_int::ModInt<usize>;
fn solve() {
    let s = std::io::stdin();
    let mut sc = Scanner { stdin: s.lock() };
    let n: usize = sc.read();
    let a: usize = sc.read();
    let b: usize = sc.read();
    let a1 = n - a;
    let b1 = n - b;
    let mut result = ModInt::new(2).pow(n);
    result -= 1;
    let mut a_sum = ModInt::new(1);
    let mut a_sum_1 = ModInt::new(1);
    for x in 0..a {
        a_sum *= ModInt::new(n - x);
        a_sum_1 *= ModInt::new(a - x);
    }
    let mut b_sum = ModInt::new(1);
    let mut b_sum_1 = ModInt::new(1);
    for x in 0..b {
        b_sum *= ModInt::new(n - x);
        b_sum_1 *= ModInt::new(b - x);
    }
    result -= (a_sum / a_sum_1);
    result -= (b_sum / b_sum_1);
    println!("{}", result.0);
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
