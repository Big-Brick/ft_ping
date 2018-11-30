NAME1 = ft_ping

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INC = Includes

SDIR = Srcs

SRCS1 =	\
		get_host_addr.c\
		create_socket.c\
		fill_ping_pckt.c\
		stats.c\
		sigint_handler.c\
		calculate_ping.c\
		timeval_math.c\
		read_msg_data.c\
		main.c\

SRCS1_R = $(SRCS1:%.c=$(SDIR)/%.c)

HEADERS1 = \
			ft_ping.h\

HEADERS1_R = $(HEADERS1:%.h=$(INC)/%.h)

ODIR = Objects

OBJ1 = $(SRCS1:.c=.o)

OBJ1_R = $(OBJ1:%.o=$(ODIR)/%.o)

all : $(NAME1)

$(NAME1) : $(ODIR)/ $(OBJ1_R)
	make -C Libs/libft
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1_R) Libs/libft/libft.a

.PHONY: clean1 fclean1 dfclean1 re1 clean fclean re

clean1 :
	rm -f $(OBJ1_R)

fclean1 : clean1
	rm -f $(NAME1)

re1 : fclean1 $(NAME1)

clean: clean1

fclean : fclean1
	make fclean -C Libs/libft

re : re1

norm:
	make norm -C Libs/libft
	norminette $(SRCS1_R) $(HEADERS1_R)

add:
	make add -C Libs/libft
	git add $(SRCS1_R) $(HEADERS1_R)\
			.gitignore Makefile CMakeLists.txt author

test1: $(NAME1)
	./$(NAME1) google.com.ua

$(ODIR)/ :
	mkdir -p $@

$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I Libs/libft -I $(INC)
