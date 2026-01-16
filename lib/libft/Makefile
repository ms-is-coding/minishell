# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 21:10:40 by smamalig          #+#    #+#              #
#    Updated: 2026/01/16 20:05:25 by smamalig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR			:= src
BUILD_DIR		:= build

CC				:= cc
ZIG				:= zig
AR				:= ar
ARFLAGS			:= rcs
CFLAGS			:= -Wall -Wextra -MMD -MP -std=gnu2x
CFLAGS_DEBUG	:= -Og -g3 -Wshadow -Wpadded -Wconversion -Wstrict-prototypes \
					-Wmissing-declarations -Wstrict-prototypes -Wundef \
					-Wmissing-prototypes -Wold-style-definition -Winline \
					-Wsign-conversion -Wcast-align -Wcast-qual -Wwrite-strings \
					-Wuninitialized -Wdouble-promotion -Wfloat-equal -Wvla \
					-Wnull-dereference -Wformat=2 -fstack-protector-strong
CFLAGS_RELEASE	:= -O2 -DNDEBUG -march=native
CFLAGS_SANITIZE	:= -fsanitize=address,undefined,leak

INCLUDES		:= -Iinclude
NPROC			:= $(shell nproc)

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

CORE_SRC	:= $(addprefix src/core/, alloc/calloc.c alloc/free.c alloc/malloc.c alloc/realloc.c convert/atoi.c convert/atoi_safe.c convert/atol.c convert/atol_safe.c convert/atoll.c convert/atoll_safe.c convert/itoa.c ctype/isalnum.c ctype/isalpha.c ctype/isascii.c ctype/isblank.c ctype/iscntrl.c ctype/isdigit.c ctype/isgraph.c ctype/islower.c ctype/isprint.c ctype/ispunct.c ctype/isspace.c ctype/isupper.c ctype/isxdigit.c ctype/tolower.c ctype/toupper.c file/advance.c file/atoi32.c file/atox32.c file/init.c file/whitespace.c mem/memccpy.c mem/memchr.c mem/memcmp.c mem/memcpy.c mem/memmove.c mem/mempcpy.c mem/memset.c random/rng.c random/rng_init.c str/compare/strcmp.c str/compare/strncmp.c str/concat/strcat.c str/concat/strlcat.c str/concat/strncat.c str/copy/strcpy.c str/copy/strdup.c str/copy/strlcpy.c str/copy/strncpy.c str/copy/strndup.c str/copy/strpcpy.c str/copy/strpncpy.c str/info/strlen.c str/info/strnlen.c str/search/strchr.c str/search/strnstr.c str/search/strpbrk.c str/search/strrchr.c str/search/strspn.c str/search/strstr.c str/search/strtok.c)
VECTOR_SRC	:= $(addprefix src/vector/, capacity.c clear.c every.c foreach.c free.c get.c length.c map.c new.c push.c reserve.c set.c some.c)
PRINTF_SRC	:= $(addprefix src/printf/, conversion.c dprintf.c format.c handlers.c parse_format.c parser.c print_hex.c print_signed.c print_str.c print_unsigned.c printf.c save_pos.c snprintf.c sprintf.c strerror.c util.c util2.c vdprintf.c vprintf.c vsnprintf.c vsprintf.c)
MATH_SRC	:= $(addprefix src/math/, abs.c intlen.c max.c min.c nmax.c nmin.c)

ALL_SRC		:= $(CORE_SRC) $(VECTOR_SRC) $(PRINTF_SRC) $(MATH_SRC)

CORE_OBJ	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(CORE_SRC))
VECTOR_OBJ	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(VECTOR_SRC))
PRINTF_OBJ	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(PRINTF_SRC))
MATH_OBJ	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(MATH_SRC))

CORE_DEP	:= $(CORE_OBJ:.o=.d)
VECTOR_DEP	:= $(VECTOR_OBJ:.o=.d)
PRINTF_DEP	:= $(PRINTF_OBJ:.o=.d)
MATH_DEP	:= $(MATH_OBJ:.o=.d)

CORE_LIB	:= libftcore.a
VECTOR_LIB	:= libftvector.a
PRINTF_LIB	:= libftprintf.a
MATH_LIB	:= libftmath.a

INCLUDES	:= -Iinclude

# **************************************************************************** #
# * RULES                                                                    * #
# **************************************************************************** #


.PHONY: all
all: $(CORE_LIB) $(VECTOR_LIB) $(PRINTF_LIB) $(MATH_LIB)
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


.PHONY: postbuild
postbuild:
	cp -f $(ROOT_DIR)/$(CORE_LIB) $(CORE_LIB)
	cp -f $(ROOT_DIR)/$(VECTOR_LIB) $(VECTOR_LIB)
	cp -f $(ROOT_DIR)/$(PRINTF_LIB) $(PRINTF_LIB)
	cp -f $(ROOT_DIR)/$(MATH_LIB) $(MATH_LIB)


$(CORE_LIB): $(ROOT_DIR)/$(CORE_LIB)

$(VECTOR_LIB): $(ROOT_DIR)/$(VECTOR_LIB)

$(PRINTF_LIB): $(ROOT_DIR)/$(PRINTF_LIB)

$(MATH_LIB): $(ROOT_DIR)/$(MATH_LIB)


$(ROOT_DIR)/$(CORE_LIB): $(CORE_OBJ)
	@echo $(CORE_OBJ)
	ar rcs $@ $^


$(ROOT_DIR)/$(PRINTF_LIB): $(PRINTF_OBJ)
	ar rcs $@ $^


$(ROOT_DIR)/$(VECTOR_LIB): $(VECTOR_OBJ)
	ar rcs $@ $^


$(ROOT_DIR)/$(MATH_LIB): $(MATH_OBJ)
	ar rcs $@ $^


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(ROOT_DIR)/obj


.PHONY: fclean
fclean:
	rm -rf $(BUILD_DIR)
	rm -f $(CORE_LIB) $(VECTOR_LIB) $(PRINTF_LIB) $(MATH_LIB)


.PHONY: re
re: fclean
	@make all --no-print-directory


-include $(CORE_DEP) $(VECTOR_DEP) $(PRINTF_DEP) $(MATH_DEP)


TESTS=$(shell find tests -name "*.zig")


.PHONY: test
test:
	@for t in $(TESTS); do \
		echo "Running $$t..."; \
		$(ZIG) test $$t $(INCLUDES) -lc -L. -lftcore -lftvector \
		-lftprintf -lftmath || exit 1; \
	done


.PHONY: norm
norm:
	echo $(ALL_SRC) | xargs -n1 -P$(NPROC) norminette


.PHONY: tidy
tidy:
	echo $(ALL_SRC) | xargs -n1 -P$(NPROC) clang-tidy -p .
