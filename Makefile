# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 11:03:00 by smamalig          #+#    #+#              #
#    Updated: 2025/10/01 22:19:21 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -MMD -MP -std=c99
SRC_DIR		= src
OBJ_DIR		= obj

SRC_ARGS	= arguments/init.c arguments/add.c arguments/find.c arguments/get.c
SRC_LEXER	= lexer/init.c lexer/lex.c lexer/advance.c
SRC_PARSER	= parser/init.c parser/parse.c parser/util.c parser/rules.c \
			  parser/command.c parser/expr.c parser/logical.c parser/list.c \
			  parser/group.c parser/redir.c
SRC_BYTECODE 	= bytecode/write.c
SRC_BUILTINS = builtins/cd.c builtins/echo.c builtins/exec.c builtins/exit.c \
			   builtins/false.c builtins/pwd.c builtins/true.c
SRC_FILES	:= $(SRC_ARGS) $(SRC_LEXER) $(SRC_PARSER) $(SRC_BYTECODE) \
			   $(SRC_BUILTINS) main.c

SRCS		:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS		:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.d, $(SRCS))

INCLUDES	= -Iinclude -Ilibft/include

RED			= \e[31m
GREEN		= \e[32m
YELLOW		= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m
CYAN		= \e[36m
RESET		= \e[m

LIBFT_FLAGS	= -Llibft -lft
LIBFT_DIR	= ./libft

LDFLAGS		= $(LIBFT_FLAGS) -lreadline

ifeq ($(DEBUG), 1)
	CFLAGS += -Og -g3 -D_DEBUG \
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
	CFLAGS += -Werror
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

