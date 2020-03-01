/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/01 17:07:44 by abarthel          #+#    #+#             */
/*   Updated: 2020/02/12 13:55:33 by efischer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "error.h"

const struct s_tags	g_tags[] =
{
	{"${", &parameter_expansions, "}"},
	{"$", &parameter_expansions, ""},
	{"~", &tilde_expansion, ""},
	{"\0", NULL, NULL}
};

static int	expansion_dispatcher(char *str, int tilde)
{
	int	i;
	int	ref;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	ref = -1;
	while (*(g_tags[i].opentag))
	{
		if (!tilde && !ft_strcmp("~", g_tags[i].opentag))
			break; /* Stop expansions on tilde if tilde not required */
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
		{
			closest = ptr;
			ref = i;
		}
		++i;
	}
	return (ref);
}

static char	*get_closest_exp(char *str, int tilde)
{
	int		i;
	char	*ptr;
	char	*closest;

	i = 0;
	closest = NULL;
	while (*(g_tags[i].opentag))
	{
		if (!tilde && !ft_strcmp("~", g_tags[i].opentag))
			break; /* Stop expansions on tilde if tilde not required */
		ptr = ft_strstr(str, g_tags[i].opentag);
		if (ptr && (!closest || (ptr < closest && closest)))
			closest = ptr;
		++i;
	}
	return (closest);
}

static int		replace_expansion(char **token, char **next, int ref)
{
	static size_t	index;
	char			*new;
	size_t			lnew;
	size_t			lprefix;
	int				ret;

	ret = e_success;
	if (*token == *next)
		index = 0;
	lprefix = (size_t)((*next) - (*token));
	if (!(ret = g_tags[ref].f(&index, next, g_tags[ref].opentag, g_tags[ref].closetag)))
	{
		lnew = lprefix + ft_strlen(*next);
		new = (char*)ft_memalloc(sizeof(char) * (lnew + 1));
		ft_strncat(new, *token, lprefix);
		ft_memdel((void**)token);
		ft_strcat(new, *next);
		ft_memdel((void**)next);
		*next = &(new)[index + lprefix];
		*token = new;
		return (e_success);
	}
	return (ret);
}

int			treat_single_exp(char **str, int tilde)
{
	int	ref;
	int	ret;
	char	*next;

	next = *str;
	while ((next = get_closest_exp(next, tilde)))
	{
		ref = expansion_dispatcher(next, tilde);
		if ((ret = replace_expansion(str, &next, ref)))
		{
			psherror(ret, *str, e_cmd_type);
			return (ret);
		}
	}
	return (e_success);
}

/*
int			treat_expansions(char **tokens)
{
	int	i;
	int	ret;

	i = 0;
	if (!tokens)
		return (e_invalid_input);
	while (tokens[i])
	{
		ret = treat_single_exp(&tokens[i]);
		if (ret)
			return (ret);
		++i;
	}
	return (e_success);
}
*/


//int			treat_expansions(t_list *lst)
//{
//	int		ref;
//	int		ret;
//	char	*next;
//
//	if (((t_token*)(lst->content))->type != START)
//		return (e_invalid_input);
//	lst = lst->next;
//	/* Tokens might be wrong, strsplit is not ok fpor instance "echo ${LOGNAME }KO" does not work*/
//	/*ft_print_tables(tokens);
//	exit(1);
//*/	/* END debugg */
//	while (((t_token*)(lst->content))->type != END)
//	{
//		next = ((t_token*)(lst->content))->value;
//		if (next != NULL)
//		{
//			while ((next = get_closest_exp(next)))
//			{
//				ref = expansion_dispatcher(next);
//				if ((ret = replace_expansion(&((t_token*)(lst->content))->value,
//						&next, ref)))
//				{
//					psherror(ret, ((t_token*)(lst->content))->value, e_cmd_type);
//					return (ret);
//				}
//			}
//		}
//		lst = lst->next;
//	}
//	return (e_success);
//}
//
//int			expansions(t_ast *ast)
//{
//	int		ret;
//
//	ret = SUCCESS;
//	while (ast != NULL)
//	{
//		if (ast->content != NULL)
//			ret = treat_expansions(ast->content);
//		else if (ast->left != NULL && ((t_ast*)(ast->left))->content != NULL)
//			ret = treat_expansions(((t_ast*)(ast->left))->content);
//		if (ret != e_success)
//			break ;
//		ast = ast->right;
//	}
//	return (ret);
//}
