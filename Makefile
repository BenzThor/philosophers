# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thorben <thorben@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/01/31 09:54:18 by thorben          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME			= philosophers

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

CC 				= cc

CFLAGS 			= -Wall -Werror -Wextra -g

REMOVE 			= rm -f
REMOVE_DIR		= rm -rf

INC_DIR			= ./inc
SRCS_DIR		= ./sources
OBJDIR			= ./objs

HEADER			= $(addprefix $(INC_DIR)/,\
				philosophers.h)

SRCS 			= $(addprefix $(SRCS_DIR)/,\
					exit.c \
					init.c \
					input_check.c \
					philosophers.c \
					utils.c \
					utils_write.c)

all:			${NAME}

OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

${NAME}:		$(HEADER) $(OBJS)
				${CC} ${OBJS} ${CFLAGS} -o ${NAME}
				@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"
				@echo

clean:
				${REMOVE_DIR} ${OBJDIR}
				@echo

fclean:
				${REMOVE} ${NAME}
				${REMOVE_DIR} ${OBJDIR}
				@echo "${NAME}: ${RED}${NAME} was deleted${RESET}"
				@echo

re:				fclean all

test:			$(HEADER)
				${CC} -g $(SRCS) -o ${NAME}

valgrind:		$(NAME)
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
				--show-mismatched-frees=yes	--track-fds=yes ./${NAME}

.PHONY:			all clean fclean re valgrind
