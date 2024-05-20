#include "minishell.h"

int	is_arg_numeric(char *arg)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] != '\0')
	{
		if (i == 0 && (arg[i] == '-' || arg[i] == '+'))
			i++;
		if (ft_isdigit(arg[i]) == 0)
			return (0);
		i++;
	}
	
	len = ft_strlen(arg);
	if ((arg[0] == '-' || arg[0] == '+') && len > 20)
		return (0);
	else if ((arg[0] != '-' && arg[0] != '+') && len > 19)
		return (0);

	if (arg[0] == '-' && len == 20 && ft_atoi(arg) == 0 && arg[19] != '8')
		return (0);
	else if (arg[0] == '+' && len == 20 && ft_atoi(arg) == -1 && arg[19] != '7')
		return (0);
	else if (len == 19 && ft_atoi(arg) == -1 && arg[18] != '7')
		return (0);

	return (1);
}

int	ft_exit(t_env_lst *env_lst, t_data *data, char **args)
{
	int	count;
	int	exit_status;

	ft_putendl_fd("exit", 2); // this doesn't appear if exit is piped, example: echo hello | exit --> WEIRD
	if (args[0] == NULL)
	{
		free_env_lst(env_lst);
		ft_free_data(data, 0);
		exit(0);
	}
	else if (is_arg_numeric(args[0]) == 0)
	{
		write_error("exit", args[0], "numeric argument required");
		free_env_lst(env_lst);
		ft_free_data(data, 0);
		exit(255);
	}
	count = 0;
	while (args[count] != NULL)
		count++;
	if (count > 1)
		return (write_error(NULL, "exit", "too many arguments"));
	exit_status = ft_atoi(args[0]) % 256;
	free_env_lst(env_lst);
	ft_free_data(data, 0);
	exit(exit_status);
}