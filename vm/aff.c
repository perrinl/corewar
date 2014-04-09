/*
** aff.c for aff in /home/merran_g/work/c_elem/corewar/vm
** 
** Made by Geoffrey Merran
** Login   <merran_g@epitech.net>
** 
** Started on  Tue Apr  8 19:31:35 2014 Geoffrey Merran
** Last update Wed Apr  9 15:19:34 2014 Geoffrey Merran
*/

#include "aff.h"

void	init_window(t_win *win)
{
  xSDL_Init(SDL_INIT_VIDEO);
  xTTF_Init();
  win->screen = xSDL_SetVideoMode(SIZE_X, SIZE_Y, 32, SDL_HWSURFACE);
  SDL_WM_SetCaption("Corewar 2014", NULL);
  win->police = TTF_OpenFont("police/imagine_font.ttf", 20);
  win->color.r = 255;
  win->color.g = 255;
  win->color.b = 255;
}

Uint32		get_case_color(t_arena *arena, int address, t_proc *procs, t_win *win)
{
  t_proc	*tmp;

  tmp = procs;
  while (tmp)
    {
      if (address == tmp->pc)
	return (SDL_MapRGB(win->screen->format, 0, 255, 255));
      tmp = tmp->next;
    }
  if (arena->color[address] == 1)
    return (SDL_MapRGB(win->screen->format, 255, 0, 0));
  if (arena->color[address] == 2)
    return (SDL_MapRGB(win->screen->format, 0, 0, 255));
  return (SDL_MapRGB(win->screen->format, 20, 20, 20));
}

void		aff_window(t_win *win, t_arena *arena, t_proc *procs, t_cycles *cycles)
{
  SDL_Surface	*text;
  SDL_Rect	pos;

  pos.x = 26;
  pos.y = 30;
  text = TTF_RenderText_Solid(win->police, "Current Cycle :", win->color);
  SDL_BlitSurface(text, NULL, win->screen, &pos);
  aff_arena(win, arena, procs);
  SDL_Flip(win->screen);
  SDL_FreeSurface(text);
}

void		aff_arena(t_win *win, t_arena *arena, t_proc *procs)
{
  int		i;
  SDL_Rect	*pos;

  i = 0;
  pos = my_xmalloc(sizeof(*pos));
  pos->x = 26;
  pos->y = 200;
  pos->w = PLOT_W;
  pos->h = PLOT_H;
  while (i < MEM_SIZE)
    {
      SDL_FillRect(win->screen, pos, get_case_color(arena, i, procs, win));
      pos->x += pos->w + SEP_W;
      if (pos->x >= SIZE_X - 26)
	{
	  pos->x = 26;
	  pos->y += pos->h + SEP_H;
	}
      i++;
    }
}