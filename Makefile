# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/17 17:34:44 by rriyas            #+#    #+#              #
#    Updated: 2022/06/18 17:51:46 by rriyas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= fractol
CC		= gcc
RM		= rm -f
SRCS	= events.c fractal_utils.c fractal.c parse.c main.c
OBJS	= ${SRCS:.c=.o}
LIB		= minilibx_opengl_20191021/libmlx.a
CFLAGS = -Wall -Wextra -Werror

$(NAME):	${OBJS} ${LIB}
			${CC} ${CFLAGS} -I minilibx_opengl_20191021/ $(OBJS) -L minilibx_opengl_20191021/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

${LIB}:
			make -C minilibx_opengl_20191021/

all:	$(NAME)

clean:
		@${RM} ${OBJS}

fclean:	clean
		${RM} fractol

re:		fclean all

.PHONY: all clean fclean re
