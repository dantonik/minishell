/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dantonik <dantonik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:03:54 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/27 01:36:21 by dantonik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(t_head *head)
{
	char	*pwd;
	int		len;

	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd != NULL)
	{
		len = ft_strlen(pwd);
		write(1, pwd, len);
		write(1, "\n", 1);
		free(pwd);
		head->e_s = 0;
		return (0);
	}
	head->e_s = 1;
	return (1);
}