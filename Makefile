CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
OBJ_DIR = obj

OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/db.o $(OBJ_DIR)/network.o

EXEC = redis_clone

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/db.h $(SRC_DIR)/network.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/db.o: $(SRC_DIR)/db.c $(SRC_DIR)/db.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/db.c -o $(OBJ_DIR)/db.o

$(OBJ_DIR)/network.o: $(SRC_DIR)/network.c $(SRC_DIR)/network.h $(SRC_DIR)/db.h
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/network.c -o $(OBJ_DIR)/network.o

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC)
	rm -rf $(OBJ_DIR)
