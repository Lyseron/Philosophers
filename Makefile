NAME       = philo
CC         = cc
CFLAGS     = -Wall -Wextra -Werror -pthread -g

SRCS    = main.c parsing.c routine.c routine_action.c monitor.c init.c safe_print.c \
cleanup.c stop_dead.c time.c thread_creation.c stop_eat.c

OBJ_DIR = obj/
OBJS    = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))
RM      = rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re