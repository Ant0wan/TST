/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snunes <snunes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 22:27:51 by snunes            #+#    #+#             */
/*   Updated: 2020/05/09 18:39:51 by snunes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_H
# define AVL_H

# include "ft_readline.h"

typedef struct	s_node
{
	struct s_node	*right;
	struct s_node	*left;
	char			*name;
	char			*color;
	int				length;
	int				heigth;
	int				nb_node;
}				t_node;

typedef struct	s_data
{
	int	name_l;
	int	column;
	int	row;
	int	nb_line;
	int	name_p_line;
	int	chosen_exec;
	int	nb_exec;
	int	color;
	int	first_print;
	int	last_print;
	int	compl_start;
	int	overflow;
	int	has_overflow;
	int	taken_lines;
}				t_data;

t_node			*add_node(t_node *tree, char *name, t_data *data, char *color);
void			free_node(t_node *node);
int				check_balance(t_node *node);
t_node			*balance(int balanced, t_node *node, t_node *new_node);
int				max(int a, int b);
int				heigth(t_node *node);
int				ft_node_cmp(t_node *tree, t_node *node);
char			*get_color(char *file);
t_node			*get_node(t_node *tree, int nb_node);

#endif
