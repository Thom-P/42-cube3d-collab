#gcc -Wall -Wextra -I../include/ -L../libft/ -L../minilibx_macos/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -fsanitize=address -o cube

gcc -O2 -Wall -Wextra -Werror -Wconversion -I../include/ -L../libft/ -L../minilibx_macos/ -lmlx -lft -framework OpenGL -framework AppKit *.c -o cube

#Using leaks
#export MallocStackLogging=1 #to allow line finding
#unset MallocStackLogging #to remove 
#gcc -Wall -Wextra -Werror -O0 -I../include/ -L../libft/ -L../minilibx_macos/ -lmlx -lft -framework OpenGL -framework AppKit *.c -g -o cube
#leaks --atExit --list -- ./cube toto
#nb: leaks only detect lost pointers to allocated mem, blocks that for sure can no longer be freed, does not detect alloc but not freed memory
