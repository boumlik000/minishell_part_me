#/!bin/bash

cc pipe.c -L../includes/libft/ -lft -lreadline -g3 -fsanitize=address -o pipe