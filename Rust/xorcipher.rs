/*
MIT License

Copyright (c) 2021 guen-ynk

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/
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
   
    buffer = buffer.iter().zip(object.iter().cycle()).map(|(x,y)| *x ^ *y).collect();

    let duration = start.elapsed();

    println!("{:?}", "finished");
    println!("{:?}", duration);


    write_bytes(&buffer, if mode == 0 { &"key.key" } else { &"result" });
    buffer.flush();


    Ok(())
}