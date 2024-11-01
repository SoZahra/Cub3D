/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:24:47 by fzayani           #+#    #+#             */
/*   Updated: 2024/10/23 14:25:29 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);

int					ft_isalnum(int c);

int					ft_isalpha(int c);

int					ft_isascii(int c);

int					ft_isdigit(int c);

int					ft_isprint(int c);

int					ft_tolower(int c);

int					ft_toupper(int c);

char				*ft_itoa(int nb);

size_t				ft_strlen(const char *s);

void				ft_putchar_fd(char c, int fd);

void				ft_putnbr_fd(int n, int fd);

void				ft_putstr_fd(char *s, int fd);

void				ft_putendl_fd(char *s, int fd);

void				ft_bzero(void *s, size_t n);

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int					ft_strncmp(char *s1, char *s2, unsigned int n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

int					ft_isspace(int c);

size_t				ft_strlcat(char *dest, const char *src, size_t destlen);

size_t				ft_strlcpy(char *dest, const char *src, size_t destlen);

char				*ft_strdup(const char *s1);

char				**ft_split(char const *s, char c);

void				*ft_memset(void *b, int c, size_t len);

char				*ft_strchr(const char *str, int occ);

char				*ft_strrchr(const char *str, int occ);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strtrim(char const *s1, char const *set);

void				*ft_calloc(size_t count, size_t size);

void				*ft_memchr(const void *s, int occ, size_t n);

void				*ft_memcpy(void *dest, const void *src, size_t n);

void				*ft_memmove(void *dest, const void *src, size_t len);

char				*ft_strnstr(const char *s1, const char *s2, size_t n);

char				*ft_substr(char const *s, unsigned int start, size_t len);

t_list				*ft_lstnew(void *content);

void				ft_lstadd_front(t_list **lst, t_list *new);

void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_lstsize(t_list *lst);

t_list				*ft_lstlast(t_list *lst);

void				ft_lstdelone(t_list *lst, void (*del)(void *));

void				ft_lstclear(t_list **lst, void (*del)(void *));

char				*ft_itoa_unsigned(unsigned int n);

int					ft_strcmp(const char *s1, const char *s2);

char				*ft_strndup(const char *s, size_t n);

char				*ft_strncpy(char *dst, const char *src, size_t n);

/// gnl////
char				*get_next_line(int fd);
char				*ft_read_to_left_str(int fd, char *left_str);
char				*ft_strchr_(char *s, int c);
char				*ft_strjoin_(char *left_str, char *buff);
size_t				ft_strlen_(char *s);
char				*ft_get_line(char *left_str, int *is_malloc_error);
char				*ft_new_left_str(char *left_str, int *is_malloc_error);

// gnl 2//

// char	*gnl_strjoin(char *s1, char *s2);
// char	*get_next_line(int fd);

/// ft_printf////
int					ft_putnbr_printf(long nb);
void				ft_rev_printf(char *str);
int					ft_putnbr_base_printf(long int nbr, char *base);
int					ft_print_p(unsigned long address);
int					ft_putstr_printf(const char *str);
int					ft_aff_p(va_list args);
int					ft_printf(const char *format, ...);
int					ft_putchar_printf(char c);

////printf fd

int					ft_putnbr_unsigned_printf_fd(unsigned int n, int fd);
int					ft_aff_p_fd(va_list args, int fd);
int					ft_check_format_fd(char str, va_list args, int fd);
int					ft_printf_fd(int fd, const char *format, ...);
int					ft_putchar_printf_fd(char c, int fd);
int					ft_putstr_printf_fd(const char *str, int fd);
int					ft_putnbr_base_printf_fd(unsigned long nbr,
						const char *base, int fd);
int					ft_putnbr_printf_fd(int n, int fd);

#endif
