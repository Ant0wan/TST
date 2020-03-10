/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:22:31 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/10 12:44:32 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

int	g_hist_lookup_value = 1;

static void	readline_internal_keys(union u_buffer c, char **value)
{
	while (c.value)
	{
		if (g_hist_lookup_value == 1)
			c = read_key();
		else
		{
			c.value = g_hist_lookup_value;
			g_hist_lookup_value = 1;
		}
		if (enter_rc(c))
			return ;
		if (isstdkey(c.value))
			(g_emacs_standard_keymap[c.value].func)(c.value);
		else if (isctrlkey(c))
		{
			if (mvctrlkey(c))
				c.buf[2] = c.buf[5] + 20;
			(g_emacs_ctlx_keymap[(int)c.buf[2]].func)();
		}
		else if (ismetachar(c))
			return ;
		else
			paste_via_input(c.value);
		*value = g_line.line;
	}
}

static char	*readline_internal(void)
{
	char			*value;

	value = NULL;
	init_line_buffer();
	value = g_line.line;
	update_line();
	readline_internal_keys((union u_buffer){.value = 1}, &value);
	return (value);
}

char		*ft_readline(const char *prompt)
{
	char	*value;

	value = NULL;
	prep_terminal();
	if (!g_hist)
		init_history();
	initialize();
	set_prompt(prompt);
	rl_set_signals();
	while (!value)
	{
		value = readline_internal();
		if (value && value[0] && (value = hist_expanse(value)))
		{
			add_hentry(value, 1);
			break ;
		}
	}
	deprep_terminal();
	rl_clear_signals();
	if (value != NULL)
		ft_putchar_fd('\n', 2);
	return (value);
}
