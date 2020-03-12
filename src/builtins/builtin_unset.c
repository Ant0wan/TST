/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efischer <efischer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 08:32:50 by efischer          #+#    #+#             */
/*   Updated: 2020/03/12 10:28:56 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char		**get_name_tab(int ac, char **av)
{
	char	*err;
	char	**tab;
	size_t	i;

	i = 0;
	tab = (char**)malloc(sizeof(char*) * (ac + 1));
	if (tab != NULL)
	{
		while (av[i] != NULL)
		{
			if (ft_strchr(av[i], '=') != NULL)
			{
				ft_asprintf(&err, "unset: `%s': not a valid identifier", av[i]);
				ft_putendl_fd(err, 2);
				ft_free_tab(i, &tab);
				break ;
			}
			else
				tab[i] = ft_strdup(av[i]);
			i++;
		}
	}
	if (tab != NULL)
		tab[i] = NULL;
	return (tab);
}

static int		match_name(char *var_name, char **name)
{
	int		ret;
	size_t	i;

	i = 0;
	ret = FALSE;
	while (name[i] != NULL)
	{
		if (ft_strequ(var_name, name[i]) == TRUE)
		{
			ret = TRUE;
			break ;
		}
		i++;
	}
	return (ret);
}

static void		remove_first_var(char **name)
{
	extern t_list	*g_env;
	t_list			*head;

	head = g_env;
	while (g_env != NULL && match_name(((t_shell_var*)(g_env->content))->name,
		name) == TRUE)
	{
		head = g_env->next;
		ft_lstdelone(&g_env, &del_elem);
		g_env = head;
	}
}

static void		unset_var(char **name)
{
	extern t_list	*g_env;
	t_list			*head;
	t_list			*tmp;

	remove_first_var(name);
	head = g_env;
	tmp = g_env;
	g_env = g_env->next;
	while (g_env != NULL)
	{
		if (match_name(((t_shell_var*)(g_env->content))->name, name) == TRUE)
		{
			tmp->next = g_env->next;
			ft_lstdelone(&g_env, &del_elem);
			g_env = tmp->next;
		}
		else
		{
			tmp = g_env;
			g_env = g_env->next;
		}
	}
	g_env = head;
}

int				cmd_unset(int ac, char **av)
{
	int		ret;
	char	**name;

	ret = SUCCESS;
	if (ft_getopt(ac - 1, av, "") == FALSE)
	{
		ft_putendl_fd("unset: usage: unset [arg ...]", 2);
		ret = FAILURE;
	}
	name = get_name_tab(ac - 1, av + 1);
	if (name != NULL)
	{
		unset_var(name);
		ft_free_tab(ft_tablen(name), &name);
	}
	return (ret);
}
