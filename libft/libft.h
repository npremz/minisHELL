/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npremont <npremont@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:00:38 by npremont          #+#    #+#             */
/*   Updated: 2023/12/15 11:44:52 by npremont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# endif

/* STRUCTURES */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* FUNCTIONS */

void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
size_t	ft_strlcpy(char *dst, const char *src,
			size_t dstsize);
size_t	ft_strlen(const char *str);
int		ft_atoi(const char *nptr);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	**ft_split(char const *str, char charsep);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src,
			size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *prefix, char *suffix);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlcat(char *dst, const char *src,
			size_t dstsize);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_strjoin_gnl(char *prefix, char *suffix, int has_fail);
int		ft_has_newline(char *str);
char	*get_next_line(int fd);
void	ft_free_gnl(char **ptr, int flag, char **buff);
int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_printn(char *str);
int		ft_printaddr(char *str);
char	*ft_utoa_base(unsigned int nbr, char *base);
char	*ft_lutoa_base(unsigned long int nbr, char *base);
char	*ft_utoa(unsigned int n);
int		ft_printf(const char *input, ...);
int		ft_isinstr(char c, char *str);
int		ft_atoi_base(char *str, char *base);
void	ft_free(void *ptr);
void	ft_free_split(char **split);
void	*ft_realloc(void *ptr, size_t size, int free_ptr);

#endif
