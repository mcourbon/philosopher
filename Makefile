NAME 		= philo

define HEAD                                                      

  ┓ •┓       ┓     
┏┓┣┓┓┃┏┓┏┏┓┏┓┣┓┏┓┏┓
┣┛┛┗┗┗┗┛┛┗┛┣┛┛┗┗ ┛ 
┛          ┛       

endef
export HEAD

DEF_COLOR 	= \033[0;39m
YELLOW		= \033[0;93m
GREEN		= \033[0;92m
BLUE 		= \033[0;94m
CYAN		= \033[0;96m
PURPLE	 	= \033[0;35m
BOLD		= \033[1m

BG_GREEN	= \033[42m
NC			= \033[0m

CFLAGS		=	-Wall -Werror -Wextra
CC			=	cc
RM			=	rm -rf

FILES 		=	philosopher			\
				action				\
				monitor				\
				utils				\
				utils2				\

all: $(NAME)

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

HEADER_DIR = ./
HEADER = $(wildcard $(HEADER_DIR)*.h)

%.o: %.c $(HEADER) Makefile
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "\n$(BG_GREEN)philosopher successfuly compiled !$(NC)"
	@echo "$(CYAN)$(BOLD)$$HEAD$(DEF_COLOR)"
	@${CC} $(CFLAGS) $(SRCS) -I $(HEADER) -o ${NAME}

clean:
	@$(RM) $(OBJS)
	@echo "$(CYAN)philosopher object files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(MINILIBX)
	@echo "$(CYAN)3$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(CYAN)2$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(CYAN)1$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(GREEN)philosopher executable files cleaned!$(DEF_COLOR)"


re: fclean all

.PHONY: all clean fclean re