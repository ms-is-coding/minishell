/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:13:41 by smamalig          #+#    #+#             */
/*   Updated: 2025/12/23 17:35:19 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_INTERNAL_H
# define PRINTF_INTERNAL_H

# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>

enum e_printf_flags
{
	PRINTF_FLAG_ALTERNATE = 1 << 0,
	PRINTF_FLAG_ZEROPAD = 1 << 1,
	PRINTF_FLAG_LEFTADJ = 1 << 2,
	PRINTF_FLAG_SIGN = 1 << 3,
	PRINTF_FLAG_SPPAD = 1 << 4
};

enum e_printf_length_modifiers
{
	PRINTF_LEN_NONE,
	PRINTF_LEN_HH,
	PRINTF_LEN_H,
	PRINTF_LEN_L,
	PRINTF_LEN_LL,
	PRINTF_LEN_Q,
	PRINTF_LEN_J,
	PRINTF_LEN_Z,
	PRINTF_LEN_T,
};

typedef struct s_printf_parser
{
	va_list		ap;
	char		*dst;
	const char	*fmt;
	size_t		size;
	size_t		pos;
	int			flags;
	int			width;
	int			prec;
	int			len_mod;
	int			spec_pos;
	char		spec_buf[32];
	int			reserved_0;
	void		*reserved_1;
	char		(*curr)(struct s_printf_parser *parser);
	char		(*next)(struct s_printf_parser *parser);
	int			(*match)(struct s_printf_parser *parser, char c);
}	t_printf_parser;

# define PRINTF_START 1
# define PRINTF_END 0
# define PRINTF_NUMERIC 1
# define PRINTF_OTHER 0
# define PRINTF_UPPER 1
# define PRINTF_LOWER 0

void		_ft_printf_init_parser(t_printf_parser *p);
void		_ft_printf_reset_parser(t_printf_parser *p);

intmax_t	_ft_printf_abs(intmax_t n);
char		_ft_printf_abs_char(signed char c);
int			_ft_printf_int_len(intmax_t n);
int			_ft_printf_uint_len(uintmax_t n);
void		_ft_printf_char(t_printf_parser *p, char c);

char		*_ft_printf_strchr(const char *s, char c);
int			_ft_printf_isdigit(char c);
size_t		_ft_printf_strnlen(const char *s, size_t n);
const char	*_ft_str_errorname(int error);

void		_ft_printf_insert(t_printf_parser *p, char c);
void		_ft_printf_padding(t_printf_parser *p, int len, int is_start,
				int is_num);
void		_ft_printf_sign(t_printf_parser *p, int is_neg, int is_start);

void		_ft_printf_str(t_printf_parser *p, const char *s);
void		_ft_printf_strerror(t_printf_parser *p);
void		_ft_printf_save_pos(t_printf_parser *p, void *save_ptr);
void		_ft_printf_int(t_printf_parser *p, intmax_t n);
void		_ft_printf_hex(t_printf_parser *p, uintmax_t n, int mask);
void		_ft_printf_pointer(t_printf_parser *p, const void *ptr);
void		_ft_printf_uint(t_printf_parser *p, uintmax_t n);
void		_ft_printf_invalid_format(t_printf_parser *p);

int			_ft_printf_parse_width(t_printf_parser *p);
int			_ft_printf_parse_precision(t_printf_parser *p);
int			_ft_printf_parse_flags(t_printf_parser *p);

void		_ft_printf_handle_hex(t_printf_parser *p, int mask);
void		_ft_printf_handle_int(t_printf_parser *p);
void		_ft_printf_handle_uint(t_printf_parser *p);
int			_ft_printf_handle_conv(t_printf_parser *p);

#endif
