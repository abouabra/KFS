CFLAGS= -Wall -Wextra -Werror -ffreestanding -c 
LDFLAGS=-melf_i386 -T ../conf/link.ld 
ASFLAGS=-felf

Kernel_SRC = main.c
Driver_SRC = ports.c screen.c
CPU_SRC =
MEM_SRC =

Kernel_DIR = Kernel/
DRIVER_DIR = Drivers/
CPU_DIR = CPU/
MEM_DIR = Memory/
OBJ_DIR = ../obj/

C_OBJ = $(addprefix $(OBJ_DIR), $(Kernel_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(Driver_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(CPU_SRC:.c=.o))
C_OBJ += $(addprefix $(OBJ_DIR), $(MEM_SRC:.c=.o))


all: $(C_OBJ) asm link
	@bash -c "cd ../conf && ./update_image.sh"
	@qemu-system-i386 -fda ../conf/floppy.img

asm: ASM/boot.asm
	@mkdir -p $(OBJ_DIR)
	@nasm $(ASFLAGS) $< -o ../obj/boot.o

link:
	@make -C libft > /dev/null
	@i386-elf-ld $(LDFLAGS) -o ../obj/kernel ../obj/boot.o $(C_OBJ) libft/libft.a


$(OBJ_DIR)%.o: $(Kernel_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@i386-elf-gcc $(CFLAGS) -ffreestanding -c $< -o $@

$(OBJ_DIR)%.o: $(DRIVER_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@i386-elf-gcc $(CFLAGS) -ffreestanding -c $< -o $@


$(OBJ_DIR)%.o: $(CPU_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	i386-elf-gcc $(CFLAGS) -ffreestanding -c $< -o $@

$(OBJ_DIR)%.o: $(MEM_DIR)%.c 
	@mkdir -p $(OBJ_DIR) 
	i386-elf-gcc $(CFLAGS) -ffreestanding -c $< -o $@

fclean:
	@make -C libft fclean > /dev/null
	@rm -rf $(OBJ_DIR)

re: fclean all