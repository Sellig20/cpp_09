NAME					=		pmergeme

SRCS					=		main.cpp \

OBJS		= ${SRCS:.cpp=.o}

CC			= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g3
RM			= rm -f

all: 		${NAME}

.cpp.o:
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o}

$(NAME):	$(OBJS)
			${CC} $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS)

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all