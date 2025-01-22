/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharumi <naharumi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:05:14 by naharumi          #+#    #+#             */
/*   Updated: 2025/01/22 17:58:03 by naharumi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

// libft
int		ft_atoi(const char *nptr);
int		ft_atoi_base(char *str, char *base);
int		ft_isdigit(int c);
int		ft_isspace(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_free_arr(char **arr);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);

// split
char	**ft_split(char const *s, char c);
char	**ft_split_args(char const *s, char c);
char	*get_substr(char const *s, char c);
void	*free_arr(char **arr, int i);
int		args_count(char const *s, char c);
int		arg_len(char const *str, char c);

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);

// printf
int	ft_printf(const char *format, ...);
int	print_arg(va_list args, char spec);
int	print_chr(char c);
int	print_str(char *str);
int	print_nbr(long nbr);
int	print_unbr(unsigned int nbr);
int	print_ptr(unsigned long ptr);
int	print_hex(unsigned long n, const char *base);

#endif