NAME = Mini_OS.bin

Kernel_SRC = kernel.c
Driver_SRC = ports.c screen.c keyboard.c
CPU_SRC = idt.c isr.c timer.c
MEM_SRC = kmalloc.c

Kernel_DIR = Kernel/
DRIVER_DIR = Drivers/
CPU_DIR = CPU/
MEM_DIR = Memory/

OBJ_DIR = obj/

C_OBJ = $(addprefix $(OBJ_DIR), $(Kernel_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(Driver_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(CPU_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(MEM_SRC:.c=.o))

FLAGS = -Werror

all: $(NAME)

kernel: $(C_OBJ) asm
	make -C libft
	echo $(C_OBJ)
	i386-elf-ld -o obj/kernel.bin -Ttext 0x1000 obj/kernel_entry.o $(C_OBJ) obj/interrupt.o libft/libft.a --oformat binary

$(OBJ_DIR)%.o: $(Kernel_DIR)%.c
	mkdir -p obj/
	i386-elf-gcc $(FLAGS) -ffreestanding -c $< -o $@

$(OBJ_DIR)%.o: $(DRIVER_DIR)%.c 
	mkdir -p obj/
	i386-elf-gcc $(FLAGS) -ffreestanding -c $< -o $@


$(OBJ_DIR)%.o: $(CPU_DIR)%.c 
	mkdir -p obj/
	i386-elf-gcc $(FLAGS) -ffreestanding -c $< -o $@

$(OBJ_DIR)%.o: $(MEM_DIR)%.c 
	mkdir -p obj/
	i386-elf-gcc $(FLAGS) -ffreestanding -c $< -o $@

asm: ASM/Boot_Loader.asm ASM/kernel_entry.asm CPU/interrupt.asm
	mkdir -p obj/
	nasm -f bin ASM/Boot_Loader.asm -o obj/Boot_Loader.o
	nasm -f elf ASM/kernel_entry.asm -o obj/kernel_entry.o
	nasm -f elf CPU/interrupt.asm -o obj/interrupt.o

$(NAME): kernel
	cat obj/Boot_Loader.o obj/kernel.bin > $(NAME)
	qemu-system-i386 -fda $(NAME)
	

clean:
	make -C libft clean
	rm -rf $(OBJ_DIR)
fclean:
	make -C libft fclean
	rm -rf $(OBJ_DIR) $(NAME)

re: fclean all