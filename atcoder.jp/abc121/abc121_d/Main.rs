use std::io::Read;

fn f(x: i64) -> i64 {
    if x <= 0 {
        return 0;
    }
    if x == 1 {
        return 1;
    }
    if x == 2 {
        return 3;
    }
    if x == 3 {
        return 0;
    }
    let mut res: i64 = 0;
    let mut y: i64 = x;
    let mut base: i64 = 1;
    while 2 * base <= x {
        base *= 2;
    }

    if (x - base) % 2 == 0 {
        return base ^ f(x - base);
    }
    return f(x - base);
}

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();
    let mut iter = buf.split_whitespace();
    let A: i64 = iter.next().unwrap().parse().unwrap();
    let B: i64 = iter.next().unwrap().parse().unwrap();
    let mut result: i64 = 0;
    result = f(B) ^ f(A - 1);
    println!("{}", result);
}
