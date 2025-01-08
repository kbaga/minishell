// #include "minishell.h"

// t_pid_list *init_pid_list(void)
// {
//     t_pid_list *list = malloc(sizeof(t_pid_list));
//     if (!list)
//     {
//         perror("Error: malloc failed");
//         exit(EXIT_FAILURE);
//     }
//     list->pids = malloc(sizeof(pid_t) * 10);
//     if (!list->pids)
//     {
//         perror("Error: malloc failed");
//         free(list);
//         exit(EXIT_FAILURE);
//     }
//     list->count = 0;
//     list->capacity = 10;
//     return (list);
// }

// void add_pid(t_pid_list *list, pid_t pid)
// {
//     if (list->count >= list->capacity)
//     {
//         list->capacity *= 2;
//         pid_t *new_pids = realloc(list->pids, sizeof(pid_t) * list->capacity);
//         if (!new_pids)
//         {
//             perror("Error: realloc failed");
//             free(list->pids);
//             free(list);
//             exit(EXIT_FAILURE);
//         }
//         list->pids = new_pids;
//     }
//     list->pids[list->count++] = pid;
// }

// void wait_all_pids(t_pid_list *list)
// {
//     for (size_t i = 0; i < list->count; i++)
//     {
//         if (waitpid(list->pids[i], NULL, 0) == -1)
//         {
//             perror("Error: waitpid failed");
//         }
//     }
// }

// void free_pid_list(t_pid_list *list)
// {
//     if (list)
//     {
//         free(list->pids);
//         free(list);
//     }
// 	list = NULL;
// }

// // int main(void)
// // {
// //     t_pid_list *pid_list = init_pid_list();
// //     for (int i = 0; i < 5; i++)
// //     {
// //         pid_t pid = fork();
// //         if (pid == -1)
// //         {
// //             perror("Error: fork failed");
// //             free_pid_list(pid_list);
// //             exit(EXIT_FAILURE);
// //         }
// //         if (pid == 0)
// //         {
// //             printf("Child process %d\n", getpid());
// //             exit(0); // Child process exits immediately
// //         }
// //         else
// //         {
// //             add_pid(pid_list, pid);
// //         }
// //     }

// //     wait_all_pids(pid_list);
// //     free_pid_list(pid_list);
// //     printf("All child processes have been waited for.\n");
// //     return 0;
// // }