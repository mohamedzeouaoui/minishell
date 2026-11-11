<h1 align="center">minishell</h1>

<p align="center">
  <em>As beautiful as a shell.</em><br>
  A minimal Bash-like shell written in C as part of the 42 curriculum.
</p>

<p align="center">
  <img alt="Language" src="https://img.shields.io/badge/language-C-blue">
  <img alt="Norm" src="https://img.shields.io/badge/norminette-passing-brightgreen">
  <img alt="42" src="https://img.shields.io/badge/school-42-black">
  <img alt="Score" src="https://img.shields.io/badge/score-101%2F100-success">
</p>

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Built-in Commands](#built-in-commands)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Project Structure](#project-structure)
- [How It Works](#how-it-works)
- [Signals](#signals)
- [Testing](#testing)
- [Allowed Functions](#allowed-functions)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)

---

## About

**minishell** is a simplified UNIX shell that reproduces the core behavior of Bash. The goal of the project is to learn about processes, file descriptors, pipes, signals, and parsing by building an interactive command interpreter from scratch.

The shell reads a line of input, parses it into tokens and commands, expands variables, sets up redirections and pipes, and executes the result, all while handling signals and keeping track of the exit status like a real shell.

## Features

- Interactive prompt with **command history** (via `readline`)
- Execution of commands found through `PATH`, or via relative/absolute paths
- **Quote handling**
  - `'single quotes'` prevent all interpretation of enclosed characters
  - `"double quotes"` prevent interpretation except for `$`
- **Environment variable expansion** (`$VAR`)
- **Exit status expansion** (`$?`)
- **Redirections**
  - `<` redirect input
  - `>` redirect output
  - `>>` redirect output in append mode
  - `<<` heredoc (reads input until a delimiter is found)
- **Pipes** (`|`) connecting the output of one command to the input of the next
- **Signal handling** for `Ctrl-C`, `Ctrl-D` and `Ctrl-\`
- Seven **built-in commands** implemented from scratch

## Built-in Commands

| Command  | Description                                         |
|----------|-----------------------------------------------------|
| `echo`   | Print arguments, supports the `-n` option           |
| `cd`     | Change the current directory (relative or absolute) |
| `pwd`    | Print the current working directory                 |
| `export` | Set or display environment variables                |
| `unset`  | Remove environment variables                        |
| `env`    | Print the environment                               |
| `exit`   | Exit the shell with an optional status code         |

## Installation

### Requirements

- A UNIX-like system (Linux or macOS)
- `gcc` or `cc`
- `make`
- GNU `readline` library

On Debian/Ubuntu:

```bash
sudo apt-get install build-essential libreadline-dev
```

On macOS (Homebrew):

```bash
brew install readline
```

### Build

```bash
git clone https://github.com/mohamedzeouaoui/minishell.git
cd minishell
make
```

### Makefile rules

| Rule        | Description                                |
|-------------|--------------------------------------------|
| `make`      | Compile the project                        |
| `make clean`  | Remove object files                      |
| `make fclean` | Remove object files and the executable   |
| `make re`     | Recompile from scratch                   |

## Usage

Launch the shell:

```bash
./minishell
```

You will get an interactive prompt where you can type commands just like in Bash:

```text
minishell$ echo "Hello, 42!"
Hello, 42!
minishell$ exit
```

## Examples

```bash
# Simple commands
minishell$ ls -la
minishell$ /bin/echo hello

# Variables and exit status
minishell$ export NAME=42
minishell$ echo "Hello $NAME"
Hello 42
minishell$ ls /nonexistent
minishell$ echo $?
2

# Pipes
minishell$ cat file.txt | grep "42" | wc -l

# Redirections
minishell$ echo "hello" > out.txt
minishell$ echo "world" >> out.txt
minishell$ cat < out.txt
hello
world

# Heredoc
minishell$ cat << EOF
> first line
> second line
> EOF
first line
second line

# Quotes
minishell$ echo '$HOME'
$HOME
minishell$ echo "$HOME"
/home/user
```

## Project Structure

```text
minishell/
├── .gitignore
├── Makefile
├── README.md
├── main.c                # Entry point and main loop
├── minishell.h           # Structures, prototypes and macros
├── env/                  # Environment management (copy, get, set, unset)
├── execution/            # Command execution, pipes, redirections, built-ins
├── heredoc/              # Heredoc handling (<<)
├── parsing/              # Lexer, syntax checks, expansion, command building
└── utils/                # Helper functions and memory management
```

## How It Works

1. **Read**: `readline()` displays the prompt and fetches the user's input, which is added to the history.
2. **Lex**: the input is split into tokens (words, operators, quotes).
3. **Parse**: tokens are checked for syntax errors and organized into a list of commands with their arguments and redirections.
4. **Expand**: environment variables, `$?` and quotes are processed.
5. **Execute**:
   - Built-ins run in the parent process when alone (so `cd`, `export`, `unset` and `exit` affect the shell itself).
   - Other commands are launched with `fork()` and `execve()`.
   - Pipes are created with `pipe()` and file descriptors are rewired with `dup2()`.
6. **Wait**: the shell collects exit statuses with `waitpid()` and stores the last one in `$?`.

## Signals

| Key      | In interactive mode        | While a command runs   | In heredoc            |
|----------|----------------------------|------------------------|-----------------------|
| `Ctrl-C` | New prompt on a new line   | Interrupts the command | Cancels the heredoc   |
| `Ctrl-D` | Exits the shell            | Sends EOF              | Ends the heredoc      |
| `Ctrl-\` | Does nothing               | Quits the command      | Does nothing          |

Only one global variable is used, and only to store the received signal number.

## Testing

Compare your shell's behavior against Bash:

```bash
# Check for memory leaks (readline leaks are expected and can be suppressed)
valgrind --leak-check=full --show-leak-kinds=all \
  --suppressions=readline.supp ./minishell
```

Some useful community testers:

- [minishell_tester](https://github.com/LucasKuhn/minishell_tester)
- [42_minishell_tester](https://github.com/zstenger93/42_minishell_tester)

Edge cases worth testing:

- Unclosed quotes
- Empty commands and lines with only spaces
- Multiple consecutive pipes or redirections
- Missing files and permission errors
- Unset `PATH`
- Commands such as `cat | cat | ls`

## Allowed Functions

`readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

## Authors

- **Mohamed Zeouaoui** (mzeouaou): [@mohamedzeouaoui](https://github.com/mohamedzeouaoui)
- **Anass Sodor** (asodor): [@anasooo](https://github.com/anasooo)

## Acknowledgments

- The 42 network for the subject and the peer-learning environment
- The Bash manual and `man` pages
- Everyone who tested and challenged the project during evaluations
