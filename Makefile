TARGET   = RISCV_TLM

SYSTEMC ?=/usr/local/systemc-2.3.4
TARGET_ARCH=linux64

CC       = g++
# compiling flags here
CFLAGS   = -Wall -I. -O3 -std=c++17 -g -Wextra -Wunused-function 



LINKER   = g++
# linking flags here
LFLAGS   = -Wall -I. -lm -g
LIBS   = -lsystemc -lm $(EXTRA_LIBS)


# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = ./
INCDIR = -I. -I./inc -I$(SYSTEMC)/include
LIBDIR = -L. -L$(SYSTEMC)/lib-$(TARGET_ARCH)


SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) $(LIBS) $(LIBDIR) -o $@
	@echo "Linking complete!"


$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo "Compiling "$<" ..."
	@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@
	@echo "Done!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"

all: $(BINDIR)/$(TARGET)
