NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CCFLAGS = -Wall -Wextra -Werror
SRC = pipex.o utils.o utils2.o
SRC_BONUS = bonus/pipex_bonus.o bonus/utils_bonus.o bonus/utils2_bonus.o bonus/utils3_bonus.o  bonus/get_next_line_bonus.o bonus/get_next_line_utils_bonus.o
OBJS_BONUS := $(SRC_BONUS:%.c=%.o)


all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CCFLAGS) -o $(NAME) $(SRC)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CCFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

.o:.c
	$(CC) $(CCFLAGS) -c $< -o $@ 

clean:
	rm -f $(SRC) $(SRC_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: clean all

.PHONY: all bonus clean fclean
