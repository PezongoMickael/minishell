/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:13 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/07 18:41:47 by rel-fila         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lst_clear_parsing(t_parsing **lst)
{
	t_parsing	*t;
	t_parsing	*tmp;

	if (!lst)
		return ;
	t = *lst;
	while (t)
	{
		tmp = t->next;
        if (t->words[0])
            free_arg(t->words);
        free(t->words);
        free(t);
		t = tmp;
	}
	*lst = NULL;
}

void update_envp_var(t_envp **envp)
{
    t_envp *node;

    node = *envp;
    while (node)
    {
        if (!ft_strncmp(node->name, "?", 1))
        {
            free(node->content);
            node->content = ft_strdup("258");
        }
        node = node->next;
    }
}

void start_treatment(char *line, t_parsing **parsings, t_envp **envp)
{
    t_lexer *lexer;

    if (!check_spaces(line))
    {
        add_history(line);
        if (!check_line(line))
        {
            lexer = expand(line, envp);
            if (!check_lexer_list(lexer))
            {
                gather_words(lexer);
                // while (lexer)
                // {
                //     printf("%s | %d\n", lexer->str, lexer->category);
                //     lexer = lexer->next;
                // }
                parsing(&lexer, parsings, envp);
                execute(*envp, *parsings);
                // while (*parsings)
                // {
                //     i = 0;
                //     printf("out : %d | in : %d\n", (*parsings)->out_file, (*parsings)->in_file);
                //     while ((*parsings)->words[i])
                //         printf("str : %s\n", (*parsings)->words[i++]);
                //     (*parsings)= (*parsings)->next;
                // }
            }
            else
                update_envp_var(envp);
            free_lexer(&lexer);
            if (*parsings != NULL)
			{
				ft_lst_clear_parsing(parsings);
				*parsings = NULL;
			}
        }
        else
            printf("Quotes error\n");
    }
    else if (check_spaces(line))
        add_history(line);
}

void start_shell(t_envp **envp, t_parsing **parsings)
{
    char *line;

    while (1)
    {
        line = readline(PROMPT);
        if (!line)
        {
            printf("%s\n", EXIT_MSG);
            exit(0);
        }
        if (line[0])
            start_treatment(line, parsings, envp);
        // int i = 0;
        // while (*parsings)
        // {
        //     printf("Parsing %d\n", i);
        //     int j = 0;
        //     while ((*parsings)->words && (*parsings)->words[j])
        //     {
        //         printf("%s \n", (*parsings)->words[j]);
        //         j++;
        //     }
        //     printf("in_file = %d | out_file = %d\n", (*parsings)->in_file, (*parsings)->out_file);
        //     (*parsings) = (*parsings)->next;
        //     i++;
        // }
        free(line);
    }
}