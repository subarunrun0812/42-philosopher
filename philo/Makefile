# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: susasaki <susasaki@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 12:38:11 by susasaki          #+#    #+#              #
#    Updated: 2023/04/14 12:29:14 by susasaki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = 	src/main.c\
		src/init.c \
		src/errors.c \
		src/arg_check.c \
		src/death_check.c \
		src/output_philo_doing.c \
		src/philo_doing.c \
		src/philo.c \
		src/time.c \
		src/dead_flag.c\
		src/ft_atoll.c\

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(OBJS)

clean :
	$(RM) $(OBJS)
	$(RM) $(NAME)

re : fclean all