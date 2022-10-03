/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 00:49:08 by leo               #+#    #+#             */
/*   Updated: 2022/10/03 14:39:29 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	initialize_struct(t_struct *st)
{
	st->op_list = NULL;
	st->stack_a = NULL;
	st->stack_b = NULL;
	st->tail_a = NULL;
	st->tail_b = NULL;
	st->argv = NULL;
	st->argc = 0;
	st->min = 0;
	st->max = 0;
}

int	validate_argv(t_struct *st, char *argv)
{
	t_node	*current_node;
	t_node	*temp;
	long	num;

	current_node = st->stack_a;
	num = ft_atol(argv);
	if ((num == 0 && ft_strcmp(argv, "0") != 0) || num > MAXINT || num < MININT)
		print_on_exit(st, ERROR, PRINT_ON);
	while (current_node)
	{
		if (current_node->num == num)
			print_on_exit(st, ERROR, PRINT_ON);
		current_node = current_node->next;
	}
	temp = ft_nodenew(num);
	if (!st->stack_a)
	{
		st->stack_a = temp;
		st->tail_a = temp;
	}
	else
		ft_nodeadd_end(&st->tail_a, temp);
	return (num);
}

int	check_if_sorted(t_struct *st)
{
	t_node	*current;
	int		flag;

	flag = 1;
	current = st->stack_a;
	if (st->stack_a)
	{
		while (current->next)
		{
			if (current->num > current->next->num)
				flag = 0;
			current = current->next;
		}
	}
	return (flag);
}

char	**init_str_argv(t_struct *st, char *str, int *argc)
{
	char	**argv;
	char	**temp;

	if (ft_strchr(str, ' ') == NULL)
		exit(0);
	argv = ft_strsplit(str, ' ');
	temp = argv;
	*argc = 1;
	while (*(temp++))
		(*argc)++;
	st->argc = *argc;
	st->argv = argv;
	return (argv);
}

int	check_push_conditions(t_struct *st)
{
	int	res;

	res = 0;
	if (st->stack_b->num < st->stack_a->num
		&& st->stack_b->num > st->tail_a->num)
		res = 1;
	if (st->stack_b->num > st->max && st->stack_a->num == st->min)
	{
		res = 1;
		st->max = st->stack_b->num;
	}
	if (st->stack_b->num < st->stack_a->num && st->stack_a->num == st->min)
	{
		res = 1;
		st->min = st->stack_b->num;
	}
	return (res);
}
