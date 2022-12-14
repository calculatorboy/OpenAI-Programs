TARGET = tic-tac-toe

SRC = tic-tac-toe.c

# Import the necessary libraries for GRRLIB
LIBRARIES = -lgrrlib -lm -lfat -lwiiuse -lbte -logc

# Include the current directory in the list of include directories
INCLUDE = -I.

# Include the current directory in the list of library directories
LIBPATH = -L.

# Build rule for the tic-tac-toe.elf file
$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(LIBPATH) $(LIBRARIES) -o $(TARGET).elf

include $(DEVKITPPC)/wii_rules
