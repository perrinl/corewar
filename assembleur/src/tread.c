/*
** tread.c for  in /home/mediav_j/corewar/assembleur/src
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Wed Apr  2 15:39:27 2014 Jeremy Mediavilla
** Last update Fri Apr 11 16:36:55 2014 Joris Bertomeu
*/

#include "assembleur.h"
#include "gnl.h"

void		tread_line(char *buff, t_system *system, int fd, int line)
{
  int		ret;

  ret = parse_line_cn(buff, system, fd);
  if (ret == 0)
    write_to_file(buff, fd, line, system);
}

void	do_labels(int fd, t_system *sys)
{
  int		i;
  int		j;
  t_conv	conv;

  i = 0;
  printf("CL = %d COL = %d\n", sys->cl, sys->col);
  while (i < sys->cl)
    {
      j = 0;
      while (j < sys->col)
	{
	  if (strcmp(sys->olabels[j].name, sys->labels[i].name) == 0)
	    {
	    printf("Ecriture de %d à l'offset %d\n", sys->labels[i].offset,
		   sys->olabels[j].offset);
	    conv.value = sys->labels[i].offset - sys->olabels[j].offset;
	    lseek(fd, sys->olabels[j].offset, SEEK_SET);
	    write(fd, &conv.octets[3], 1);
	    write(fd, &conv.octets[2], 1);
	    write(fd, &conv.octets[1], 1);
	    write(fd, &conv.octets[0], 1);
	    }
	  j++;
	}
      printf("%d => >%s<\n", sys->labels[i].offset, sys->labels[i].name);
      i++;
    }
}

void	second_pass(int fd, t_system *sys)
{
  t_conv	conv;
  unsigned int	size;

  size = lseek(fd, 0, SEEK_END) - (4 + 4 + 2048 + 128);
  conv.value = size;
  lseek(fd, 4, SEEK_SET);
  write(fd, &conv.octets[3], 1);
  write(fd, &conv.octets[2], 1);
  write(fd, &conv.octets[1], 1);
  write(fd, &conv.octets[0], 1);
  do_labels(fd, sys);
}

char	*parse_name_file(t_system *sys)
{
  int	i;
  char	*tmp;

  tmp = malloc(256 * sizeof(*tmp));
  i = 0;
  while (sys->name_file[i] != '.' && sys->name_file[i])
    {
      tmp[i] = sys->name_file[i];
      i++;
    }
 return (tmp);
}

void		tread_file(char *path, t_system *sys)
{
  int		fd;
  char		*buff;
  int		fd2;
  int		line;
  char		*name;

  buff = malloc(4096 * sizeof(*buff));
  memset(buff, 0, 4096);
  line = 0;
  name = malloc(256 * sizeof(*name));
  name = parse_name_file(sys);
  fd = open(path, O_RDONLY);
  fd2 = open(name,
	    O_CREAT | O_TRUNC | O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
  if (fd != -1 && fd2 != -1)
    {
      write_magic(fd2);
      while ((buff = get_next_line(fd)) != NULL)
	{
	  sys->start_line = lseek(fd2, 0, SEEK_CUR);
	  tread_line(buff, sys, fd2, line++);
	}
    }
  second_pass(fd2, sys);
  free(buff);
}

void		tread_line_cnf_asm(t_system *system, char *buff, int line)
{
  int		i;
  int		j;

  j = 0;
  i = 0;
  while (buff[i] != ':')
    {
      system->cmd_asm[line][0][i] = buff[i];
      i++;
    }
  i++;
  while (buff[i] != '\0')
    {
      system->cmd_asm[line][1][j++] = buff[i];
      i++;
    }
}
