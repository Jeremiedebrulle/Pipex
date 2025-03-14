# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdebrull <jdebrull@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/31 14:58:16 by jdebrull          #+#    #+#              #
#    Updated: 2025/03/14 20:53:28 by jdebrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCDIR = srcs
OBJDIR = objs
LIBFTDIR = libft
CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(LIBFTDIR)
LIBFT = -L$(LIBFTDIR) -lft

SRCS = $(addprefix $(SRCDIR)/, main.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

NAME = pipex

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR)/libft.a
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFTDIR)/libft.a $(LIBFT)

$(LIBFTDIR)/libft.a:
	@$(MAKE) --no-print-directory -C $(LIBFTDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFTDIR) fclean

re: fclean all
