#include "pipex.h"


char *get_env_path(char **env, char *cmd)
{
    int i;
    char *path_var;
    char **paths;
    char *temp;

    i = 0;
    while (ft_strncmp("PATH", env[i], 4) != 0)
        i++;
    paths = ft_split(env[i] + 5, ':');
    i = 0;
    while (paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        temp = paths[i];
        paths[i] = ft_strjoin(paths[i], cmd);
        free(temp);
        //printf("path %d: %s\n", i, paths[i]); OK
        if (access(paths[i], F_OK) == 0)
            return (paths[i]); ///DAR FREE NA HIGH FUNC
        free(paths[i]);
        i++;
    }
    free(paths);
    return (NULL);
}






int main(int ac, char **av, char **env)
{

    char * s;
    if (ac != 5)
    {
        printf("Error.\n Argumentos\n");
        return (0);
    }
    s = get_env_path(env, av[2]);//PEGA O CAMINHO CORRETO DO COMANDO

    printf("-------%s", s);

    return (0);
}