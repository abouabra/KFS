NAME = mini_os.bin

ASM_FILES = Boot_Loader.asm Print_ASCII.asm Load_Disk.asm
OBJ_DIR = obj/

ASM_OBJ = $(addprefix $(OBJ_DIR), $(ASM_FILES:.asm=.o))

all: $(NAME)

asm: $(ASM_OBJ)
	cat $(ASM_OBJ) > $(NAME)
$(OBJ_DIR)%.o: %.asm
	mkdir -p $(OBJ_DIR)
	nasm -f bin $< -o $@ 

$(NAME): asm
	qemu-system-i386 -fda $(NAME)

clean:
	rm -rf $(OBJ_DIR)
fclean:
	rm -rf $(OBJ_DIR) $(NAME)

re: fclean all