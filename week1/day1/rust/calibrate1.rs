use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;

fn main() {
    let mut start: i32;
    let mut end: i32;
    let mut sum = 0;

    if let Ok(lines) = read_lines("../input.txt") {

        for line in lines {
            start = -1;
            end = -1;
            if let Ok(ip) = line {
                for c in ip.chars() {
                    let tmp = c as i32 - 0x30;
                    if tmp >= 0 && tmp < 10 {
                        if start < 0 {
                            start = tmp;
                            end = tmp;
                        } else {
                            end = tmp;
                        }
                    }
                }
            }
            sum += start * 10 + end;
        }

        println!("Final sum: {}", sum);
    }
}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}