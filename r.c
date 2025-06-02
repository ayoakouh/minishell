/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoakouh <ayoakouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:33:44 by ayoakouh          #+#    #+#             */
/*   Updated: 2025/06/02 15:27:22 by ayoakouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>
char *check_path(t_env **list)
{
    t_env *tmp;

    if (!list || !*list)
        return (NULL);
        
    tmp = *list;
    while (tmp)
    {
        if (!ft_strcmp(tmp->key, "PATH"))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    ft_free_split(char **str)
{
    int i = 0;

    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}
void    check_directory(t_cmd *cmd)
{
    struct stat err;
    if(stat(cmd->args[0], &err) == 0)
    {
        if (S_ISDIR(err.st_mode)) {
            write(2, "minishell: ", 11);
            write(2, cmd->args[0], ft_strlen(cmd->args[0]));
            write(2, ": is a directory\n", 17);
            cmd->data.exit_status = get_or_set(SET, 126);
            exit(126);
        }
    }
    else if(chdir(cmd->args[0]) == -1)
    {
        if (errno == 20)
        {
            write(2, "minishell: ", 11);
            write(2, cmd->args[0], ft_strlen(cmd->args[0]));
            write(2, ": Not a directory\n", 18);
            cmd->data.exit_status = get_or_set(SET, 126);
            exit(126);
        }
    }
}

void wait_for_children(t_cmd *cmd, pid_t child_pid)
{
    int status;

    status = 0;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    waitpid(child_pid, &status, 0);
    cmd->data.exit_status = WEXITSTATUS(status);
        if (WIFSIGNALED(status))
        {
            int sig = WTERMSIG(status);
            if (sig == SIGQUIT)
            {
                ft_putstr_fd("Quit: 3\n", 1);
                cmd->data.exit_status = get_or_set(SET, 128 + sig);
            }
            else if (sig == SIGINT)
            {
                ft_putstr_fd("\n", 1);
                cmd->data.exit_status = get_or_set(SET, 128 + sig);
            }
            else
                cmd->data.exit_status = get_or_set(SET, 0);
        }
}
void check_is_deroctory(t_cmd *cmd)
{
    int fd = open(cmd->args[0], O_DIRECTORY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: ", 2);
        write(2, cmd->args[0], ft_strlen(cmd->args[0]));
        cmd->data.exit_status = get_or_set(SET, 1);
        ft_putstr_fd(": Not a directory\n", 2);
        exit(1);
    }
    else
        close(fd);
}
void ft_print_error(t_cmd *cmd)
{
    ft_putstr_fd("minishell: ", 2);
    write(2, cmd->args[0], ft_strlen(cmd->args[0]));
    if(errno == 2)
    {
        ft_putstr_fd(": No such file or directory\n", 2);
        cmd->data.exit_status = get_or_set(SET, 127);
        exit(127);
    }
    else if(errno == 13)
    {
        cmd->data.exit_status = get_or_set(SET, 126);
        ft_putstr_fd(": Permission denied\n", 2);
        exit(126);
    }
    else if(errno == 21)
    {
        cmd->data.exit_status = get_or_set(SET, 126);
        ft_putstr_fd(": Is a directory\n", 2);
        exit(126);
    }  
}
void handle_absolute_path(t_cmd *cmd, char **help)
{
    pid_t child_pid;
    int status = 0;
    child_pid = fork();
    if (child_pid == 0)
    {
         check_directory(cmd);
        if(access(cmd->args[0], X_OK) == 0)
        {
            execve(cmd->args[0], cmd->args, help);
            cmd->data.exit_status = get_or_set(SET, 0);
            exit(0);
        }
        else
        {
            ft_print_error(cmd);
        }
    }
    else if (child_pid > 0)
    {
        wait_for_children(cmd, child_pid);
    }
    else
    {
        perror("fork");
        exit(0);
    }
}

void ft_execute_path_command(t_cmd *cmd, char **env_array, char **split_path)
{
    char *tmp;
    char *helper;
    int i = 0;
    while (split_path[i])
    {
        tmp = ft_strjoin(split_path[i], "/");
        helper = ft_strjoin(tmp, cmd->args[0]);
        free(tmp);
        if (!helper)
        {
            i++;
            continue;
        }
        if(!(access(helper, X_OK) == -1))
        {
            execve(helper, cmd->args, env_array);
            cmd->data.exit_status = get_or_set(SET, 0);
        }
        free(helper);
        i++;
    }
    write(2, "minishell: ", 11);
    write(2, cmd->args[0], ft_strlen(cmd->args[0]));
    write(2, ": command not found\n", 20);
    ft_free_split(split_path);
    cmd->data.exit_status = get_or_set(SET, 127);
    exit(127);
}

void restart_setting_term()
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void desable_echo_term()
{
    struct termios term;
    tcgetattr(1, &term);
	term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
void ft_excute_commands(t_cmd *cmd, t_env **env_list)
{
    char **env_doble;
    char *path;
    char **split_path;
    pid_t child_pid;
    split_path = NULL;
    struct termios infos;
    struct termios term;

    env_doble = convert_env_list(env_list);
    if(!cmd->args || !cmd->args[0])
        return ;
    if(ft_strchr(cmd->args[0], '/'))
    {
            handle_absolute_path(cmd, env_doble);
            return ;
    }
    child_pid = fork();
    if(child_pid == 0)
    {
        restart_setting_term();
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        path = check_path(env_list);
        if(!path)
        {
            if(ft_strcmp(cmd->args[0], "..") == 0)
            {
                write(2, "minishell: ", 11);
                write(2, cmd->args[0], ft_strlen(cmd->args[0]));
                write(2, ": is a directory\n", 17);
                cmd->data.exit_status = get_or_set(SET, 126);
                exit(126);
            }     
            if(access(cmd->args[0], X_OK) != -1)
            {
                execve(cmd->args[0], cmd->args, env_doble);
                exit(0);
            }
            else
            {
                ft_print_error(cmd);
            }
        }
        else
        {
            split_path = ft_split(path, ':');
            if (!split_path)
                return ;
            ft_execute_path_command(cmd, env_doble, split_path);
            ft_free_split(split_path);
        }
    }
    else if(child_pid > 0)
    {
        wait_for_children(cmd, child_pid);
    }
    else if(child_pid < 0)
    {
        perror("fork failed");
        ft_free_split(split_path);
    }
}
