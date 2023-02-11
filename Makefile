# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/03 16:25:18 by nkietwee          #+#    #+#              #
#    Updated: 2023/02/11 13:12:22 by nkietwee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
SRCS	= ft_pipex.c\
		ft_pipex_util.c\
		ft_split.c\
		ft_strjoin.c\
		ft_strlen.c\
		ft_strtrim.c\
		ft_putstr_fd.c\
		ft_find_substring.c


CC = cc -Wall -Wextra -Werror
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%o: %c
	$(CC) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	# $(CC)  $(NAME) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all  clean fclean re
