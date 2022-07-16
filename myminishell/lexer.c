#include "minishell.h"

// LEXER


void	int_red(t_shell *s)
{
	t_pipe	*temp;

	temp = s->s_p;
	while (temp)
	{
		int		i;
		char	*string;
		i = 0;
		int quote = 0;
		string = temp->sub;
		// printf("SUBPIPE_STRING:%s\n", string);
		int in = 0;
		// int start = 0;
		// int out = 0;
		while (string[i])
		{
			if (!quote)
			{
				if (string[i] == IN)
				{
					if (!ft_strncmp(&string[i], HD, 2) && !in)
					{
						i++;
						// ft_putstr_fd("HEREDOC\n", 1);
						string = iohandler(temp, i, 3);
						i = -1;
						in = 1;
					}
					else if (!in)
					{
						string = iohandler(temp, i, 1);
						i = -1;
						// ft_putstr_fd("INPUT\n", 1);
					}
				}
				else if (string[i] == OUT)
				{
					// printf("string%d:%c\n", i, string[i]);
					if (!ft_strncmp(&string[i], AP, 2))
					{
						i++;
						string = iohandler(temp, i, 4);
						i = -1;
						// ft_putstr_fd("APPEND\n", 1);
					}
					else /* if (!out) */
					{
						string = iohandler(temp, i, 2);
						i = -1;
						// ft_putstr_fd("OUTPUT\n", 1);
					}
				}
				else if (string[i] == S_Q || string[i] == D_Q)
					quote = string[i];
			}
			else if (quote && (!string[i] || string[i] == quote))
				quote = 0;
			i++;
		}
		temp = temp->next;
	}
}

void	pipe_handle(t_shell *s, int *start, int i)
{
	char *token;
	char *temp;
	token = ft_substr(s->input, *start, i - *start);
	temp = ft_strtrim(token, " ");
	free(token);
	token = temp;
	ft_plstadd_back(&(s->s_p), ft_plstnew(token));
	*start = i + 1;
}

void	pipe_split(t_shell *s)
{
	int	i;
	int	quote;
	int start;

	i = 0;
	start = 0;
	quote = 0;
	while (1)
	{
		if ((s->input[i] == PIPE && !quote) || s->input[i] == '\0')
		{
			pipe_handle(s, &start, i);
			if (s->input[i] == '\0')
				break ;
		}
		else if ((s->input[i] == S_Q || s->input[i] == D_Q) && !quote)
			quote = s->input[i];
		else if (quote && (!(s->input[i]) || s->input[i] == quote))
			quote = 0;
		i++;
	}
}

//add_history functionality is built in, so further work required.