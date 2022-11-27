/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:12:26 by dantonik          #+#    #+#             */
/*   Updated: 2022/11/27 06:26:14 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
	{
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "  \b\b", 4);
}

static int	check_empty_input(char *input)
{
	int	i;

	i = 0;
	while (1)
	{
		if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
			i++;
		else
			break ;
	}
	if (input[i] == '\0')
		return (1);
	else
		return (0);
}

int	inner_loop(t_head *head, t_env_head *env_head, char *input)
{
	input = NULL;
	input = readline(MINISHELL);
	if (!input)
		return (-1);
	if (check_empty_input(input))
		return (free (input), 0);
	else
		add_history(input);
	input = expander(input, env_head);
	if (check_empty_input(input))
		return (printf("trash: invalid input!\n"), free(input), 0);
	head->length = 0;
	head->temp_fd = -1;
	head->envp_ours = env_head;
	create_list(&head, input);
	check_builtins(head);
	main_loop(head, env_head);
	free(input);
	free_list_loop(&head);
	return (0);
}

t_head	*init_head(char **argv)
{
	t_head	*head;

	(void) argv;
	return (head = (t_head *)ft_calloc(1, sizeof(t_head)), \
	head->std_input[1] = dup(0), head->std_output[1] = dup(1), head);
}

char	**path_str(t_env_head *envp)
{
	char		**paths;
	t_env_node	*current;
	int			i;

	paths = ft_calloc(envp->length, sizeof(char *));
	i = 0;
	current = envp->head;
	while (current != NULL)
	{
		paths[i] = ft_strjoin(current->key, current->value);
		current = current->next;
		i++;
	}
	paths[i] = NULL;
	return (paths);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_head		*head;
	t_env_head	*env_head;

	if (argc != 1)
		return (printf("trash: %s: No such file or directory\n", argv[1]), \
			EXIT_FAILURE);
	if (envp == NULL || envp[0] == NULL)
		return (printf("trash: send the environment please!\n"), EXIT_FAILURE);
	head = init_head(argv);
	env_head = init_envs(envp, head);
	if (head == NULL)
		exit(1);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (1)
		if (inner_loop(head, env_head, input) == -1)
			break ;
	if (input)
		free (input);
	system("leaks minishell");
	return (close(head->std_input[1]), close(head->std_output[1]), \
	free_list_loop(&head), free_list_env(&env_head), free(head), \
	free(env_head), rl_clear_history(), 0);
}
