NAME = Mini_OS.bin

# boot = ASM/Boot_Loader.asm
# entry = kernel_entry.asm
SRC = kernel.c
Kernel_DIR = Kernel/
OBJ_DIR = obj/

C_OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

kernel: $(C_OBJ) asm
	i386-elf-ld -o obj/kernel.bin -Ttext 0x1000 obj/kernel_entry.o $(C_OBJ) --oformat binary

$(OBJ_DIR)%.o: $(Kernel_DIR)%.c
	mkdir -p obj/
	i386-elf-gcc -ffreestanding -c $< -o $@

asm: ASM/Boot_Loader.asm ASM/kernel_entry.asm
	mkdir -p obj/
	nasm -f bin ASM/Boot_Loader.asm -o obj/Boot_Loader.o
	nasm -f elf ASM/kernel_entry.asm -o obj/kernel_entry.o

# cat $(ASM_OBJ) > $(NAME)

$(NAME): kernel
	cat obj/Boot_Loader.o obj/kernel.bin > $(NAME)
	qemu-system-i386 -fda $(NAME)

clean:
	rm -rf $(OBJ_DIR)
fclean:
	rm -rf $(OBJ_DIR) $(NAME)

re: fclean all