/*
** vm_arena2.c for  in /home/nicolas/Workspace/Corewar/vm
** 
** Made by Nicolas Ades
** Login   <nicolas@epitech.net>
** 
** Started on  Thu Apr  3 14:19:48 2014 Nicolas Ades
** Last update Sun Apr 13 17:12:13 2014 Geoffrey Merran
*/

#include "vm_arena.h"

void		reset_pc(t_proc *proc)
{
  t_proc	*tmp;

  tmp = proc;
  while (tmp != NULL)
    {
      tmp->alive = 0;
      tmp = tmp->next;
    }
}

int		one_winner(t_proc *proc, t_champ *champ)
{
  int		nb_alive;
  t_champ	*tmp_ch;

  nb_alive = 0;
  tmp_ch = champ;
  while (tmp_ch != NULL)
    {
      if (tmp_ch->live > 0)
	nb_alive++;
      tmp_ch = tmp_ch->next;
    }
  reset_pc(proc);
  if (nb_alive < 2)
    return (1);
  tmp_ch = champ;
  while (tmp_ch != NULL)
    {
      tmp_ch->live = 0;
      tmp_ch = tmp_ch->next;
    }
  return (0);
}

void		who_win(t_champ *champ)
{
  t_champ	*tmp;
  int		win;

  tmp = champ;
  win = nb_champ_alive(champ);
  my_printf("\n");
  while (tmp)
    {
      if (tmp->live != 0 && win != 1)
	my_printf("Player n°%d is alive !\n", tmp->id);
      if (tmp->live != 0 && win == 1)
	my_printf("Player n°%d is winner !\n", tmp->id);
      tmp = tmp->next;
    }
  if (win == 0)
    my_printf("Nobody is alive\n");
}

int	my_mod(int a, int b)
{
  int	r;

  r = a % b;
  return (r < 0 ? r + b : r);
}
