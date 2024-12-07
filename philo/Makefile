# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=thread

LIBFT_DIR = /home/azubieta/sgoinfre/azubieta/Utils/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(LIBFT_DIR)

SRC_DIR = ./src
SRCS = philo.c\
		$(SRC_DIR)/philo_utils.c\
		$(SRC_DIR)/philo_threads.c\
		$(SRC_DIR)/philo_lifecycle.c\
		$(SRC_DIR)/philo_init.c\
		$(SRC_DIR)/philo_clean.c\

OBJ_DIR = ./objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = philo

#OBJ_DIR_BONUS = ./objs_bonus
#BONUS_DIR = ./src
#BONUS_SRCS = $(BONUS_DIR)/bonus/pipex_bonus.c\
			$(BONUS_DIR)/ft_execute.c\
			$(BONUS_DIR)/ft_process.c\
			$(BONUS_DIR)/ft_utils.c\

#BONUS_OBJS = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(OBJ_DIR_BONUS)/%.o)

#BONUS_NAME = pipex_bonus

# Colors
RED     			= \033[0;31m
GREEN   			= \033[0;32m
YELLOW  			= \033[0;33m
CYAN    			= \033[0;36m
WHITE   			= \033[0;37m
RESET   			= \033[0m

# Reglas
all: $(NAME)

#bonus: $(BONUS_NAME)

#$(BONUS_NAME): $(OBJ_DIR_BONUS) $(LIBFT) $(BONUS_OBJS)
#	@printf "$(CYAN)[Building Bonus] Creating $(BONUS_NAME)...\n$(RESET)"
#	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS_NAME)
#	@printf "$(GREEN)[Success] $(BONUS_NAME) created successfully!\n$(RESET)"

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	@printf "$(CYAN)[Building Main] Creating $(NAME)...\n$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)[Success] $(NAME) created successfully!\n$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "$(YELLOW)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#$(OBJ_DIR_BONUS)/%.o: $(BONUS_DIR)/%.c | $(OBJ_DIR_BONUS)
#	@mkdir -p $(dir $@)
#	@printf "$(YELLOW)[Compiling Bonus]$(RESET) $<\n"
#	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@printf "$(CYAN)[Directory] Creating object directory $(OBJ_DIR)...\n$(RESET)"
	@mkdir -p $(OBJ_DIR)

#$(OBJ_DIR_BONUS):
#	@printf "$(CYAN)[Directory] Creating bonus object directory $(OBJ_DIR_BONUS)...\n$(RESET)"
#	@mkdir -p $(OBJ_DIR_BONUS)

$(LIBFT):
	@printf "$(CYAN)[Building Libft] Compiling libft...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
#	@$(MAKE) -C $(LIBFT_DIR) bonus
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "$(GREEN)[Libft Ready] Libft compiled successfully!\n$(RESET)"

clean:
	@printf "$(RED)[Cleaning] Removing object files...\n$(RESET)"
	@rm -rf $(OBJ_DIR)
#	@rm -rf $(OBJ_DIR_BONUS)
	@printf "$(GREEN)[Cleaned] Object files removed successfully!\n$(RESET)"

fclean: clean
	@printf "$(RED)[Full Clean] Removing binaries and $(LIBFT)...\n$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
#	@rm -f $(BONUS_NAME)
	@printf "$(GREEN)[Cleaned] All binaries and libraries removed successfully!\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus