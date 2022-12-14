TARGET = tic-tac-toe

SRC = tic-tac-toe.c

# Import the necessary libraries for GRRLIB
LIBRARIES = -lgrrlib -lm -lfat -lwiiuse -lbte -logc -lwupc -lm

# Build rule for the tic-tac-toe.elf file
$(TARGET).elf: $(SRC)
  $(CC) $(CFLAGS) $(SRC) $(INCLUDE) $(LIBRARIES) -o $(TARGET).elf

include $(DEVKITPPC)/wii_rules
