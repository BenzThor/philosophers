# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpochlau <bpochlau@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/01/24 14:19:20 by bpochlau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME			= philosophers

GREEN			= \033[0;32m
RED				= \033[0;31m
RESET			= \033[0m

LIBFT 			= ./libraries/libft/libft.a

CC 				= cc

CFLAGS 			= -Wall -Werror -Wextra -g

REMOVE 			= rm -f
REMOVE_DIR		= rm -rf

INC_DIR			= ./inc
SRCS_DIR		= ./sources
OBJDIR			= ./objs

HEADER			= $(addprefix $(INC_DIR)/,\
				minishell.h)

SRCS 			= $(addprefix $(SRCS_DIR)/,\
					philosophers.c)

OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJDIR)/%.o)

all:			${LIBFT} ${NAME}

$(OBJDIR)/%.o: $(SRCS_DIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

${NAME}:		${LIBFT} $(HEADER) $(OBJS)
				${CC} ${OBJS} ${LIBFT} ${CFLAGS} ${LRL} -o ${NAME}
				@echo "$(NAME): $(GREEN)$(NAME) was compiled.$(RESET)"
				@echo

${LIBFT}:
				@echo
				make all -C libraries/libft

clean:
				make clean -C libraries/libft
				${REMOVE_DIR} ${OBJDIR}
				@echo

fclean:
				${REMOVE} ${NAME}
				make fclean -C libraries/libft
				${REMOVE_DIR} ${OBJDIR}
				@echo "${NAME}: ${RED}${NAME} and libft.a were deleted${RESET}"
				@echo

re:				fclean all

test:			${LIBFT} $(HEADER)
				${CC} -g $(SRCS) ${LIBFT} ${LRL} -o ${NAME}

valgrind:		$(NAME)
				valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
				--show-mismatched-frees=yes	--track-fds=yes ./${NAME}

.PHONY:			all clean fclean re valgrind
