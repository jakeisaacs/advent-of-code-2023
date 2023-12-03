use std::fs::File;
use std::io::{self, BufRead};
use std::path::Path;
use regex::Regex;
use substring::Substring;

fn main() {
    let re = Regex::new(r"\d\d\s\w+").unwrap();
    let mut sum = 0;
    let mut i = 0;
    let mut gamenum = 0;

    if let Ok(lines) = read_lines("../input.txt") {
        for line in lines {
            if let Ok(l) = line {
                i += 1;
                gamenum = i;
                for cap in re.captures_iter(l.as_str()) {
                    let s = cap.get(0).unwrap().as_str();
                    let n = s.len();

                    let count = s.substring(0,2).parse::<usize>().unwrap();
                    let color = s.substring(3, n);

                    if count > 14 || (count > 12 && color == "red") || (count > 13 && color == "green") || (count > 14 && color == "blue") {
                        gamenum = 0;
                        break;
                    } 
                        
                }
                sum += gamenum;
            }
        }

        println!("Total game sum: {}", sum);
    }

}

fn read_lines<P>(filename: P) -> io::Result<io::Lines<io::BufReader<File>>>
where P: AsRef<Path>, {
    let file = File::open(filename)?;
    Ok(io::BufReader::new(file).lines())
}