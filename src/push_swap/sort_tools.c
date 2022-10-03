/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 15:05:34 by leo               #+#    #+#             */
/*   Updated: 2022/09/12 22:51:24 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static t_op	find_optimal_correction(t_struct *st, int list_size)
{
	t_node	*current;
	t_node	*temp;
	t_op	op;
	int		count;

	current = st->stack_a;
	op = RA;
	count = 0;
	while (current)
	{
		temp = current;
		if (current->num == st->max)
			break ;
		current = current->next;
		count++;
	}
	if (count >= list_size / 2)
		op = RRA;
	return (op);
}

static int	check_push(t_struct st, int a_prev, int a_next, int b)
{
	int	res;

	res = 0;
	if (b > a_prev && b < a_next)
		res = 1;
	if (b > st.max && a_prev == st.max)
		res = 1;
	if (b < a_next && a_prev == st.max && a_next == st.min)
		res = 1;
	return (res);
}

static int	count_moves(int *min, int count, int a_count)
{
	if (*min > count || *min == 0)
	{
		if (count > a_count)
			*min = count - a_count;
		else
			*min = count;
		return (1);
	}
	return (0);
}

static void	check_from_left(t_struct st, int *a, int *b, int min)
{
	t_node	*temp;
	int		count;
	int		a_count;

	a_count = 0;
	while (st.stack_a)
	{
		count = 0 + a_count;
		temp = st.stack_b;
		while (temp)
		{
			if (check_push(st, st.tail_a->num, st.stack_a->num, temp->num)
				&& count_moves(&min, count, a_count))
			{
				*a = st.stack_a->num;
				*b = temp->num;
				break ;
			}
			count++;
			temp = temp->next;
		}
		st.tail_a = st.stack_a;
		st.stack_a = st.stack_a->next;
		a_count++;
	}
}

void	sort_list(t_struct *st, int list_size)
{
	t_op	op;
	int		a;
	int		b;

	a = st->stack_a->num;
	if (st->stack_b)
	{
		b = st->stack_b->num;
		check_from_left(*st, &a, &b, 0);
		while (st->stack_a->num != a || st->stack_b->num != b)
		{
			if (st->stack_a->num == a)
				rotate(st, RB, PRINT_ON);
			else if (st->stack_b->num == b)
				rotate(st, RA, PRINT_ON);
			else
				rotate(st, RR, PRINT_ON);
		}
		check_push_conditions(st);
		push(st, PA, PRINT_ON);
		sort_list(st, list_size);
	}
	op = find_optimal_correction(st, list_size);
	while (!check_if_sorted(st))
		rotate(st, op, PRINT_ON);
}
