CC = gcc

TARGET = src/main.c
INCLUDES = src/fileM.c
EXEC = bin/pass

all : $(TARGET) $(INCLUDES)
	$(CC) $(TARGET) $(INCLUDES) -o $(EXEC)

exec :
	./$(EXEC)

clean :
	rm $(EXEC) *.o
