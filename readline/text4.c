/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:13:58 by abarthel          #+#    #+#             */
/*   Updated: 2020/05/26 10:18:20 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

void	wd_left(void)
{
	while (g_line.c_pos > 0 && g_line.line[g_line.c_pos - 1] == ' ')
		cursor_l();
	while (g_line.c_pos > 0 && g_line.line[g_line.c_pos - 1] != ' ')
		cursor_l();
	if (g_vim_mode && --g_vim_cmd_count > 0 && g_line.c_pos > 0)
		wd_left();
}

void	clear_scr(void)
{
	if (g_dumb_term)
	{
		clear_line();
		ft_putchar_fd('\n', g_dis.fd);
		return ;
	}
	ft_putstr_fd(g_termcaps.clrpag, g_dis.fd);
	g_dis.start_offset = 0;
	display_prompt();
	g_line.is_modified = 1;
	place_cursor(0);
}

void	rl_void(void)
{
	ft_putstr_fd(g_termcaps.bl, g_dis.fd);
}

void	paste_via_input(unsigned long v)
{
	union u_buffer	u;
	int				len;

	len = 0;
	u.value = v;
	while (len < 8 && u.buf[len])
		++len;
	insert_text(&(u.buf[0]), len, 1);
}

void	clear_eol(void)
{
	if (g_line.c_pos != g_line.len)
	{
		g_clip.l = g_line.len - g_line.c_pos;
		if (g_clip.str != NULL)
			free(g_clip.str);
		g_clip.str = ft_strndup(&(g_line.line[g_line.c_pos]), g_clip.l);
		add_back();
		ft_bzero(&(g_line.line[g_line.c_pos]), g_clip.l);
		g_line.len -= g_clip.l;
		g_line.is_modified = 1;
		update_line();
	}
}
