/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 23:32:58 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 16:27:06 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDLIB_H
# define STDLIB_H

# include <stdbool.h>
# include <assert.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdarg.h>
# include <time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_rng256
{
	uint64_t	s[4];
	uint64_t	seed;
}	t_rng256;

typedef enum e_result
{
	RESULT_OK,
	RESULT_ERROR,
	RESULT_OVERFLOW,
	RESULT_EOF,
	RESULT_INVAL,
	RESULT_READ_ERROR,
	RESULT_RDONLY,
	RESULT_UNKNOWN
}	t_result;

/* ************************************************************************** */
/* ALLOC                                                                      */
/* ************************************************************************** */

void		*ft_calloc(size_t n, size_t size)
			__attribute__((__warn_unused_result__));

// Warning: only accepts pointers allocated through `ft_malloc`
void		ft_free(void *ptr);

// Warning: this allocation must be freed using `ft_free`
void		*ft_malloc(size_t size)
			__attribute__((__warn_unused_result__));

// Warning: only accepts pointers allocated through `ft_malloc`
void		*ft_realloc(void *ptr, size_t size)
			__attribute__((__warn_unused_result__));

/* ************************************************************************** */
/* RANDOM                                                                     */
/* ************************************************************************** */

void		ft_rng_init(t_rng256 *rng, uint64_t seed);
uint64_t	ft_rng_u64(t_rng256 *rng);
uint32_t	ft_rng_u32(t_rng256 *rng);
double		ft_rng_f64(t_rng256 *rng);

/* ************************************************************************** */
/* CONVERT                                                                    */
/* ************************************************************************** */

int			ft_atoi(const char *nptr);
int			ft_atoi_safe(const char *nptr);
long		ft_atol(const char *nptr);
long		ft_atol_safe(const char *nptr);
long long	ft_atoll(const char *nptr);
long long	ft_atoll_safe(const char *nptr);
int			ft_toupper(int c);
int			ft_tolower(int c);

/* ************************************************************************** */
/* INPUT / OUTPUT                                                             */
/* ************************************************************************** */

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *s, int fd);
void		ft_putendl_fd(const char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/* ************************************************************************** */
/* MATH                                                                       */
/* ************************************************************************** */


/* ************************************************************************** */
/* STRING                                                                     */
/* ************************************************************************** */

char		*ft_itoa(int n);
char		*ft_itoa_unsafe(int n);

/* ************************************************************************** */
/* FILE                                                                       */
/* ************************************************************************** */

# ifndef FILE_BUFFER_SIZE
#  define FILE_BUFFER_SIZE 1024
# endif

typedef struct s_file
{
	int				fd;
	unsigned int	len;
	unsigned int	line;
	_Bool			eof;
	char			reserved[3];
	char			*curr;
	char			buf[FILE_BUFFER_SIZE];
}	t_file;

// internal use only
t_result	_ft_file_refill(t_file *file);

t_result	ft_file_init(t_file *file, int fd)
			__attribute__((__warn_unused_result__));

t_result	ft_file_i8(t_file *file, uint8_t *ret);
t_result	ft_file_u8(t_file *file, uint8_t *ret);
t_result	ft_file_atoi32(t_file *file, int32_t *ret);
t_result	ft_file_atou32(t_file *file, uint32_t *ret);
t_result	ft_file_atox32(t_file *file, uint32_t *ret);
t_result	ft_file_consume(t_file *file, char c, _Bool *found);

_Bool		ft_file_eof(t_file *file);

t_result	_ft_file_skip_whitespace(t_file *file);
t_result	_ft_file_advance(t_file *file);

#endif
