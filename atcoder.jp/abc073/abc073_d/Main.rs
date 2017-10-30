use std::io;
use std::mem;
use std::cmp::{min};
 
const N: usize = 201;
const INF: i32 = 536870912;
 
fn main() {
    let mut cost = [[INF; N]; N];
    let mut cost = [[INF; 1 << 9]; N];
    let nmr: Vec<i32> = get_line()
        .split(' ')
        .map(|x| x.trim().parse().unwrap())
        .collect();
    let n: i32 = nmr[0];
    let m: i32 = nmr[1];
    let r: i32 = nmr[2];
 
    let mut R: Vec<i32> = get_line()
        .split(' ')
        .map(|x| x.trim().parse().unwrap())
        .collect();
 
    for i in 0..m {
        let mut abc: Vec<usize> = get_line()
            .split(' ')
            .map(|x| x.trim().parse().unwrap())
            .collect();
        abc[0] -= 1;
        abc[1] -= 1;
        cost[abc[0]][abc[1]] = abc[2] as i32;
        cost[abc[1]][abc[0]] = abc[2] as i32;
    }
 
    for i in 0..n {
        cost[i as usize][i as usize] = 0;
    }
    for k in 0..n {
        for i in 0..n {
            for j in 0..n {
                cost[i as usize][j as usize] = min(cost[i as usize][j as usize], cost[i as usize][k as usize] + cost[k as usize][j as usize]);
            }
        }
    }
 
    let mut res = INF;
 
    R.sort();
    let mut permutations = Vec::new();
    while R.next_permutation(){
        permutations.push(R.to_vec());
    }
 
    for perm in permutations {
        let mut tmp = 0;
        let mut pos = perm[0] -1;
        for x in &perm {
            // println!("{}", x);
            let y : usize = (x - 1) as usize;
            tmp += cost[pos as usize][y as usize];
            pos = x - 1;
        }
        // println!("tmp = {}", tmp);
        res = min(res, tmp);
    }
    println!("{}", res);
}
 
 
/// Permute a slice into its next or previous permutation (in lexical order).
///
/// ```
/// use permutohedron::LexicalPermutation;
///
/// let mut data = [1, 2, 3];
/// let mut permutations = Vec::new();
///
/// loop {
///     permutations.push(data.to_vec());
///     if !data.next_permutation() {
///         break;
///     }
/// }
///
/// assert_eq!(permutations, &[&[1, 2, 3], &[1, 3, 2],
///                            &[2, 1, 3], &[2, 3, 1],
///                            &[3, 1, 2], &[3, 2, 1]]);
///
/// // `data` has been mutated in-place:
/// assert_eq!(data, [3, 2, 1]);
/// ```
pub trait LexicalPermutation {
    /// Return `true` if the slice was permuted, `false` if it is already
    /// at the last ordered permutation.
    fn next_permutation(&mut self) -> bool;
    /// Return `true` if the slice was permuted, `false` if it is already
    /// at the first ordered permutation.
    fn prev_permutation(&mut self) -> bool;
}
 
impl<T> LexicalPermutation for [T] where T: Ord {
    /// Original author in Rust: Thomas Backman <serenity@exscape.org>
    fn next_permutation(&mut self) -> bool {
        // These cases only have 1 permutation each, so we can't do anything.
        if self.len() < 2 { return false; }
 
        // Step 1: Identify the longest, rightmost weakly decreasing part of the vector
        let mut i = self.len() - 1;
        while i > 0 && self[i-1] >= self[i] {
            i -= 1;
        }
 
        // If that is the entire vector, this is the last-ordered permutation.
        if i == 0 {
            return false;
        }
 
        // Step 2: Find the rightmost element larger than the pivot (i-1)
        let mut j = self.len() - 1;
        while j >= i && self[j] <= self[i-1]  {
            j -= 1;
        }
 
        // Step 3: Swap that element with the pivot
        self.swap(j, i-1);
 
        // Step 4: Reverse the (previously) weakly decreasing part
        self[i..].reverse();
 
        true
    }
 
    fn prev_permutation(&mut self) -> bool {
        // These cases only have 1 permutation each, so we can't do anything.
        if self.len() < 2 { return false; }
 
        // Step 1: Identify the longest, rightmost weakly increasing part of the vector
        let mut i = self.len() - 1;
        while i > 0 && self[i-1] <= self[i] {
            i -= 1;
        }
 
        // If that is the entire vector, this is the first-ordered permutation.
        if i == 0 {
            return false;
        }
 
        // Step 2: Reverse the weakly increasing part
        self[i..].reverse();
 
        // Step 3: Find the rightmost element equal to or bigger than the pivot (i-1)
        let mut j = self.len() - 1;
        while j >= i && self[j-1] < self[i-1]  {
            j -= 1;
        }
 
        // Step 4: Swap that element with the pivot
        self.swap(i-1, j);
 
        true
    }
 
}
 
fn get_line() -> String {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    return String::from(line.trim());
}