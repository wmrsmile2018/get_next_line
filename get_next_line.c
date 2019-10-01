/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bannabel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 20:17:06 by bannabel          #+#    #+#             */
/*   Updated: 2019/09/30 20:17:09 by bannabel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "stdio.h"

int ft_get_line(int fd, char **line, char *(*s)[])
{
  char *tmp;
  char **str;
  int len;

  str = *s;
  len = 0;
  while(str[fd][len] != '\n' && str[fd][len] != '\0')
    len++;
  *line = ft_strsub(str[fd], 0, len);
  tmp = ft_strdup(str[fd] + len + 1);
  free(str[fd]);
  printf("str[fd]_________%s\n", str[fd]);
  str[fd] = tmp;
  // printf("%s\n", str[fd]);
  return (1);
}

int get_next_line(const int fd, char **line)
{
  size_t size;
  char *str[MAX_FD + 1];
  char buf[BUFF_SIZE + 1];
  char *tmp;

  if(!line || BUFF_SIZE < 1 || fd < 0 || fd > MAX_FD)
    return (-1);
  if(!str[fd])
    str[fd] = ft_strnew(0);
  while(!ft_strrchr(str[fd], '\n') && (size = read(fd, buf, BUFF_SIZE)) > 0)
  {
    tmp = ft_strjoin(str[fd], buf);
    free(str[fd]);
    str[fd] = tmp;
  }
  if(size )
    return(ft_get_line(fd, line, &str));
  // else if(str[fd])
  // {
    // free(str[fd]);
    // printf("wowowowowo %s\n", str[fd]);
    // *line = ft_strjoin(str[fd], buf);
    // free(str[fd]);
    // return(1);
  // }
  return (0);
}

int main () {
  char *line;
  int fd = open("text", O_RDONLY);
  for(int i = 1; get_next_line(fd, &line) > 0; i++) {
    // printf("%d) %s\n", i, line);
    // printf("_______________________________%d______________________________\n", i);
  }
}
