# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbrahm <aelbrahm@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/26 17:56:39 by aelbrahm          #+#    #+#              #
#    Updated: 2023/07/31 07:58:59 by aelbrahm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#================================#
#         COLORS                 #
#================================#
BLU = \033[34;1m
CYN = \033[36;1m
PRP = \033[35;1m
GRN = \033[32;1m 
RED = \033[31;1m
YLW = \033[33;1m
C_CLS = \033[0m

#================================#
#         GLOBAL_VARIABLE        #
#================================#

FLAGS =	-g -pthread  
# -fsanitize=thread 
RM =	rm -rf

#================================#
#         GLOBAL_VARIABLE        #
#================================#
SRCS = $(shell ls src | grep -E ".+\.c")
OBJS_O = $(SRCS:.c=.o)
NAME = bin/Philo
OBJS = $(addprefix obj/, $(OBJS_O))
dir = bin obj
INCLU = Include/philo.h

#================================#
#            RULES               #
#================================#	

all : $(NAME)

$(NAME) : $(dir) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(dir) : 
	mkdir -p $(dir)
	
obj/%.o : src/%.c $(INCLU)
	@printf "|[ $(GRN)%-37s$(C_CLS)$(YLW) ]| \r" "Compailing... $(notdir $@)"
	@$(CC) $(FLAGS) -c $< -o $@

#====================================================================#
clean :
	$(RM) obj
	printf "[ $(RED)%-30s$(C_CLS) ]\n" "Objects file got cleaned successfuly ❌"
	sleep 1
fclean : clean
	$(RM) $(dir)
	printf "[ $(RED)%-30s$(C_CLS) ]\n" "Executable & Archives got removed successfuly ❌"
re : fclean all
.SILENT : $(NAME) $(dir) clean fclean