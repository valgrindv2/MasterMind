/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:06:16 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/18 16:06:16 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../parsing/minishell.h"
# define RECURS_LIMIT 500
# define EXECVE_FAILURE 127
# define EXPORTED true
# define NO_VALUE false

# define ANON 127

# define PANIC true
# define CHILL false

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*gnl_ft_strjoin(char *s1, char *s2);
size_t	gnl_ft_strlen(const char *s);
char	*gnl_ft_strdup(char *s1);
char	*gnl_ft_substr(char *s, unsigned int start, size_t len);
char	*gnl_ft_strchr(const char *s, int c);

// # define ANON '-'

// text colors
# define RED "\e[31m"
# define GRN "\e[32m"
# define BLU "\e[34m"
# define YLW "\e[33m"
# define MGN "\e[35m"
# define CYN "\e[36m"
# define RST "\e[97m"

#endif