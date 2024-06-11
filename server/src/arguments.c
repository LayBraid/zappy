/*
** EPITECH PROJECT, 2023
** server
** File description:
** arguments
*/

#include "arguments.h"

static args_t *new_args(void)
{
    args_t *args = malloc(sizeof(args_t));
    if (args == NULL)
        return NULL;

    args->port = 0;
    args->width = 0;
    args->height = 0;
    args->names = NULL;
    args->clients_nb = 0;
    args->freq = 0;
    return args;
}

static int is_args_good(args_t *args)
{
    if (args->port == 0 || args->width == 0 ||
        args->height == 0 || args->clients_nb == 0 ||
        args->names == NULL || args->freq == 0)
        return 0;
    return 1;
}

static void add_team(char ***names, const char *string)
{
    const int size = *names == NULL ? 0 : tab_len(*names);

    *names = realloc(*names, (size + 2) * sizeof(char *));
    (*names)[size] = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy((*names)[size], string);
    (*names)[size + 1] = NULL;
}

static args_t *verify_args(args_t *args)
{
    if (!is_args_good(args)) {
        free(args); return NULL;
    }
    return args;
}

args_t *parse_args(int ac, char **av)
{
    args_t *args = new_args();
    if (args == NULL) return NULL;
    char opt;
    while ((opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1)
        switch (opt) {
            case 'p': args->port = atoi(optarg); break;
            case 'x': args->width = atoi(optarg); break;
            case 'y': args->height = atoi(optarg); break;
            case 'n':
                for (int n = optind - 1; n < ac && av[n][0] != '-'; n++)
                    add_team(&args->names, av[n]);
                break;
            case 'c': args->clients_nb = atoi(optarg); break;
            case 'f': args->freq = atoi(optarg);break;
            case '?':
            default: free(args); return NULL;
        }
    return verify_args(args);
}
