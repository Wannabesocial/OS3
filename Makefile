# C compiler we use
CXX = gcc 

CFLAGS = -lpthread -Iinc

LDLIBS = -lrt -lm 

# Output filename after compilation 
MM = memory_manager

PM = page_manager

# Directory for object files
OBJ_DIR = obj

# Source files (without ffc_manager.c)
SRC = src/link_list.c\
		src/hash_table.c\
		src/config.c\
		src/ipc.c\
		src/mm_utils.c
		

# Create object file names for each source file
OBJ = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Main target
all: $(MM) $(PM)

# Create the directory that will keep the FIFOs files (ffs_in, ffs_out)
# $(FIFOs_DIR):
# 	mkdir -p $(FIFOs_DIR)

# Build (Memmory Manager) executable
$(MM): memory_manager.c $(OBJ)
	$(CXX) $(CFLAGS) -o $(MM) memory_manager.c $(OBJ) $(LDLIBS)

# Build (Page Manager) executable
$(PM): page_manager.c $(OBJ)
	$(CXX) $(CFLAGS) -o $(PM) page_manager.c $(OBJ) $(LDLIBS)

# Build object files (without server.c)
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CFLAGS) -c $< -o $@ $(LDLIBS)

# Clean up object files and executables
clean:
	rm -rf $(MM) $(PM) $(OBJ_DIR)