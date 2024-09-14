# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: etaattol <etaattol@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/09/15 00:44:54 by etaattol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= 	minishell

FLAGS		=	-Wall -Wextra -Werror -g -I. #-fsanitize=address

SRCFILES 	= 	main.c \

				executor/executor.c \
				executor/fd_closer.c \
				executor/file_redirections.c \
				executor/path_solver.c \
				executor/pipe_executor.c \
				executor/redirection_executor.c \
				
				lexer/env_expander.c \
				lexer/lexer.c \
				lexer/token_utils.c \

				parser/command_parser.c \
				parser/heredoc_handler.c \
				parser/open_files.c \
				parser/parser.c \
				parser/redirection_handler.c \
				
				builtins/builtin_handler.c \
				builtins/export_unset.c \
				builtins/handle_cd.c \
				builtins/handle_echo.c \
				builtins/handle_env.c \
				builtins/handle_exit.c \
				builtins/handle_pwd.c \

				utils/data_manager.c \
				utils/env_utils_ops.c \
				utils/env_utils.c \
				utils/error_handler.c \
				utils/heredoc_status.c \
				utils/memory_utils_array.c \
				utils/memory_utils.c \
				utils/signal_handler.c \
				utils/string_utils.c \
				utils/terminal_configuration.c \

				signal/signal_handler.c \
				
SRCDIR		=	srcs
PIPEDIR		=	pipes_are_calling
OBJDIR		=	objs

HEADER		=	minishell.h

LIBFT_DIR	=	./libft
LIBFT		=	$(LIBFT_DIR)/libft.a

SRCS		=	$(addprefix $(SRCDIR)/, $(SRCFILES)) \

PSRCS		=	$(addprefix $(PIPEDIR)/, $(PIPEFILES))

OBJS		= 	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS)) \
				$(patsubst $(PIPEDIR)/%.c, $(OBJDIR)/%.o, $(PSRCS))

ANSI_CYAN 	:= 	\033[0;36m
ANSI_BLUE 	:= 	\033[0;34m
ANSI_RED 	:= 	\033[31m
ANSI_RESET 	:= 	\033[0m

all: 			$(NAME)

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HEADER) 
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(OBJDIR)/%.o:	$(PIPEDIR)/%.c $(HEADER)
				@mkdir -p $(OBJDIR)
				@cc $(FLAGS) -o $@ -c $<

$(NAME):		$(OBJS) $(LIBFT)
				@cc $(HEADERS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
				@echo "$(ANSI_CYAN)Compilation Complete: $(NAME) $(ANSI_RESET)"

$(LIBFT):		
				@make -C $(LIBFT_DIR)
				@echo "$(ANSI_CYAN)LIBFT Compiled! $(ANSI_RESET)"

clean:
				@rm -rf $(OBJDIR)
				@rm -f $(PIPEDIR)/*.o   #this is useless i Think#
				@make -C $(LIBFT_DIR) clean
				@echo "$(ANSI_RED)Objects and LIB_FT Cleaned$(ANSI_RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@make -C $(LIBFT_DIR) fclean
				@echo "$(ANSI_RED)Executable $(NAME) removed$(ANSI_RESET)"

re:				fclean all
