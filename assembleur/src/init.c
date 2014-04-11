/*
** init.c for  in /home/mediav_j/corewar/assembleur/src
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Wed Apr  2 15:07:56 2014 Jeremy Mediavilla
** Last update Fri Apr 11 16:37:19 2014 Joris Bertomeu
*/

#include "assembleur.h"
#include "gnl.h"

char		**init_tab()
{
  char		**tab;

  tab = malloc(17 * sizeof(char *));
  tab[0] = "sti";
  tab[1] = "and";
  tab[2] = "ld";
  tab[3] = "live";
  tab[4] = "zjmp";
  tab[5] = "st";
  tab[6] = "add";
  tab[7] = "sub";
  tab[8] = "or";
  tab[9] = "xor";
  tab[10] = "ldi";
  tab[11] = "fork";
  tab[12] = "lld";
  tab[13] = "lldi";
  tab[14] = "lfork";
  tab[15] = "aff";
  tab[16] = NULL;
  return (tab);
}

void		init_cmd_asm(t_system *system)
{
  int		i;
  int		j;

  i = 0;
  system->cmd_asm = malloc(16 * sizeof(*system->cmd_asm));
  memset(system->cmd_asm, 0, 16 * sizeof(*system->cmd_asm) - 1);
  while (i < 16)
    {
      system->cmd_asm[i] = malloc(2 * sizeof(**system->cmd_asm));
      memset(system->cmd_asm[i], 0, 2 * sizeof(**system->cmd_asm) - 1);
      j = 0;
      while (j < 2)
	{
	  system->cmd_asm[i][j] = malloc(32 * sizeof(***system->cmd_asm));
	  memset(system->cmd_asm[i][j++], 0, 32 * sizeof(***system->cmd_asm) - 1);
	}
      i++;
    }
  parse_list_asm(system);
}

void		init(int ac, char **argv)
{
  int		i;
  t_system	*system;

  i = 1;
  system = malloc(sizeof(*system));
  check_ext(ac, argv);
  system->f_c = 0;
  system->f_n = 0;
  system->wm = 0;
  system->cl = 0;
  system->col = 0;
  system->ins.c = 0;
  system->ins.i = 0;
  system->ins.ibase = 0;
  system->ins.ret_chck = 0;
  system->ins.cmptr = 0;
  system->name_file = malloc(256 * sizeof(*system->name));
  while (i < ac)
    {
      system->comment = 0;
      system->name = 0;
      strcpy(system->name_file, argv[i]);
      tread_file(argv[i], system);
      aff_info(system, argv[i++]);
    }
}

void		header_init1(int *j, t_system *sys, int fd, int *i)
{
  char		c;

  c = 0x0;
  sys->f_n = 1;
  *j = (int) lseek(fd, 0, SEEK_CUR);
  write(fd, sys->name, strlen(sys->name));
  *i = (int) lseek(fd, 0, SEEK_CUR) - *j;
  *j = 0;
  while (*j < PROG_NAME_LENGTH - *i)
    {
      write(fd, &c, 1);
      (*j)++;
    }
  printf(">> Name wrote ( %d/%i octets, Total %d octets )\n", *i,
	 PROG_NAME_LENGTH, (int) lseek(fd, 0, SEEK_CUR));
}

char		*init_tab_char()
{
  char		*tab;

  tab = malloc(17 * sizeof(char));
  tab[0] = 0x1;
  tab[1] = 0x2;
  tab[2] = 0x3;
  tab[3] = 0x4;
  tab[4] = 0x5;
  tab[5] = 0x6;
  tab[6] = 0x7;
  tab[7] = 0x8;
  tab[8] = 0x9;
  tab[9] = 0xa;
  tab[10] = 0xb;
  tab[11] = 0xc;
  tab[12] = 0xd;
  tab[13] = 0xe;
  tab[14] = 0xf;
  tab[15] = 0x10;
  tab[16] = '\0';
  return (tab);
}
