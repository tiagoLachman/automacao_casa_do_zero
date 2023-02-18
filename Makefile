CC = gcc
CFLAGS = -I inc/
LIBS = -lws2_32

SRCS = src/server.c src/http.c
OBJS = $(SRCS:.c=.o)

TARGET = server

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /q src\*.o