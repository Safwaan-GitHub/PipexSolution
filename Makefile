# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanoor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:38:29 by sanoor            #+#    #+#              #
#    Updated: 2024/03/13 16:35:05 by sanoor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC_UTIL_DIR = src_util
SRC_BONUS_DIR = src_bonus
OBJ_DIR = obj

INCLUDES = -Iinclude

# Regular source files
SRC_FILES = main.c pipex.c pipex_utils.c
SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

# Bonus source files
BONUS_FILES = main_bonus.c pipex_bonus.c pipex_utils_bonus.c
BONUS_SRC = $(addprefix $(SRC_BONUS_DIR)/,$(BONUS_FILES))

# Utility source files
SRC_UTIL_FILES = fd_putstr_fd.c ft_lstadd_back.c ft_split.c \
        ft_strjoin.c ft_strlen.c ft_substr.c \
        ft_free_matrix.c ft_lstclear.c ft_strdup.c \
        ft_strlcpy.c ft_strnstr.c ft_strncmp.c
SRC_UTIL = $(addprefix $(SRC_UTIL_DIR)/,$(SRC_UTIL_FILES))

# Regular object files
OBJ_FILES = $(SRC_FILES:.c=.o) $(SRC_UTIL_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

# Bonus object files
BONUS_OBJ_FILES = $(BONUS_FILES:.c=.o) $(SRC_UTIL_FILES:.c=.o)
BONUS_OBJ = $(addprefix $(OBJ_DIR)/,$(BONUS_OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

bonus: $(BONUS_OBJ)
	$(CC) $(BONUS_OBJ) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_UTIL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
