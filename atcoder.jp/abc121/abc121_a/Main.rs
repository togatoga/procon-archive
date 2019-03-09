use std::io::Read;

fn main() {
    let mut buf = String::new();

    std::io::stdin().read_to_string(&mut buf).unwrap();


    let mut iter = buf.split_whitespace();

    let H: usize = iter.next().unwrap().parse().unwrap();
    let W: usize = iter.next().unwrap().parse().unwrap();
    let h: usize = iter.next().unwrap().parse().unwrap();
    let w: usize = iter.next().unwrap().parse().unwrap();
    let res = (H - h) * (W - w);
    println!("{}", res);
}