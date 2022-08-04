/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qduong <qduong@students.42wolfsburg.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:39:33 by qduong            #+#    #+#             */
/*   Updated: 2022/08/04 11:06:09 by qduong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/**
 * modified plstnew function to work with t_pipe lists. initialises nodes  
 * @param content [void *] subpipe string char *
 * @param fd_in -2 is used because -1 is used for open error
 * @return t_pipe* returns node to subpipe
 */
t_pipe	*ft_plstnew(void *content, t_shell *s)
{
	t_pipe	*new;
	// static t_pipe	*first = NULL;
	// static int		top = 1;

	new = malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	// if (top)
	// 	first = new;
	new->sub = content;
	new->argv = NULL;
	new->fd_in = -2;
	new->fd_out = -2;
	new->hd = NULL;
	new->hd_fd = -2;
	new->last = 0;
	new->next = NULL;
	new->main = s;
	// new->top = first;
	// top = 0;
	// printf("TOP:%p\n", new->top);
	return (new);
}

void	ft_plstadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*current;

	current = *lst;
	if (lst)
	{
		if (*lst)
		{
			while (current -> next != NULL)
			{
				current = current -> next;
			}
			current -> next = new;
		}
		else
			*lst = new;
	}
}
