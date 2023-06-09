SRCS 		:= 	./src/main.c \
				$(wildcard ./src/helpers/*.c) \
				$(wildcard ./src/functions/*.c)

OBJS 		:= $(SRCS:.c=.o)
CC 			:= gcc
NAME 		:= scheduling
INCLUDES 	:= includes
CFLAGS 		:= -Wall -Wextra -Werror
RM			:= rm -rf


.PHONY: all clean fclean re

all: $(NAME) clean



$(NAME):  $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(NAME) created."


%.o: %.c
	@echo "Building $(NAME)..."
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all