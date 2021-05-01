use std::io;
use std::io::prelude::*;
use std::io::BufWriter;
use std::fs::File;
use std::time::{Instant};

fn get_input() -> String {
    let mut buffer = String::new();
    io::stdin().read_line(&mut buffer).expect("Failed");
    buffer.replace("\n","")
}
fn write_bytes(buffer: &[u8], filename: &str) -> io::Result<()>{
    let mut writer = BufWriter::new(File::create(filename)?);

    writer.write_all(buffer)?;
    writer.flush()?;
    Ok(())
}

fn main() -> io::Result<()> {
    println!("{:?}", "------  XOR CIPHER  ------\nMODE: 0 cipher - 1 decipher");
    let mode: i8 = get_input().parse().unwrap();


    println!("{:?}", if mode == 0 {"Mode CIPHER: File that is going to be ciphered."} else { "Mode DECIPHER: .key file first please" } );
    let mut f = File::open(get_input())?;

    println!("{:?}", if mode == 0 {"Mode CIPHER: File wished to used as cipher key."} else { "Mode DECIPHER: File used as cipher key" });
    let mut d = File::open(get_input())?;

    let mut buffer = Vec::new();
    let mut object = Vec::new();

    f.read_to_end(&mut buffer)?;
    d.read_to_end(&mut object)?;
    let start = Instant::now();
    for x in 0..buffer.len()-1 {
        buffer[x] = buffer[x] ^ object[x%object.len()];
    }
    let duration = start.elapsed();
    println!("{:?}", "finished");
    println!("{:?}", duration);


    write_bytes(&buffer, if mode == 0 { &"key.key" } else { &"result" });
  

    Ok(())
}