# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcoureau <pcoureau@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 15:22:55 by pcoureau          #+#    #+#              #
#    Updated: 2021/12/02 15:38:10 by pcoureau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =			philosophers
CC =			cc
FLAGS =			-Wall -Wextra -Werror -g -pthread
# FLAGS +=		-fsanitize=thread
RM =			rm -rf
DIR_SRCS =		./srcs/
SRC =	main.c \
		errors.c \
		parsing.c \
		utils.c \
		forks.c \
		lunch.c \
		time.c \
		philos.c \
		checkargs.c \
		routine.c \
		routineii.c \
		alive.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))
OBJS =			$(SRCS:.c=.o)
COMPIL = $(FLAGS) $(OBJS)

all:			$(NAME)
				@echo "Compiled "$(NAME)" successfully!"

$(NAME) :		$(OBJS)
				@$(CC) $(COMPIL) -o $(NAME)

%.o: %.c
				@$(CC) $(FLAGS) -c $< -o $@
				@echo "Compiled "$<" successfully!"

clean:
	$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
