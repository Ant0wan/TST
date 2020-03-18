/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yforeau <yforeau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 01:41:05 by yforeau           #+#    #+#             */
/*   Updated: 2018/10/09 01:41:10 by yforeau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_glob_utils.h"

t_list	*ft_lst_at(t_list *lst, unsigned int nbr)
{
	while (lst && nbr-- > 0)
		lst = lst->next;
	return (lst);
}
