# Minishell

## Overview
Minishell is a simple shell implementation that allows users to interact with their operating system through a command-line interface. It supports various features such as command execution, history management, redirections, pipes, environment variable expansion, and more.

## Features

### Basic Shell Functionality
- Display a prompt when waiting for a new command.
- Maintain a working history for previously entered commands.

### Command Execution
- Search and launch the right executable based on the PATH variable or using a relative or absolute path.
- Avoid using more than one global variable to indicate a received signal, ensuring signal handlers do not access main data structures.

### Input Handling
- Do not interpret unclosed quotes or special characters not required by the subject (e.g., backslash or semicolon).
- Handle single quotes (`'`) to prevent the shell from interpreting meta-characters in the quoted sequence.
- Handle double quotes (`"`) to prevent the shell from interpreting meta-characters in the quoted sequence except for `$` (dollar sign).

### Redirections
- `<` should redirect input.
- `>` should redirect output.
- `<<` should read input until a line containing the specified delimiter without updating the history.
- `>>` should redirect output in append mode.

### Pipes
- Implement pipes (`|`) where the output of each command in the pipeline is connected to the input of the next command via a pipe.

### Environment Variable Handling
- Handle environment variables (`$`) that expand to their values.

### Special Variables
- Handle `$?`, which expands to the exit status of the most recently executed foreground pipeline.

### Interactive Mode
- Handle `ctrl-C` to display a new prompt on a new line.
- Handle `ctrl-D` to exit the shell.
- Handle `ctrl-\` with no specific action.

### Built-in Commands
- `echo` with option `-n`
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

### Additional Features
- Heredoc expands environment variables.
- Colored prompt to indicate whether the last status code was 0 or not.
- If Minishell is launched without an environment, it creates one that includes: `SHLVL`, `_`, `PATH`, `PWD`.

## Usage
Compile the program using the provided Makefile:

```bash
make
```

Run Minishell:

```bash
./minishell
```

## Makefile Commands
- `make`: Compile the program.
- `make all`: Same as `make`.
- `make clean`: Remove object files.
- `make fclean`: Remove object files and the executable.
- `make re`: Rebuild the program from scratch.

## External Functions
- `readline`, `rl_clear_history`, `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`, `add_history`, `printf`, `malloc`, `free`, `write`, `access`, `open`, `read`, `close`, `fork`, `wait`, `waitpid`, `wait3`, `wait4`, `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`, `exit`, `getcwd`, `chdir`, `stat`, `lstat`, `fstat`, `unlink`, `execve`, `dup`, `dup2`, `pipe`, `opendir`, `readdir`, `closedir`, `strerror`, `perror`, `isatty`, `ttyname`, `ttyslot`, `ioctl`, `getenv`, `tcsetattr`, `tcgetattr`, `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`

## Libft
Libft functions are authorized for use.

Feel free to explore and enjoy the Minishell experience!
