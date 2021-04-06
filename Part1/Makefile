CC=g++
CFLAGS= -O3 
DEPS =
OBJ = hw2_part1_test.o 
EXEC = hw2_part1_test
LIB = _hw2_part1
LIB_DIR = yqy5271_hw2_part1

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) -I. -I./$(LIB_DIR)

$(EXEC): $(OBJ)
	module load gcc/7.3.1; \
	cd $(LIB_DIR) && $(MAKE);
	module load gcc/7.3.1; \
	$(CC) -o $@ $^ $(CFLAGS) -L./$(LIB_DIR)/ -l$(LIB) -L.

.PHONY: clean
clean:
	cd $(LIB_DIR) && $(MAKE) clean
	rm -f $(OBJ) $(EXEC)
