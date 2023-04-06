CC = c++ -Wall -Wextra -Werror -std=c++98

SRC =  main.cpp parsing.cpp parsing1.cpp send.cpp parsing2.cpp parsing_request.cpp

NAME = webserv

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -f $(NAME) 

fclean: clean	
	rm -f $(NAME) 

re : fclean all