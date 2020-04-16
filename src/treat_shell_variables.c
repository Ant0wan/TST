/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_shell_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 13:54:08 by abarthel          #+#    #+#             */
/*   Updated: 2020/04/16 13:54:10 by abarthel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static char	**tab_remove_first_elem(int *ac, char **av)
{
	char	**new_tab;
	int		i;

	i = 0;
	new_tab = NULL;
	if (*ac > 1)
	{
		new_tab = (char**)malloc(sizeof(char*) * *ac);
		if (new_tab == NULL)
			return (NULL);
		while (i + 1 < *ac)
		{
			new_tab[i] = ft_strdup(av[i + 1]);
			i++;
		}
		new_tab[i] = NULL;
	}
	ft_free_tab(*ac, &av);
	(*ac)--;
	return (new_tab);
}

int			set_shell_var(t_list *elem, char *name, char *value)
{
	extern t_list	*g_env;
	t_list			*lst_new;
	t_shell_var		shell_var;

	ft_bzero(&shell_var, sizeof(shell_var));
	if (elem != NULL)
	{
		((t_shell_var*)(elem->content))->value = value;
		((t_shell_var*)(elem->content))->flag |= SET;
	}
	else
	{
		shell_var.name = name;
		shell_var.value = value;
		shell_var.flag |= SET;
		lst_new = ft_lstnew(&shell_var, sizeof(shell_var));
		if (lst_new == NULL)
			return (FAILURE);
		ft_lstadd(&g_env, lst_new);
	}
	return (SUCCESS);
}

int			treat_shell_variables(t_process *p)
{
	t_list			*elem;
	char			*name;
	char			*value;

	if (!p->argv[0])
		return (0);
	while (p->argv != NULL && (value = is_valid_assignment(p->argv[0])))
	{
		name = ft_strndup(p->argv[0], value - p->argv[0]);
		value = ft_strdup(value + 1);
		elem = get_shell_var(name, g_env);
		if (!name || !value || set_shell_var(elem, name, value) == FAILURE)
			return (FAILURE);
		p->argv = tab_remove_first_elem(&p->argc, p->argv);
	}
	ft_merge_sort(&g_env, &alpha_sort);
	return (SUCCESS);
}
