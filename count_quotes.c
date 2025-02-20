/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luisfederico <luisfederico@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:47:38 by luisfederic       #+#    #+#             */
/*   Updated: 2025/02/20 10:17:10 by luisfederic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int look_quote(char *line, int i, int *num_prev, int num)
{
	int j;
	
	j = i + 1;
	*num_prev += 1;
	while(line[j] && line[j] != num)
	{
		j++;
	}
	if(line[j] == num)
	{
		*num_prev += 1;
	}
	return (j - i);
}

int tokens_count(char *line)
{
	int qs;
	int qd;
	int j;

	qs = 0;
	qd = 0;
	j = 0;
	while(line[j])
	{
		if(line[j] == '\"')
		{
			j += look_quote(line, j, &qd, '\"');
		}
		if(line[j] == '\'')
		{
			j += look_quote(line, j, &qs, '\'');
		}
	}
	if((qs > 0 && qs % 2 != 0) || (qd > 0 && qd % 2 != 0))
	{
		return(0);
	}
	return(1);
}
