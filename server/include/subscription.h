/*
** EPITECH PROJECT, 2023
** server
** File description:
** No file there , just an epitech header example
*/

#ifndef SUBSCRIPTION_H_
    #define SUBSCRIPTION_H_

    #include "inc.h"
    #include "socket.h"
    #include "circular_buff.h"

    #define SUB_SIZE 10

typedef struct client_s client_t;


subscription_t *new_subscription(char *metadata);
void subscribe(subscription_t *list, client_t **new_sub);
void delete_subscription(subscription_t *sub, client_t *to_delete);

void broadcast(subscription_t *sub, char *msg);


/* ### CIRC BUFF ### */
bool write_circular_buff(circular_buff_t *buff, char *str);

#endif /* SUBSCRIPTION_H_ */
