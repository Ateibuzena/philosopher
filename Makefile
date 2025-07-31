# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDES = -I$(LIBFT_DIR)

SRC_DIR = ./src
SRCS = philo.c\
		$(SRC_DIR)/philo_utils.c\
		$(SRC_DIR)/philo_threads.c\
		$(SRC_DIR)/philo_lifecycle.c\
		$(SRC_DIR)/philo_init.c\
		$(SRC_DIR)/philo_clean.c\
		$(SRC_DIR)/philo_monitor.c\
		$(SRC_DIR)/ft_strtol.c\
		$(SRC_DIR)/ft_atoi.c\

OBJ_DIR = ./objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = philo

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus