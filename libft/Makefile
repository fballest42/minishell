# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcabezas <rcabezas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/21 09:02:58 by rcabezas          #+#    #+#              #
#    Updated: 2021/10/20 10:12:22 by rcabezas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c\
      ft_memcmp.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_strchr.c\
      ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c\
      ft_isdigit.c ft_isalnum.c ft_isascii.c\
      ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c\
	  ft_strjoin.c ft_substr.c ft_split.c ft_strtrim.c ft_itoa.c\
	  ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
	  ft_putnbr_fd.c ft_putchar.c ft_isupper.c get_next_line.c \
	  ft_numlen.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
	  ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c \
	  ft_lstsize.c ft_atof.c  get_next_line.c ft_strcmp.c ft_strcpy.c \
	  ft_putstr.c ft_realloc.c ft_strdowncase.c ft_strtok.c \
	  ft_matrixlen.c ft_strdowncase.c ft_freematrix.c ft_matrixdup.c

SRCS = $(addprefix $(SRCS_FOLDER)/, $(SRC))

RM = rm -f

CFLAGS = -Wall -Wextra -Werror

SRCS_FOLDER = srcs

INCLUDES = includes

OBJ = $(SRCS:.c=.o)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -o $@ -c $<  -I $(INCLUDES) 

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean:     clean
	@$(RM) $(NAME)

re:		fclean all
