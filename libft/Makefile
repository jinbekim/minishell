# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinbekim <jinbekim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/22 18:47:30 by jinbekim          #+#    #+#              #
#    Updated: 2021/06/15 19:46:26 by jinbekim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
INC = -I./incs/
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar
ARFLAGS = rcs

FUNC = ft_atoi ft_isalpha ft_isprint ft_toupper \
	ft_tolower ft_isascii ft_isalnum ft_isdigit \
	ft_strncmp ft_memcmp ft_bzero ft_memset \
	ft_memchr ft_memcpy ft_memmove ft_memccpy ft_strchr \
	ft_strrchr ft_strnstr ft_strlen ft_strlcpy ft_strlcat \
	ft_calloc ft_strdup ft_strjoin ft_strtrim ft_split ft_itoa \
	ft_strmapi ft_putchar_fd ft_putstr_fd ft_putendl_fd \
	ft_putnbr_fd ft_substr ft_lstnew ft_lstadd_front \
	ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone \
	ft_lstclear ft_lstiter ft_lstmap ft_isblank ft_strcmp

SRCS = $(addprefix ./srcs/, $(addsuffix .c, $(FUNC)))
OBJS = $(addprefix ./objs/, $(addsuffix .o, $(FUNC)))

./objs/%.o : ./srcs/%.c
	$(CC) $(CFLAGS) -c -o $@ $? $(INC)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(ARFLAGS) $@ $?

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : clean all

.PHONY : clean fclean re bonus
