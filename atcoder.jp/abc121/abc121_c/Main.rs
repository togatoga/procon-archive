use std::io::Read;
use std::cmp;
fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let mut iter = buf.split_whitespace();
    let N: usize = iter.next().unwrap().parse().unwrap();
    let mut M: usize = iter.next().unwrap().parse().unwrap();
    let mut AB: Vec<(usize, usize)> = (0..N).map(|_| {
        (
            iter.next().unwrap().parse().unwrap(),
            iter.next().unwrap().parse().unwrap(),
        )
    }).collect();
    AB.sort_by(|a, b|
        a.0.cmp(&b.0)
    );

    let mut result: i64 = 0;
    for (a, b) in AB {
        if M <= 0 {
            break;
        }
        let cost: i64 = a as i64 * cmp::min(M, b) as i64;
        result += cost;
        M -= cmp::min(M, b);
    }
    println!("{}", result);
}