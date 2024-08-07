OBJECTS =  hello.o 
#CROSS   = riscv64-unknown-elf
CROSS   = aarch64-linux-gnu
CC      = $(CROSS)-gcc-10.2.0
AS      = $(CROSS)-as-10.2.0
LD      = $(CROSS)-ld-10.2.0
OBJDUMP = $(CROSS)-objdump-10.2.0
LIB_DIR = -Llibfemtorv -L/home/$$USER/miniconda3/envs/fpga/riscv32-elf/lib/rv32i/ilp32/ \
          -L/home/$$USER/miniconda3/envs/fpga/lib/gcc/riscv32-elf/10.1.0/rv32iac/ilp32/
LIBS    = -lfemtorv -lm -lc -lgcc
LDFLAGS = -m elf32lriscv -b elf32-littleriscv --no-relax --print-memory-usage -Tlinker.ld
AFLAGS  = -march=rv32i -mabi=ilp32
CFLAGS  =  -Ilibfemtorv/include -Ilibfemtoc/include -fno-pic -march=rv32i -mabi=ilp32 -fno-stack-protector -w -Wl,--no-relax
OBJCOPY = $(CROSS)-objcopy
all: firmware.hex
#vpath %S libfemtorv 

%.bin: %.elf
#	$(OBJCOPY) -O verilog $< $@
	$(OBJCOPY) -O binary $< $@
	chmod -x $@

firmware.elf: $(OBJECTS) 
	$(LD) $(LDFLAGS)  -Map firmware.map $(OBJECTS) -o $@  ${LIB_DIR}  ${LIBS}  
	chmod -x $@
	
firmware.hex: firmware.elf firmware.lst
	../firmware_words_src/firmware_words firmware.elf -ram 8192 -max_addr 8192  -out firmware.hex
	cp firmware.hex ../../rtl
	
firmware.lst: firmware.elf
	$(OBJDUMP) -h -S $< > $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< 
%.o: %.S
	$(AS) $(AFLAGS) -c $< -o $@
clean:
	rm -rf  $(OBJECTS) *.elf *.bin .*~ *~ *.map *.d *.hex *.lst
.PHONY: clean
