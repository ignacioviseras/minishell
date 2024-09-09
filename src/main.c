/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drestrep <drestrep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:18:27 by drestrep          #+#    #+#             */
/*   Updated: 2024/09/09 18:28:33 by drestrep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(void)
{
	char *line;

	while(1)
	{
		minishell();
		line = readline("Ingresa una línea de texto: ");
		add_history(line);
		if(line != NULL)
			printf("La línea ingresada es: %s\n", line);
		else
		{
			printf("Line == NULL\n");
			break;
		}
		rl_on_new_line();
	}
	return 0;
}
