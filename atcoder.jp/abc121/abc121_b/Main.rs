use std::io::Read;

fn main() {
    let mut buf = String::new();


    std::io::stdin().read_to_string(&mut buf).unwrap();


    let mut iter = buf.split_whitespace();

    let N: i32 = iter.next().unwrap().parse().unwrap();
    let M: i32 = iter.next().unwrap().parse().unwrap();
    let C: i32 = iter.next().unwrap().parse().unwrap();

    let B: Vec<i32> = (0..M).map(|_| { iter.next().unwrap().parse().unwrap() }).collect();
    let A: Vec<Vec<i32>> = (0..N).map(|_| {
        (0..M).map(|_| { iter.next().unwrap().parse().unwrap() }).collect()
    }).collect();
    let mut result = 0;
    for i in 0..N {
        let mut sum = 0;
        for j in 0..M {
            sum += A[i as usize][j as usize] * B[j as usize];
        }
        sum += C;
        if sum > 0 {
            result += 1;
        }
    }
    println!("{}", result);
}