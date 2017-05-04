# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alelievr <alelievr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/04 19:22:36 by alelievr          #+#    #+#              #
#    Updated: 2017/05/03 20:38:58 by yalaouf          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

#	Sources
SRCDIR		=	src
SRC			=	btree/btree_apply_infix.c	\
				btree/btree_apply_prefix.c	\
				btree/btree_apply_suffix.c	\
				btree/btree_create_node.c	\
				list/ft_lstadd.c	\
				list/ft_lstdel.c	\
				list/ft_lstdelone.c	\
				list/ft_lsteadd.c	\
				list/ft_lstiter.c	\
				list/ft_lstmap.c	\
				list/ft_lstnew.c	\
				list/ft_lstsplit.c	\
				list/ft_print_list.c	\
				math/aliase.c	\
				math/cmp_float.c	\
				math/ft_abs.c	\
				math/ft_factorial.c	\
				math/ft_pow.c	\
				math/ft_sqrt.c	\
				math/new_matrix.c	\
				math/rgb.c	\
				print/ft_aputstr.c	\
				print/ft_putascii.c	\
				print/ft_putchar.c	\
				print/ft_putchar_color.c	\
				print/ft_putchar_fd.c	\
				print/ft_putdouble.c	\
				print/ft_putendl.c	\
				print/ft_putendl_fd.c	\
				print/ft_putlong.c	\
				print/ft_putlong_fd.c	\
				print/ft_putnbr.c	\
				print/ft_putnbr_color.c	\
				print/ft_putnbr_fd.c	\
				print/ft_putnbrpos.c	\
				print/ft_putstr.c	\
				print/ft_putstr_color.c	\
				print/ft_putstr_fd.c	\
				print/ft_putstrcpos.c	\
				print/ft_putstrcpos_fd.c	\
				print/ft_putstrpos.c	\
				string/ft_atof.c	\
				string/ft_atoi.c	\
				string/ft_atoll.c	\
				string/ft_bzero.c	\
				string/ft_convert.c	\
				string/ft_deconvert.c	\
				string/ft_itoa.c	\
				string/ft_memalloc.c	\
				string/ft_memccpy.c	\
				string/ft_memchr.c	\
				string/ft_memcmp.c	\
				string/ft_memcpy.c	\
				string/ft_memdel.c	\
				string/ft_memdup.c	\
				string/ft_memmem.c	\
				string/ft_memmove.c	\
				string/ft_memnew.c	\
				string/ft_memocc.c	\
				string/ft_memset.c	\
				string/ft_ndeconvert.c	\
				string/ft_nmatch.c	\
				string/ft_perror.c	\
				string/ft_strcapitalize.c	\
				string/ft_strcat.c	\
				string/ft_strchr.c	\
				string/ft_strclr.c	\
				string/ft_strcmp.c	\
				string/ft_strcpy.c	\
				string/ft_strcut.c	\
				string/ft_strdel.c	\
				string/ft_strdup.c	\
				string/ft_strequ.c	\
				string/ft_striter.c	\
				string/ft_striteri.c	\
				string/ft_strjoin.c	\
				string/ft_strlcat.c	\
				string/ft_strlcpy.c	\
				string/ft_strlen.c	\
				string/ft_strlowcase.c	\
				string/ft_strmap.c	\
				string/ft_strmapi.c	\
				string/ft_strmatch.c	\
				string/ft_strncat.c	\
				string/ft_strnchr.c	\
				string/ft_strncmp.c	\
				string/ft_strncpy.c	\
				string/ft_strndup.c	\
				string/ft_strnequ.c	\
				string/ft_strnew.c	\
				string/ft_strnstr.c	\
				string/ft_strrchr.c	\
				string/ft_strrev.c	\
				string/ft_strsplit.c	\
				string/ft_strsplitstr.c	\
				string/ft_strstr.c	\
				string/ft_strsub.c	\
				string/ft_strtr.c	\
				string/ft_strtrim.c	\
				string/ft_strtrimc.c	\
				string/ft_strtrstr.c	\
				string/ft_strupcase.c	\
				string/ft_tolower.c	\
				string/ft_toupper.c	\
				string/get_next_line.c	\
				utils/error.c	\
				utils/ft_exit.c	\
				utils/ft_firstocc.c	\
				utils/ft_getocc.c	\
				utils/ft_intlen.c	\
				utils/ft_intsize.c	\
				utils/ft_isalnum.c	\
				utils/ft_isalpha.c	\
				utils/ft_isascii.c	\
				utils/ft_isblank.c	\
				utils/ft_isdigit.c	\
				utils/ft_isprint.c	\
				utils/ft_ispunct.c	\
				utils/ft_isspace.c	\
				utils/ft_isupper.c	\
				utils/ft_lastocc.c	\
				utils/ft_memswap.c	\
				utils/ft_nbrocc.c	\
				utils/ft_nnbrocc.c	\
				utils/ft_ptrswap.c	\
				utils/ft_shl.c	\
				utils/ft_shr.c	\
				utils/ft_swap.c	\
				utils/m_error.c	\

#	Objects
OBJDIR		=	obj

#	Includes
INCDIR		=	./ include

#	Libraries
LIBDIR		=	libft
LIB			=	-lft

#	Output
NAME		=	libft.a
SONAME		=	libft.so

#	Compiler
CFLAGS		=	-Werror -Wall -Wextra -funroll-loops -fno-strict-aliasing #-ggdb -O2
CC			=	gcc


################
##   COLORS   ##
################

CLEAN_COLOR		=	9
CLEAN_COLOR_T	=	196
LINK_COLOR		=	47
LINK_COLOR_T	=	46
OBJ_COLOR		=	122
OBJ_COLOR_T		=	93
NORM_COLOR		=	153
NORM_COLOR_T	=	141
NORM_COLOR_ERR	=	160


#################
##    AUTO     ##
#################

SHELL		=	/bin/zsh
OBJ			=	$(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFLAG		=	$(addprefix -L,$(LIBDIR))
INCFLAG		=	$(addprefix -I,$(INCDIR))
NORME		=	$(addsuffix /*.h,$(INCDIR)) $(addprefix $(SRCDIR)/,$(SRC))

$(foreach S,$(SRC), \
	$(eval VPATH_TMP += $(SRCDIR)/$(dir $(S)) \
	))
VPATH		=	$(VPATH_TMP:./=)

disp_indent	=	for I in `seq 1 $(MAKELEVEL)`; do \
				test "$(MAKELEVEL)" '!=' '0' && printf "\t"; \
				done

exec_color	=	$(call disp_indent); \
				echo $(1)$(2) $(3) $(4) $(5) $(6) $(7) $(8) $(9) $(10)"\033[31m"; \
				$(2) $(3) $(4) $(5) $(6) $(7) $(8) $(9) $(10)

disp_title	=	$(call disp_indent); \
				echo "\033[38;5;$(2);m[  $(1) \#$(MAKELEVEL)  ]\033[0m"


#################
##  TARGETS    ##
#################

#	First target
all: $(NAME)

#	Linking
$(NAME): $(OBJ)
	@$(call disp_title,Linking,$(LINK_COLOR_T));
	@$(call exec_color, "\033[38;5;$(LINK_COLOR_T)m➤ \033[38;5;$(LINK_COLOR)m",\
		ar rc, $(NAME), $(OBJ))
	@ranlib $(NAME)

#	Objects compilation
$(OBJDIR)/%.o: %.c
	@if [ $(ALREADY_OBJ)x != xx ]; then \
		$(call disp_title,Building,$(OBJ_COLOR_T)); \
		fi
	@mkdir $(OBJDIR) 2> /dev/null || echo "" > /dev/null
	@$(call exec_color,"\033[38;5;$(OBJ_COLOR_T)m➤ \033[38;5;$(OBJ_COLOR)m",\
		$(CC), $(CFLAGS), $(INCFLAG), -o, $@, -c, $<) # <- Building command
	@$(eval ALREADY_OBJ=x)

#	Removing objects
clean:
	@if [ $(ALREADY_RM)x != xx ]; then \
		$(call disp_title,Cleaning,$(CLEAN_COLOR_T)); \
		fi
	@$(call exec_color,"\033[38;5;$(CLEAN_COLOR_T)m➤ \033[38;5;$(CLEAN_COLOR)m",\
		rm -f, $(OBJ)) # <- Cleaning objs
	@rmdir $(OBJDIR) 2> /dev/null || echo "" > /dev/null
	@$(eval ALREADY_RM=x)

#	Removing objects and exe
fclean: clean
	@if [ $(ALREADY_RM)x != xx ]; then \
		$(call disp_title,Cleaning,$(CLEAN_COLOR_T)); \
		fi
	@$(call exec_color,"\033[38;5;$(CLEAN_COLOR_T)m➤ \033[38;5;$(CLEAN_COLOR)m",\
		rm -f, $(NAME)) # <- Cleaning binary
	@$(eval ALREADY_RM=x)

$(SONAME): $(OBJ)
	@$(call disp_title,Linking,$(LINK_COLOR_T));
	@$(call exe_color, "\033[38;5;$(LINK_COLOR_T)m➤ \033[38;5;$(LINK_COLOR)m",\
		$(CC), $(CFLAGS), -shared -fPIC -o libft.so $(OBJ))

so: $(SONAME)

#	All removing then compiling
re: fclean all

#	Checking norme
norme:
	@$(call disp_title,Norme,$(NORM_COLOR_T))
	@norminette $(NORME) | sed "s/Norme/[0;1;$(NORM_COLOR_T)m➤ [0;38;5;$(NORM_COLOR)mNorme/g;s/Warning/[38;5;$(NORM_COLOR_ERR)mWarning/g;s/Error/[38;5;$(NORM_COLOR_ERR)mError/g"

run: $(NAME)
	@gcc libftprintf.a main.c
	@echo "\033[1;35;7m[  Running #$(MAKELEVEL)  ]\033[0m"
	@echo "\033[0;1;35m➤ \033[0;38;5;147m./a.out ${ARGS}\033[0m"
	@./a.out ${ARGS}

codesize:
	@cat $(NORME) |grep -v '/\*' |wc -l

coffee:
	@clear
	@echo ""
	@echo "                   ("
	@echo "	                     )     ("
	@echo "               ___...(-------)-....___"
	@echo '           .-""       )    (          ""-.'
	@echo "      .-''''|-._             )         _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "                 ("
	@echo "	                  )      ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""       )   (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "               ("
	@echo "	                  )     ("
	@echo "               ___..(.------)--....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'
	@sleep 0.5
	@clear
	@echo ""
	@echo "             (         ) "
	@echo "	              )        ("
	@echo "               ___)...----)----....___"
	@echo '           .-""      )    (           ""-.'
	@echo "      .-''''|-._      (       )        _.-|"
	@echo '     /  .--.|   `""---...........---""`   |'
	@echo "    /  /    |                             |"
	@echo "    |  |    |                             |"
	@echo "     \  \   |                             |"
	@echo "      '\ '\ |                             |"
	@echo "        '\ '|                             |"
	@echo "        _/ /\                             /"
	@echo "       (__/  \                           /"
	@echo '    _..---""` \                         /`""---.._'
	@echo " .-'           \                       /          '-."
	@echo ":               '-.__             __.-'              :"
	@echo ':                  ) ""---...---"" (                :'
	@echo "\'._                '"--...___...--"'              _.'"
	@echo '   \""--..__                              __..--""/'
	@echo "     '._     """----.....______.....----"""         _.'"
	@echo '         ""--..,,_____            _____,,..--"""'''
	@echo '                      """------"""'

.PHONY: all clean fclean re norme codesize coffee so
