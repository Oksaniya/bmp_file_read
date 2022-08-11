NAME = BMP_READ

CC = gcc
FLAG = -glldb -g3 -Wall -Wextra -Werror

all: obj
	$(CC) $(FLAG) obj/main.o \
	 -o $(NAME) -glldb -fsanitize=address -g3
	@echo "\033[0;32mFillit compiled : \033[0m\033[31m$(NAME)\033[0m"	

obj:
	mkdir obj
	$(CC) $(FLAG) -c src/main.c -o obj/main.o 

clean:
	rm -fr obj/*.o
	rm -fr obj

fclean: clean
	rm -fr $(NAME)

re: fclean all

run: re
	./$(NAME) test16.bmp

debug: re
	lldb -- ./$(NAME) test16.bmp