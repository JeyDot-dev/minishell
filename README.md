## Minishell Project Summary

Minishell is a simple shell implementation with the following features:

### Current Features:
- Tokenizes command lines for parsing, handling errors such as missing arguments after "|><," and expanding environment variables.
- Handles Ctrl-D, Ctrl-C, and displays a colored prompt indicating the success or failure of the last command.
- Offers built-in functions (env, cd, pwd, unset, echo, exit).
- Updates the environment variables (SHLVL, PWD, OLD_PWD) as needed and creates a simple environment if it doesn't exist.
- Provides two debug modes for additional information (-d for standard debug and -v for more details).
- Implements history functionality similar to bash, excluding duplicates and empty commands.

### To-Do List:
1. Organize tokens into a structured format.
2. Implement external command execution (execve).
3. Add support for pipes and redirections.
4. Update specific environment variables (SHLVL, _=).
5. Address and fix minor bugs, including those related to history and handling empty input.
