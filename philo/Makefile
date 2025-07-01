NAME= philo
CC = cc
FLAGS= -Wall -Wextra -Werror

SRC= cleanup.c helpers1.c  herpers2.c initializing_tools.c initializing.c input_validation.c philo.c printing.c 
HEADER = philo.h
OBJ=$(SRC:.c=.o)


all: $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
