/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:13:09 by sarchoi           #+#    #+#             */
/*   Updated: 2022/08/29 14:49:42 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

# define FT_SUCCESS	1
# define FT_ERROR	-1
# define FT_EOF		0
# define FT_TRUE	1
# define FT_FALSE	0
# define BUFFER_SIZE 50

int		get_next_line(int fd, char **line);

char	*ft_strchr(const char *s, int c);
char	*ft_gnl_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *src);

#endif
