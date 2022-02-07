CC		=	gcc

CFLAGS	= 	-Wall -Wextra -Werror -g

OBJDIR	=	objs
SRCDIR	=	srcs

NAME	=	philo_bonus

SRC		=	main.c \
			check_data.c \
			ft_atoi.c \
			print.c \
			philo.c \
			utils.c \
			time.c

SRC		:=	$(addprefix $(SRCDIR)/, $(SRC))
OBJ		=	$(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(SRC:.c=.o))

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(NAME)

$(OBJ):		$(OBJDIR)

$(OBJDIR):
			mkdir $(OBJDIR)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c ./includes/philo_b.h
			$(CC) $(CFLAGS) -I ./includes -c $< -o $@

clean:
			rm -rf $(OBJDIR)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re