SRC = src/main.c \
		src/helpers/*.c \

TARGET = scheduling
INCLUDES = includes
CFLAGS = -Wall -Wextra -Werror
all : 
	gcc $(CFLAGS) $(SRC) -o $(TARGET) -I $(INCLUDES)

clean : 
	@:	

fclean : clean
	rm -f $(TARGET)

.PHONY : all clean fclean