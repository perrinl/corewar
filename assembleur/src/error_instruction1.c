/*
** error_instruction1.c for  in /home/mediav_j/corewar/assembleur/src
** 
** Made by Jeremy Mediavilla
** Login   <mediav_j@epitech.net>
** 
** Started on  Mon Apr  7 15:26:21 2014 Jeremy Mediavilla
** Last update Tue Apr  8 23:45:54 2014 Joris Bertomeu
*/

#include "assembleur.h"
#include "gnl.h"

void		sti_check_err(t_system *sys, int *values)
{
  (void)sys;
  if (values[0] != 1)
    {
      printf("Error on \"sti\" instruction : first param is not a register\n");
      exit(0);
    }
  if (values[2] == 0)
    {
      printf("Error on \"sti\" instruction : wrong number of params\n");
      exit(0);
    }
}

void		and_check_err(t_system *sys, int *values)
{
  (void)sys;
  if (values[2] == 0)
    {
      printf("Error on \"and\" instruction : wrong numbe of param\n");
      exit(0);
    }
  if (values[2] != 1)
    {
      printf("Error on \"and\" instruction : last param is not a register\n");
      exit(0);
    }
}

void		ld_check_err(t_system *sys, int *values)
{
  (void)sys;
  printf("[%d][%d][%d]\n", values[0], values[1], values[2]);
  if (values[2] != 0 || values[1] == 0)
    {
      printf("Error on \"ld\" instruction : wrong number of params\n");
      exit(0);
    }
  if (values[1] != 1)
    {
      printf("Error on \"ld\" instruction : second param must be a register\n");
      exit(0);
    }
}

void		live_check_err(t_system *sys, int *values)
{
  (void)sys;
  (void)values;
}

void		zjmp_check_err(t_system *sys, int *values)
{
  (void)sys;
  if (values[1] != 0)
    {
      printf("Error on \"zjmp\" instruction : too many param\n");
      exit(0);
    }
  if (values[0] == 1)
    {
      printf("Error on \"zjmp\" instruction : first param is not an index\n");
      exit(0);
    }
}
