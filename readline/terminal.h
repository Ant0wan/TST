/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:57 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/09 23:40:37 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# define NUM_TC_STRINGS 8

struct	s_termcaps
{
	char	*bl;
	char	*cd;
	char	*clreol;
	char	*clrpag;
	char	*cr;
	char	*sf;
	char	*sr;
	char	*cm;
};

struct	s_termcaps_string
{
	const char *const	var;
	char				**value;
};

struct	s_screen
{
	int	w;
	int	height;
	int	chars;
};

struct	s_term
{
	char	*terminal_name;
};

extern struct s_termcaps				g_termcaps;
extern struct termios					g_termios;
extern struct termios					g_termios_backup;
extern struct s_screen					g_sc;
extern struct s_term					g_term;
extern const struct s_termcaps_string	g_tc_strings[];
extern int								g_dumb_term;

int		init_terminal(void);
void	rl_set_signals(void);
void	rl_clear_signals(void);
void	resize_terminal(int signo);
void	initialize(void);

#endif
