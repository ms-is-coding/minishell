# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 11:03:00 by smamalig          #+#    #+#              #
#    Updated: 2025/10/19 14:17:57 by mattcarniel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minishell
CC				= cc
CFLAGS			= -Wall -Wextra -MMD -MP
SRC_DIR			= src
OBJ_DIR			= obj

SRC_CLI			= cli/init.c cli/add.c cli/find.c cli/get.c cli/parse.c
SRC_LEXER		:= $(addprefix lexer/, advance.c amp.c comment.c delim.c \
					dollar.c eof.c error.c group.c init.c internal.c lex.c \
					number.c pipe.c print.c redir.c)
SRC_PARSER		:= $(addprefix parser/, init.c parse.c util.c rules.c command.c \
					expr.c logical.c list.c group.c redir.c)
SRC_BYTECODE	= bytecode/write.c bytecode/get.c
SRC_BUILTINS 	:= $(addprefix builtins/, error.c cd.c echo.c exec.c exit.c \
					false.c pwd.c true.c env.c export.c alias.c unalias.c \
					type.c cd_internal.c echo_internal.c)
SRC_VM			:= $(addprefix vm/, run.c jump.c redir.c arg.c spawn.c wait.c \
					cmd.c exec.c)
SRC_DISASM		:= $(addprefix disasm/, disasm.c print.c null.c cmd.c arg.c \
					exec.c redir.c jump.c)
SRC_ENV			:= $(addprefix env/, hash.c get.c set.c remove.c find.c init.c \
					build.c)
SRC_ALIAS		:= $(addprefix alias/, hash.c get.c set.c remove.c find.c \
					init.c clear.c print.c)
SRC_ALLOCATOR	:= $(addprefix allocator/, init.c destroy.c alloc.c free.c \
					arena/alloc.c arena/free.c arena/new.c arena/create.c \
					arena/destroy.c arena/find.c \
					slab/alloc.c slab/free.c slab/create.c slab/destroy.c)
SRC_EXPANDER	:= $(addprefix expander/, expand.c init.c internal.c var.c \
					char.c dquote.c squote.c)
# user.c
# SRC_EXEC		:= exec/exec.c

SRC_FILES		:= $(SRC_CLI) $(SRC_LEXER) $(SRC_PARSER) $(SRC_BYTECODE) \
					$(SRC_BUILTINS) $(SRC_VM) $(SRC_ALLOCATOR) $(SRC_DISASM) \
					$(SRC_ENV) $(SRC_ALIAS) $(SRC_EXPANDER) \
					main.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

INCLUDES		= -Iinclude -Ilibft/include

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

LIBFT_FLAGS		= -Llibft -lft
LIBFT_DIR		= ./libft

LDFLAGS			:= $(LIBFT_FLAGS) -lreadline

ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g3 -DDEBUG \
			  -Wpedantic -Wpacked -Wstrict-prototypes -Wshadow -Wpadded \
			  -Wconversion -Wmissing-prototypes -Wmissing-declarations \
			  -Wold-style-definition -Winline -Wsign-conversion -Wundef \
			  -Wcast-align -Wcast-qual -Wwrite-strings -Wuninitialized \
			  -Wdouble-promotion -Wfloat-equal -Wvla -Wnull-dereference \
			  -Wformat=2 -fstack-protector-strong
	ifeq ($(SANITIZE), 1)
		CFLAGS += -fsanitize=address,undefined,leak
	endif
else
	CFLAGS += -Werror -DNDEBUG
endif

ifeq ($(RELEASE), 1)
	CFLAGS += -O3 -DNDEBUG -Werror -march=native
endif

all: $(NAME)

bonus: $(NAME)

$(NAME): $(LIBFT_DIR)/libft.a $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_DIR)/libft.a:
	@$(MAKE) -C $(LIBFT_DIR) USE_ERRNO=1 --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) object files\n" $(NAME)
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Removing$(RESET) executables and libraries\n" $(NAME)
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory

re: fclean
	@$(MAKE) all --no-print-directory

-include $(DEPS)

.PHONY: all clean fclean re bonus

