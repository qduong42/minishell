/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljahn <ljahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:25:47 by ljahn             #+#    #+#             */
/*   Updated: 2022/07/25 10:45:11 by ljahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Takeing care of symbolic links

void	init_pipex(t_vars *vars, t_pipe *cmd, t_list **env_lst)
{
	vars->outfile = 66; // INITALIZATION
	vars->carry = 0;//INFILE
	if (cmd->fd_in > 2)
		vars->carry = cmd->fd_in;
	vars->env = lst_to_strstr(*env_lst); // FORMATING -- freed
}

void	pipex(t_pipe *cmd, t_list **env_lst)
{
	t_vars		vars;

	init_pipex(&vars, cmd, env_lst);
	while (cmd)// Execution loop
	{
		if (while_stroke(&cmd, &vars, env_lst))
			continue ;
		assign_outfile(&vars, cmd);
		if (!vars.pid)
		{
			duping(&vars, cmd);
			if (is_buildin(cmd))
				exit(exec_buildin(cmd, env_lst)); // DOES NOT WORK AS INTENDED.
			else if (execve(vars.path, cmd->argv, vars.env))
			{
				perror("execve()");
				exit(127);
			}
		}
		aftershave(&vars, &cmd);
	}
	close_free(&vars);
}
