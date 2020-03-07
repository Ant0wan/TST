/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 18:08:48 by abarthel          #+#    #+#             */
/*   Updated: 2019/10/21 18:08:50 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_str_is_alpha(char *s)
{
	if (!*s)
		return (1);
	while ((*s >= 97 && *s <= 122) || (*s >= 65 && *s <= 90))
	{
		++s;
		if (!*s)
			return (1);
	}
	return (0);
}
