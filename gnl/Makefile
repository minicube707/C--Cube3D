# =======================================
#            MAKEFILE PROJET
# =======================================

# =======================================
#                FLAGS
# =======================================
CC = cc -Wall -Wextra -Werror -MMD -MP


# =======================================
#              FILE
# =======================================
FILE_NAMES =	get_next_line \
				get_next_line_utils



# =======================================
#              VARIABLE
# =======================================	
SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include

SRC_FILES = $(FILE_NAMES:%=$(SRC_PATH)/%.c)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)
HEA_FILES = $(HEA_PATH)/get_next_line.h

INCLUDE = -I $(HEA_PATH)
NAME = libgnl.a

# =======================================
#              RULES
# =======================================
.PHONY: all clean fclean re

all : $(NAME)


$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEA_FILES) | $(OBJ_PATH)
	$(CC) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJ_FILES)
	ar rcs $(NAME) $(OBJ_FILES)


clean :
	rm -f $(OBJ_FILES) $(DEP_FILES)
	rm -rf $(OBJ_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

# Inclusion automatique des fichiers .d s’ils existent
-include $(DEP_FILES)
