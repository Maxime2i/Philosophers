# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlangloi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/02 16:07:17 by mlangloi          #+#    #+#              #
#    Updated: 2023/07/15 17:04:12 by mlangloi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -Wall -Wextra -Werror
SRC = main.c utils.c philo_init.c philo_time.c philo_routine.c philo_init2.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -pthread $(OBJ) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re:	fclean all



