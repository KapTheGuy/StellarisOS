all: startup.bin

startup_lm3s6965.o: startup_lm3s6965.c
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o startup_lm3s6965.o startup_lm3s6965.c

uart_drv.o: uart_drv.c uart_drv.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o uart_drv.o uart_drv.c

shell.o: shell.c shell.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o shell.o shell.c

calc.o: calc.c calc.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o calc.o calc.c

settings.o: settings.c settings.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o settings.o settings.c

dinfo.o: dinfo.c dinfo.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o dinfo.o dinfo.c

kernel.o: kernel.c uart_drv.h
	arm-none-eabi-gcc -c -g -mcpu=cortex-m3 -mthumb -o kernel.o kernel.c

startup_lm3s6965.elf: startup_lm3s6965.o uart_drv.o shell.o calc.o settings.o dinfo.o kernel.o
	arm-none-eabi-ld -T lm3s6965_layout.ld -o startup_lm3s6965.elf startup_lm3s6965.o uart_drv.o shell.o calc.o settings.o dinfo.o kernel.o

system.bin: startup_lm3s6965.elf
	arm-none-eabi-objcopy -O binary startup_lm3s6965.elf system.bin

run: system.bin
	qemu-system-arm -M lm3s6965evb -kernel system.bin

rundbg: system.bin
	qemu-system-arm -S -M lm3s6965evb -kernel system.bin -gdb tcp::5678 -nographic -monitor telnet:127.0.0.1:1234,server,nowait

clean:
	rm -f startup_lm3s6965.o kernel.o uart_drv.o shell.o calc.o settings.o dinfo.o startup.elf startup.bin

dump:
	arm-none-eabi-nm -n startup_lm3s6965.o
	arm-none-eabi-objdump -h startup_lm3s6965.o
	arm-none-eabi-nm -n kernel.o
	arm-none-eabi-objdump -h kernel.o
	arm-none-eabi-nm -n uart_drv.o
	arm-none-eabi-objdump -h uart_drv.o
	arm-none-eabi-nm -n shell.o
	arm-none-eabi-objdump -h shell.o
	arm-none-eabi-nm -n calc.o
	arm-none-eabi-objdump -h calc.o
	arm-none-eabi-nm -n startup_lm3s6965.elf
	arm-none-eabi-objdump -h startup_lm3s6965.elf
	arm-none-eabi-size startup_lm3s6965.elf
