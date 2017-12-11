# Chip8mu: Chip 8 Emulator in C++

Chip8mu is a Chip-8 emulator built in C++. In addition to the standard built in controls, chip8mu also has pause functionality, speed controls, color themes, and a command line debugger with the ability to step through games one cpu cycle at a time.

![pong](https://github.com/zachhannum/chip8mu/blob/master/gifs/pong.gif)

Read more about Chip-8 [here](https://en.wikipedia.org/wiki/CHIP-8).

## How to Play
#### Install SDL
Chip8mu uses SDL to draw graphics to the screen. Follow the instructions [here](http://lazyfoo.net/SDL_tutorials/lesson01/index.php) to download SDL on your computer.

#### Compile
Chip8mu should compile with any standard c++ compiler. Tested on Ubuntu.

`> g++ -o chip8 main.cpp cpu.cpp graphics.cpp -lSDL`

#### Run
`> ./chip8 /roms/name.rom`

Chip8mu takes a command line argument that is the filename of the game you want to play. Included in this repo is pong, 15 puzzle, blinky, space invaders, and ufo.

## Features
#### Color Themes

![themes](https://github.com/zachhannum/chip8mu/blob/master/gifs/themes.gif)

Chip8mu has 5 different color themes to choose from: Default (white on black), Retro, Ubuntu, Cafe, and Inverted.

#### Command Line Debugger

![debugger](https://github.com/zachhannum/chip8mu/blob/master/gifs/debug.gif)

Chip8mu has a real-time command line debugger that displays opcode, cpu registers `V0` through `VF`, contents of the stack, key states, program counter, stack pointer, Index, and timer values. These values are updated in real-time as the program runs. The game can also be paused with `space`, and using `→` chip8mu will cycle through the game one instruction at a time.

## Controls
#### Game controls

    Chip-8 Keypad               Keyboard
      +-+-+-+-+                +-+-+-+-+
      |1|2|3|C|                |1|2|3|4|
      +-+-+-+-+                +-+-+-+-+
      |4|5|6|D|                |Q|W|E|R|
      +-+-+-+-+       =>       +-+-+-+-+
      |7|8|9|E|                |A|S|D|F|
      +-+-+-+-+                +-+-+-+-+
      |A|0|B|F|                |Z|X|C|V|
      +-+-+-+-+                +-+-+-+-+
      
#### Shortcuts

| Shortcut | Function                         |
|----------|----------------------------------|
| `Esc`    | Quit game                        |
| `Space`  | Pause game                       |
| `t`      | Cycle color theme                |
| `p`      | Enable command line debugger     |
| `↑`      | Increase game speed              |
| `↓`      | Decrease game speed              |
| `→`      | Step one cpu cycle (when paused) |

## Chip-8 References
- [Chip-8 Wiki](https://en.wikipedia.org/wiki/CHIP-8)
- [Multigesture Tutorial by Laurence Miller](http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/)
- [Cowgod's Chip-8 Technical Reference v1.0](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Lacy Foo's SDL Tutorials](http://lazyfoo.net/SDL_tutorials/)


