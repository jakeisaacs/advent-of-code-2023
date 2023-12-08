use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    let mut sum = 0;

    if let Ok(lines) = read_lines("../input.txt") {

        for line in lines {
            if let Ok(ip) = line {
                sum += check_numbers(ip);
            }
        }

        println!("Final sum: {}", sum);
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}

fn check_numbers(s: String) -> i32 {
    let numstrings = vec!["1", "2", "3", "4", "5", "6", "7", "8", "9", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    let n = s.len() as usize;
    let mut l: usize = 0;
    let mut r: usize = 0;
    let mut min: usize = n;
    let mut max: usize = 0;

    for (i, num) in numstrings.iter().enumerate() {
        if let Some(pos) = s.rfind(num) {
            if pos >= max {
                r = i%9+ 1;
                max = pos;
            }
        }
        if let Some(pos) = s.find(num) {
            if pos <= min {
                l = i%9 + 1;
                min = pos;
            }
        }

    }
    
    let sum = (l * 10 + r) as i32;

    sum
}