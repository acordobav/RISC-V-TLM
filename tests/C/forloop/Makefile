TARGET   = forloop

TARGET_ARCH=riscv32

CC       = riscv32-unknown-elf-gcc
# compiling flags here
#CFLAGS   = -Wall -I. -O0 -nostartfiles  -march=rv32i -mabi=ilp32
CFLAGS = -Wall -I. -O0 -nostdlib -march=rv32i -mabi=ilp32 --entry main
#CFLAGS = -Wall -I. -O0 -nodefaultlibs -march=rv32i -mabi=ilp32


# linking flags here
LFLAGS   = -I. --entry main
LIBS   = $(EXTRA_LIBS)


# change these to proper directories where each file should be
SRCDIR   = ./
OBJDIR   = .
BINDIR   = ./
INCDIR = -I.
LIBDIR = -L.


SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
#	$(LINKER) $(OBJECTS) $(LFLAGS) $(LIBS) $(LIBDIR) -o $@
	#riscv32-unknown-elf-objcopy -d $< > dump
	riscv32-unknown-elf-objcopy -Oihex $< $(TARGET).hex
	riscv32-unknown-elf-objcopy -O binary $< $(TARGET).bin
#	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compiling "$<" ..."
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
	$(CC) $(CFLAGS) $(INCDIR) $< -o $@
	@echo "Done!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
