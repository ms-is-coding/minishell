# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mattcarniel <mattcarniel@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 11:03:00 by smamalig          #+#    #+#              #
#    Updated: 2026/01/16 17:32:24 by mattcarniel      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell

SRC_DIR			:= src
LIB_DIR			:= lib
BUILD_DIR		:= build

CC				:= cc
CFLAGS			:= -Wall -Wextra -MMD -MP -std=gnu2x
CFLAGS_DEBUG	:= -Og -g3 -Wshadow -Wpadded -Wconversion -Wstrict-prototypes \
					-Wmissing-declarations -Wstrict-prototypes -Wundef \
					-Wmissing-prototypes -Wold-style-definition -Winline \
					-Wsign-conversion -Wcast-align -Wcast-qual -Wwrite-strings \
					-Wuninitialized -Wdouble-promotion -Wfloat-equal -Wvla \
					-Wnull-dereference -Wformat=2 -fstack-protector-strong
CFLAGS_RELEASE	:= -O2 -DNDEBUG -march=native -D__is_42sh
CFLAGS_SANITIZE	:= -fsanitize=address,undefined,leak


ifeq ($(MODE), release)
	CFLAGS += $(CFLAGS_RELEASE)
else ifeq ($(MODE), debug)
	CFLAGS += $(CFLAGS_DEBUG)
else ifeq ($(MODE), sanitize)
	CFLAGS += $(CFLAGS_DEBUG) $(CFLAGS_SANITIZE)
else
	MODE = default
	CFLAGS += -Werror
endif

ROOT_DIR	:= $(BUILD_DIR)/$(MODE)
OBJ_DIR		:= $(ROOT_DIR)/obj

SRC_CLI			= cli/init.c cli/add.c cli/find.c cli/get.c cli/parse.c
SRC_LEXER		:= $(addprefix lexer/, advance.c amp.c comment.c delim.c \
					dollar.c eof.c error.c group.c init.c internal.c lex.c \
					number.c pipe.c print.c redir.c)
SRC_PARSER		:= $(addprefix parser/, init.c parse.c util.c rules.c \
					command.c expr.c logical.c list.c group.c redir.c)
SRC_BYTECODE	= bytecode/write.c bytecode/get.c
SRC_BUILTINS 	:= $(addprefix builtins/, _find.c cd.c echo.c env.c error.c \
					exec.c exit.c export.c false.c pwd.c readonly.c true.c \
					type.c unset.c help.c \
					echo_internal.c export_internal.c \
					type_internal.c help_internal.c)
SRC_VM			:= $(addprefix vm/, run.c jump.c redir.c arg.c spawn.c wait.c \
					cmd.c exec.c heredoc.c init.c)
SRC_DISASM		:= $(addprefix disasm/, disasm.c print.c print2.c null.c cmd.c \
					arg.c exec.c redir.c jump.c heredoc.c)
SRC_ENV			:= $(addprefix env/, hash.c get.c set.c remove.c find.c init.c \
					build.c destroy.c resize.c)
SRC_ALLOCATOR	:= $(addprefix allocator/, init.c destroy.c alloc.c free.c \
					malloc.c strdup.c \
					arena/alloc.c arena/free.c arena/new.c arena/create.c \
					arena/destroy.c arena/find.c \
					slab/alloc.c slab/free.c slab/create.c slab/destroy.c)
SRC_EXPANDER	:= $(addprefix expander/, expand.c init.c internal.c var.c \
					char.c dquote.c squote.c user.c)
SRC_UTIL		:= $(addprefix util/, warn.c version.c exec.c time.c \
					secure.c signals.c prompt.c)

SRC_FILES		:= $(SRC_CLI) $(SRC_LEXER) $(SRC_PARSER) $(SRC_BYTECODE) \
					$(SRC_BUILTINS) $(SRC_VM) $(SRC_ALLOCATOR) $(SRC_DISASM) \
					$(SRC_ENV) $(SRC_EXPANDER) $(SRC_EXEC) $(SRC_UTIL) \
					main.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS			:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS			:= $(OBJS:.o=.d)

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

LIBFT_DIR		:= $(LIB_DIR)/libft
LIBFT			:= $(LIBFT_DIR)/libft.a
LDLIBS			:= -lftcore -lftvector -lftprintf -lftmath -lreadline
LDFLAGS			:= -L$(LIBFT_DIR)

INCLUDES		:= -Iinclude -I$(LIBFT_DIR)/include


.PHONY: all
all: $(NAME)
	@$(MAKE) postbuild --no-print-directory


.PHONY: default
default: all


.PHONY: release
release:
	@$(MAKE) MODE=release --no-print-directory


.PHONY: debug
debug:
	@$(MAKE) MODE=debug --no-print-directory


.PHONY: sanitize
sanitize:
	@$(MAKE) MODE=sanitize --no-print-directory


.PHONY: bonus
bonus: release


.PHONY: postbuild
postbuild:
	cp -f $(ROOT_DIR)/$(NAME) $(NAME)


$(NAME): libft
	@make $(ROOT_DIR)/$(NAME) --no-print-directory


$(ROOT_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(ROOT_DIR)/$(NAME)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


.PHONY: libft
libft:
	$(MAKE) -C $(LIBFT_DIR) --no-print-directory


.PHONY: clean
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	rm -rf $(BUILD_DIR)


.PHONY: fclean
fclean:
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	rm -rf $(BUILD_DIR)
	rm -f $(NAME)


.PHONY: re
re: fclean
	@$(MAKE) all --no-print-directory


.PHONY: norm
norm:
	@echo $(SRCS) | xargs -n1 -P$(shell nproc) norminette | grep -v OK!


.PHONY: tidy
tidy:
	echo $(SRCS) | xargs -n1 -P$(shell nproc) clang-tidy -p .


-include $(DEPS)
