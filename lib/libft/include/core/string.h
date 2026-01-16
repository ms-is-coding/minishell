/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smamalig <smamalig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:55:34 by smamalig          #+#    #+#             */
/*   Updated: 2025/11/25 15:56:49 by smamalig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stddef.h>

void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t n);
void		*ft_mempcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

char		*ft_stpcpy(char *dst, const char *src);
char		*ft_stpncpy(char *dst, const char *src, size_t n);

size_t		ft_strlen(const char *s);
size_t		ft_strnlen(const char *s, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcoll(const char *s1, const char *s2);
int			ft_strerror_r(int errnum, char *buf, size_t size);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t dsize);
char		*ft_strcat(char *dst, const char *src);
char		*ft_strncat(char *dst, const char *src, size_t ssize);
char		*ft_strdup(const char *s);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strpbrk(const char *s, const char *accept);
char		*ft_strstr(const char *haystack, const char *needle);
char		*ft_strtok(char *str, const char *delim);
char		*ft_strtok_r(char *str, const char *delim, char **saveptr);
char		*ft_strerror(int errnum);
char		*ft_strsignal(int sig);
size_t		ft_strcspn(const char *s, const char *reject);
size_t		ft_strspn(const char *s, const char *accept);
size_t		ft_strxfrm(char *dst, const char *src, size_t n);

size_t		ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dsize);
char		*ft_strnstr(const char *haystack, const char *needle, size_t n);

#endif // STRING_H
