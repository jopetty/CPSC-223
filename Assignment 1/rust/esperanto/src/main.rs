use std::io::{self, Read};

const LONG_ENDING: &'static str = "o";
const SHORT_ENDING: &'static str = "an";

/// Returns a buffer from standard in
fn get_buffer() -> io::Result<String> {

	let mut buffer = String::new();
	let stdin = io::stdin();
	let mut handle = stdin.lock();

	handle.read_to_string(&mut buffer)?;
	Ok(buffer)
}

/// Conditionally prints out characters in buffer
fn print_buffer(buffer: &str) {
	
	let mut count: u32 = 0;
	let mut first_char: Option<char> = None;

	for c in buffer.chars() {
		if c.is_alphabetic() {
			match count {
				0 => first_char = Some(c),
				1 => {
					match first_char.unwrap().is_lowercase() {
						true => print!("{}", c.to_lowercase().collect::<String>()),
						false => print!("{}", c.to_uppercase().collect::<String>()),
					}
				},
				_ => print!("{}", c)
			}
		} else {
			match first_char {
				Some(f) => {
					match count {
						1 => {
							print!("{}", f);
							print!("{}", SHORT_ENDING);
						},
						_ => {
							print!("{}", first_char.unwrap().to_lowercase().collect::<String>());
							match count {
								2 | 3 => print!("{}", SHORT_ENDING),
								_=> 	 print!("{}", LONG_ENDING),
							}
						},
					}
					first_char = None;
				},
				None => {},
			}
			print!("{}", c);
		}
		match first_char {
			Some(_) => count += 1,
			None => count = 0,
		}
	}
}

fn main() {

    let buffer = get_buffer().unwrap();
    print_buffer(buffer.as_str());

}
