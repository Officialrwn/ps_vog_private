/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 13:31:49 by leo               #+#    #+#             */
/*   Updated: 2022/09/22 10:13:24 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/* 
**	Functions to calculate LIS (Longest increasing subsequence) numbers
**	and push non LIS nums to stack b. 
*/

static void	init_lis_stack(t_struct *st, int max, int size)
{
	t_node	*temp;
	int		num;
	int		temp_max;

	temp_max = max;
	while (size--)
	{
		num = 0;
		if (st->lis_arr.lis[size] == temp_max && temp_max > 0)
		{
			st->max = st->max + (st->lis_arr.num[size] * (temp_max == max));
			st->min = st->lis_arr.num[size];
			num = temp_max--;
		}
		else
			st->lis_arr.mean += st->lis_arr.num[size];
		temp = ft_nodenew(num);
		if (!st->lis_arr.head)
		{
			st->lis_arr.head = temp;
			st->lis_arr.tail = temp;
		}
		else
			ft_nodeadd_front(&st->lis_arr.head, temp);
	}
}

static void	non_lis_to_stackb(t_struct *st, int *n, int flag)
{
	while ((*n)--)
	{
		if (flag)
		{
			if (st->stack_b && st->stack_b->num < st->lis_arr.mean)
				rotate(st, RR, PRINT_ON);
			else
				rotate(st, RA, PRINT_ON);
			ft_nodeadd_end(&st->lis_arr.tail, ft_nodepop(&st->lis_arr.head));
		}
		else
		{
			rotate(st, RRA, PRINT_ON);
			st->lis_arr.tail = st->lis_arr.tail->prev;
			ft_nodeadd_front(&st->lis_arr.head, st->lis_arr.tail->next);
			st->lis_arr.tail->next = NULL;
		}
	}
	ft_nodedel_front(&st->lis_arr.head);
	push(st, PB, PRINT_ON);
}

static int	get_closest_non_lis(t_node *lis, int flag)
{
	t_node	*current;
	t_node	*temp;
	int		res;

	current = lis;
	res = 0;
	while (current)
	{
		temp = current;
		if (current->num == 0)
			break ;
		else if (flag)
			current = current->next;
		else
			current = current->prev;
		res++;
	}
	if (!current && temp->num != 0)
		res = -1;
	return (res);
}

static void	init_push_non_lis_to_b(t_struct *st)
{
	int	*n;
	int	left;
	int	right;

	if (st->lis_arr.size == 1)
		return ;
	while (1)
	{
		n = &left;
		left = get_closest_non_lis(st->lis_arr.head, 1);
		right = get_closest_non_lis(st->lis_arr.tail, 0) + 1;
		if (left > right)
			n = &right;
		if (left == -1)
			break ;
		non_lis_to_stackb(st, n, (left < right));
	}
}

void	get_lis_nums(t_struct *st)
{
	int	i;
	int	j;
	int	max;

	i = 0;
	j = 1;
	while (i < st->lis_arr.size)
	{
		if (st->lis_arr.num[i] < st->lis_arr.num[j])
			st->lis_arr.lis[j] = ft_max(st->lis_arr.lis[j], \
			st->lis_arr.lis[i] + 1);
		if (++i == j && j != st->lis_arr.size - 1)
		{
			i = 0;
			j++;
		}
	}
	max = st->lis_arr.lis[j];
	while (--j)
		max = ft_max(max, st->lis_arr.lis[j]);
	init_lis_stack(st, max, st->lis_arr.size);
	st->lis_arr.mean /= (st->lis_arr.size - max);
	init_push_non_lis_to_b(st);
}
