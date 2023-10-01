#1;bold 2;low intensity 4;Underline 5;Blink 8;invis 9;strike
BLK	= \033[30m
RED	= \033[31m
GRN	= \033[32m
BRN	= \033[33m
BLU	= \033[34m
PUR	= \033[35m
CYN	= \033[36m
LGR	= \033[37m
RST	= \033[0m
USER		:=$(shell whoami)
NAME		:=	minishell
UNAME_S 	:= $(shell uname -s)
#---------------Directories----------------------
SRC_D		:=	src/
BUILD_D		:=	.build/
LIB_D		:=	libft/
INC			:=	inc/ libft/inc/

#---------------Add .c / .h here \/--------------
BUILTIN		:=	env.c	export.c	unset.c	echo.c	pwd.c	cd.c
UTILS		:=	free_return.c	export_unset_utils.c	env_utils.c		\
				getvar.c	extract_var_data.c	extract_var_name.c		\
				add_to_matrix.c	free_join.c	count_strings.c	only_spaces.c
SRC			:=	builtin.c	main.c	init_env.c	prompt.c	signal_handler.c	\
				tokenizer.c	update_history.c

LIB			:=	ft readline
#FRAMEWORK	:=	OpenGL	AppKit
#----------------------IGNORE--------------------
#------------------------------------------------
SRC			+=	$(BUILTIN:%=builtin/%)
SRC			+=	$(UTILS:%=utils/%)
SRC			:=	$(SRC:%=$(SRC_D)%)
OBJ 		:=	$(SRC:$(SRC_D)%.c=$(BUILD_D)%.o)
DEPS        :=	$(OBJ:.o=.d)
#------------------------------------------------
#----------------Linux libs \/-------------------
ifeq ($(USER),jansol)
LIB_D		:=	libft/ /opt/homebrew/opt/readline/lib/
INC			:=	/opt/homebrew/opt/readline/include/ inc/ libft/inc/
endif
ifeq ($(UNAME_S),Linux)
LIB_D		:=	libft/
INC			:=	inc/ libft/inc/
LIB			:=	ft readline history
FRAMEWORK	:=	
endif
#-------------------------------------------------
RM			:=	rm -rf
CC			:=	gcc
DIR_DUP     =	mkdir -p "$(@D)"
#-MMD -MP = Used to add dependencies during precomp. (for .h)
CPPFLAGS    :=	-MMD -MP $(addprefix -I,$(INC))
CFLAGS		:=	-Wextra -Werror -Wall
# -(r)eplace the older objects, -(c)reate if no lib, -s index stuff
AR          :=	ar
ARFLAGS     :=	-r -c -s
LDFLAGS     :=	$(addprefix -L,$(dir $(LIB_D)))
LDLIBS      :=	$(addprefix -l,$(LIB))
LDFMWK		:=	$(addprefix -framework ,$(FRAMEWORKS))
MAKEFLAGS   += --no-print-directory
#-----------------------------all------------------------------------
all		:	$(NAME)
#-----------------------------NAME-----------------------------------
$(NAME)	:	$(OBJ)
			$(MAKE) complib
			${CC} $(LDFLAGS) $(OBJ) $(LDLIBS) $(LDFMWK) -o $(NAME)
			$(info MAKING $(NAME).....)
			echo "\033[5;32m\t\tFinished compiling $(NAME) !!! $(CLR)"
#------------------------OBJ COMPILATION-----------------------------
$(BUILD_D)%.o	:	$(SRC_D)%.c
			$(DIR_DUP)
			$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
			echo created $(@F)

-include	${DEPS}
#----------------------------COMPLIB---------------------------------
complib	:
	$(info COMPILING THE LIBS)
	@$(MAKE) -s -C libft
ifeq ($(UNAME_S),Linux)
endif
ifeq ($(UNAME_S),Darwin)
endif
#----------------------------CLEAN-----------------------------------
clean	:
	$(RM) $(OBJ) $(DEPS)
	$(MAKE) -C libft clean
ifeq ($(UNAME_S),Darwin)
else
endif
	echo "$(CYN) \t\tALL CLEANED $(RST)"
#----------------------------FCLEAN----------------------------------
fclean	:	clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean
ifeq ($(UNAME_S),Darwin)
else
endif
	echo "\033[5;36m \t\tALL F*NG CLEANED !!! $(RST)"
#------------------------------RE------------------------------------
re		:	fclean all

.PHONY	:	all clean fclean re
.SILENT :
