/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpezongo <mpezongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 17:54:29 by mpezongo          #+#    #+#             */
/*   Updated: 2023/08/06 17:54:30 by mpezongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_spaces(char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if (line[i] != 32 && (line[i] > 13 || line[i] < 9))
            return (0);
    }
    return (i);
}