#![feature(ascii_ctype)]

use std::io::{self, Read};

fn get_buffer() -> io::Result<String> {
	/// 

	let mut buffer = String::new();
	let stdin = io::stdin();
	let mut handle = stdin.lock();

	handle.read_to_string(&mut buffer)?;
	Ok(buffer)
}

fn print_buffer(buffer: &str) {
	

	let mut chars = buffer.chars();

	let mut count: u32 = 0;
	for c in chars {
		if c.is_ascii_alphabetic() {
			print!("Yep");
			count += 1;
		} else {
			print!("Nope: {}", c);
			count = 0;
		}
	}
}

fn main() {

    let buffer = get_buffer().unwrap();
    print_buffer(buffer.as_str());

}
