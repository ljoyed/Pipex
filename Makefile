NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	pipex.c\
		pipex_utils.c\

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all