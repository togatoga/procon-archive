use std::io::Read;

fn main() {
    let mut buf = String::new();
    std::io::stdin().read_to_string(&mut buf).unwrap();

    let mut iter = buf.split_whitespace();
    let a: usize = iter.next().unwrap().parse().unwrap();
    let b: usize = iter.next().unwrap().parse().unwrap();
    let mut result: usize = a - 1;
        if a <= b {
        result += 1;
    }
    println!("{}", result);
}
