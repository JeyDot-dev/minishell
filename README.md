minishell
=
## Summary:
This project is about creating a simple shell.
### Features so far
*  tokenize cmd_line to an array of strings usable for parsing and handles errors such as missing arg after "|><" and updates g_status also expands env variables and "$?" to last executed command code. Example :
  ```
input: "Hello'X'" I 'a'm > "A string" $PWD
output:
Hello'X'
I
am
>
A string
home/user/minishell
```
*  handles Ctrl-D, Ctrl-C, Ctrl-\ (Ctrl-\ has no effect)
*  displays a prompt with the PWD and the color of the prompt shows if the last one had an error or not
*  has builtin functions (env, cd, pwd, unset, echo, exit)
*  Updates the environement when needed (SHLVL, PWD, OLD_PWD and soon _=)
*  If an environement doesn't exist, then minishell creates a simple one.
*  Has 2 debug modes that show different informations while using the shell (-d for standard debug and -v for a little more informations)
*  History works like bash, it doesn't store duplicate commands and empty commands
#### TODO

1. organise tokens in struct.
   + make and plan struct                  [X]
   + parsing
2. external cmd execution (execve).
3. pipes and redirections
4. update some env vars
   + SHLVL ✓
   + _=
5. bugfix
   + fix rare bug with history/terminal (echo -n cause it)
   + fix "" segfault
