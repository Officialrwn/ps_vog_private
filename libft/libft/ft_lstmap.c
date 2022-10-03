/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:10:38 by leotran           #+#    #+#             */
/*   Updated: 2022/02/08 01:32:11 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_delcontent(void *content, size_t contentsize)
{
	if (content != NULL)
	{
		free(content);
		content = NULL;
	}
	contentsize = 0;
}

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return (NULL);
	temp = ft_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
	if (!temp)
		return (NULL);
	head = temp;
	while (lst->next != NULL)
	{
		lst = lst->next;
		temp->next = ft_lstnew((*f)(lst)->content, (*f)(lst)->content_size);
		if (!temp->next)
		{
			ft_lstdel(&head, &ft_delcontent);
			return (NULL);
		}
		temp = temp->next;
	}
	return (head);
}
