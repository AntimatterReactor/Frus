## Frus

Frus is a brainfuck interpreter built in c,
it's designed to have max compatibility
by being able to be compiled with c89 standard.

It's also designed to use the minimum amount of space.

### How to Build

1. Acquire a C/C++ compiler.
2. Compile `frus.c`. E.g `gcc frus.c -o frus`

#### Tip

- Use `-O3` for faster performance and smaller file size

### Usage

Target a brainfuck using the compiled `frus.c` binary.
E.g `./frus source.bf`

NOTE: frus DOES NOT support debugging
