CC = gcc

TARGET = src/main.c
INCLUDES = src/fileM.c src/encryptionDecryption.c
EXEC = bin/pass

all : $(TARGET) $(INCLUDES)
	$(CC) -g $(TARGET) $(INCLUDES) -o $(EXEC)

exec :
	./$(EXEC)

clean :
	rm $(EXEC) *.o
