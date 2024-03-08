# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanoor <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 17:38:29 by sanoor            #+#    #+#              #
#    Updated: 2024/03/08 19:06:06 by sanoor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
SRC_UTIL_DIR = src_util
OBJ_DIR = obj

INCLUDES = -Iinclude

SRC_FILES = main.c pipex.c pipex_utils.c
SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

SRC_UTIL_FILES = fd_putstr_fd.c ft_lstadd_back.c ft_split.c \
	ft_strjoin.c ft_strlen.c ft_substr.c \
	ft_free_matrix.c ft_lstclear.c ft_strdup.c \
	ft_strlcpy.c ft_strnstr.c
SRC_UTIL = $(addprefix $(SRC_UTIL_DIR)/,$(SRC_UTIL_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o) $(SRC_UTIL_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR)/,$(OBJ_FILES))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_UTIL_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) -r $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re

