##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME	=	empire

SRCS	=	src/main.c			\
			src/empire.c		\

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-std=gnu17 -W -Wall -Wextra -Werror -g3

all:	$(NAME)

$(NAME):	$(OBJS) $(SRCS)
		gcc -o $(NAME) $(OBJS) $(CFLAGS) -L./include -lempire -lpthread

clean:
		rm -rf $(OBJS)

fclean:		clean
		rm -rf $(NAME)
		find -name "*.o" -delete
		find -name "*.gc*" -delete
		find -name "*~" -delete

re: fclean all clean
