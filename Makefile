NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra -fsanitize=address

RM = rm -rf

SRCS = 	pipex.c\
		pipex_utils.c\
		pipex_split.c\
		pipex_paths.c\
		pipex_libft1.c\
		pipex_libft2.c\
		pipex_libft3.c\

$(NAME) :
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)


all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all