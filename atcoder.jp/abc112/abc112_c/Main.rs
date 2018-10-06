macro_rules! input {
    (source = $s:expr, $($r:tt)*) => {
        let mut iter = $s.split_whitespace();
        let mut next = || { iter.next().unwrap() };
        input_inner!{next, $($r)*}
    };
    ($($r:tt)*) => {
        let stdin = std::io::stdin();
        let mut bytes = std::io::Read::bytes(std::io::BufReader::new(stdin.lock()));
        let mut next = move || -> String{
            bytes
                .by_ref()
                .map(|r|r.unwrap() as char)
                .skip_while(|c|c.is_whitespace())
                .take_while(|c|!c.is_whitespace())
                .collect()
        };
        input_inner!{next, $($r)*}
    };
}

macro_rules! input_inner {
    ($next:expr) => {};
    ($next:expr, ) => {};

    ($next:expr, $var:ident : $t:tt $($r:tt)*) => {
        let $var = read_value!($next, $t);
        input_inner!{$next $($r)*}
    };
}

macro_rules! read_value {
    ($next:expr, ( $($t:tt),* )) => {
        ( $(read_value!($next, $t)),* )
    };

    ($next:expr, [ $t:tt ; $len:expr ]) => {
        (0..$len).map(|_| read_value!($next, $t)).collect::<Vec<_>>()
    };

    ($next:expr, chars) => {
        read_value!($next, String).chars().collect::<Vec<char>>()
    };

    ($next:expr, usize1) => {
        read_value!($next, usize) - 1
    };

    ($next:expr, $t:ty) => {
        $next().parse::<$t>().expect("Parse error")
    };
}

use std::collections::HashSet;

fn main() {
    input! {
        N: i32,
        XYH: [(i32, i32, i32); N],
    }
    for cx in 0..101 {
        for cy in 0..101 {
            let mut values = HashSet::new();
            let mut ok = true;
            for &(x, y, h) in &XYH {
                if h == 0 {
                    continue;
                }
                let rest = -(x - cx).abs() - (y - cy).abs();
                let H = h - rest;
                if H >= 1 {
                    values.insert(H);
                } else {
                    ok = false;
                }
            }
            if ok && values.len() == 1 {
                for value in &values {
                    for &(x, y, h) in &XYH {
                        if h == 0 {
                            let H = value - (x - cx).abs() - (y - cy).abs();
                            if !(H < 0 || H == 0) {
                                ok = false;
                            }
                        }
                    }
                    if ok {
                        println!("{} {} {}", cx, cy, value);
                    }
                }
            }
        }
    }
}
