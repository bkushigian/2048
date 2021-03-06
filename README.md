# 2048

Built in C++ using ncurses and boost/regex, this is a work in progress. It runs 2048 via command line.

## Compiling
2048 has two dependencies: Boost and nCurses. If you have both of these libraries installed then compiling is as simple as running

```$ compile.sh```

from the project home directory. I will be upgrading this to a `Makefile` soon.

## Playing 2048

2048 is ultimately meant to be a tool to help me build an AI. As such the default is for the AI to take over. However it is just a 'nominal' AI - it's really pretty terrible. To play as a human run `2048 -p` or `2048 --human`. This will bring you to this screen:

![screenshot1](http://benkushigian.com/misc/img/gh/2048/2048_2.png "Opening Screen")


As you can see, this is very lo-fi. I will be working on the aesthetics at some point but that's not really my focus.

### Moving
The movement keys are just the WASD: W for up, S for down, A for left and D for right.
![WASD](http://benkushigian.com/misc/img/gh/2048/WASD.png "Movement Keys")


## Some options
| Short Form Options | Long Form Options   | Why would I use it?   |
| ------------------ | ------------------- | :-------------------: |
| `-h`               | `--help`            | A basic help menu     |
| `-s [FILE    ]`    | `--store [FILE]`    | Store game in FILE    |
| `-nc`              | `--nocurses`        | Disables nCurses - kinda fucky|
| `-v`               | `--viewgame [FILE]` | Load a stored game for viewing - no play |
| `-n [NUMBER]`      | `--numberofgames [NUMBER]` | Number of games before exit - useful for AI mode |
| `-t [TIME]`        | `--sleeptime [TIME]`| Sleep time between AI moves. |

## The AI
Right now the AI is very simple. It is pretty much: "Can I move up? If so, move up. Else, can I move right? If so move right. Else...". As you can imagine, this is not very strong. I have run batches of 100s of games with scores that I could beat in my sleep. In the future I hope to outdo my own high scores regularly with my AI.

## Moving forward -- what's next?
I'm implementing some methods for analyzing the board - simple statements about qualities of the board. Is it full? Is a row or column full? Where's the highest value? Is it in a corner? Part of this will be formulating the right questions to ask the board. From that I will redesign the current AI class so that it loads a file of perameters and from there evaluating each board position.

I also need to clean up the code and standardize some of my conventions, both naming and programmatic. This has been a piecemeal process over the last 6 months (comprised mainly of big gaps between writing code) so the code is a bit messy. 
