use std::io;


fn main() {
    let a : u32 = get_line().parse().unwrap();
    let d1 = a / 10;
    let d2 = a % 10;
    if d1 == 9 || d2 == 9 {
        println!("Yes");
    }else{
        println!("No");
    }
}

fn get_line() -> String {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    return String::from(line.trim())
}
