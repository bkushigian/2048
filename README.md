# 2048

Built in C++ using ncurses and boost/regex, this is a work in progress. It runs 2048 via command line.

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

## Moving forward -- what's next?
I'm implementing some methods for analyzing the board - simple statements about qualities of the board. Is it full? Is a row or column full? Where's the highest value? Is it in a corner? Part of this will be formulating the right questions to ask the board. From that I will redesing the current AI class so that it loads a file of perameters and from there evaluating each board position.



