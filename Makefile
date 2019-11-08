CC = g++ -Wall -Wextra -Werror
NAME = expertsystem

SRCS_PATH = src

SRCS_NAME = checkRules.cpp \
            expertSystem.cpp \
            main.cpp \
            ruleChecking.cpp \
            rules.cpp \
            toolRules.cpp \
            toolSystemExpert.cpp


SRCS = $(addprefix $(SRCS_PATH)/,$(SRCS_NAME))

INCLUDES_NAME = ExpertSystem.h \
                Rules.h

OBJS_NAME = $(SRCS:.c=.o)

.PHONY: all, clean, fclean, re, norme

all: $(NAME)

$(NAME): $(OBJS_NAME)
    @echo "\033[32 Compiling!\033[0m"
    $(CC) $(SRCS) -o $(NAME)
    #ln  -s  $(NAME) $(LINK_NAME)
    #@mv $(OBJS_NAME) $(SRCS_PATH)

clean:
    @rm -f $(OBJS_NAME)
    @echo "\033[32;2m Cleaned successfully!\033[0m"

fclean: clean
    @rm -f $(NAME)
    @echo "\033[32;2m Fcleaned successfully!\033[0m"

re: fclean all

norme: fclean
    @norminette $(SRCS) $(INCLUDES_NAME)
    @echo "\033[1;34m expertSystem\t\033[1;33mNorminette\t\033[0;32m[OK]\033[0m"
