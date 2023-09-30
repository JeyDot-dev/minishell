minishell
=
## Summary:
This project is about creating a simple shell.
### Features so far
*  tokenize cmd_line to an array of strings usable for parsing and handles errors such as missing arg after "|><". Example :
  ```
input: "Hello'X'" I 'a'm > "A string"
output:
Hello'X'
I
am
>
A string
```
*  while "tokenizing" also expands env variables and $?
*  handles Ctrl-D, Ctrl-C, Ctrl-\ (Ctrl-\ has no effect)
*  displays a prompt with the PWD and the color of the prompt shows if the last one had an error or not
*  has builtin functions (env, cd, pwd, unset, echo, exit)
*  Updates the environement when needed (SHLVL, PWD, OLD_PWD and soon _=)
*  If an environement doesn't exist, then minishell creates a simple one.
#### TODO
1. Tokenization  ✓
   + Meta-chars  ✓
   + Strings  ✓
   + single/double quotes  ✓
   + var expansion  ✓
2. organise tokens in struct.
   + make and plan struct
   + parsing
3. external cmd execution (execve).
4. pipes and redirections
5. update some env vars
   + SHLVL ✓
   + _=

probably some other stuff that I'll figure out.
