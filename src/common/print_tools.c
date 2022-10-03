/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 19:12:47 by leo               #+#    #+#             */
/*   Updated: 2022/10/03 14:41:20 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	print_on_exit(t_struct *st, int flag, int print_flag)
{
	if (print_flag)
	{
		if (flag)
			write(2, "Error\n", 6);
		else if (check_if_sorted(st) && !st->stack_b)
			write(1, "OK\n", 3);
		else
			write(1, "KO\n", 3);
	}
	else
	{
		ft_nodedel(&st->lis_arr.head);
		free(st->lis_arr.lis);
		free(st->lis_arr.num);
		st->lis_arr.lis = NULL;
		st->lis_arr.num = NULL;
	}
	if (st->argc > 0)
		free_argv(st->argv, st->argc);
	ft_nodedel(&st->stack_a);
	ft_nodedel(&st->stack_b);
	ft_lstdel(&st->op_list, &ft_del_lst_content);
	exit(flag);
}

void	free_argv(char **argv, int argc)
{
	if (argc > 0)
	{
		while (argc--)
		{
			if (argv[argc])
				free(argv[argc]);
		}
		free(argv);
		argv = NULL;
	}
}
