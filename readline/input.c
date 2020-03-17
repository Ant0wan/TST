/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 17:21:56 by abarthel          #+#    #+#             */
/*   Updated: 2020/03/09 15:29:54 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_readline.h"

_Bool	g_input_break = 0;

union u_buffer	read_key(void)
{
	union u_buffer	buffer_u;

	buffer_u.value = 0;
	read(STDIN_FILENO, buffer_u.buf, sizeof(buffer_u.buf));
	return (buffer_u);
}
