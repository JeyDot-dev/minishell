## Minishell Project Summary

Minishell is a simple shell implementation with the following features:

### Current Features:
- Tokenizes command lines for parsing, handling errors such as missing arguments after "|><" and expanding environment variables.
- Creates/open files and handles here doc
- Checks for access rights for files and programs
- Has a few small easter eggs
- Handles Ctrl-D, Ctrl-C, and displays a colored prompt indicating the success or failure of the last command.
- Offers built-in functions (env, cd, pwd, unset, echo, exit).
- Can use any external programs/functions
- Handles pipes and redirections
- Updates the environment variables (SHLVL, PWD, OLD_PWD) as needed and creates a simple environment if it doesn't exist.
- Provides two debug modes for additional information (-d for standard debug and -v for more details).
- Implements history functionality similar to bash, excluding duplicates and empty commands.
- Returns the right error codes

### To-Do List:
1. update SHLVL
2. ERRNO
3. Final bug hunt
