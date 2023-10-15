CC = gcc
CFLAGS = -Wall -Wextra -pedantic -Iinc -g
LDFLAGS = -lm -lws2_32
SRCDIR = src
OBJDIR = out
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
TARGET = server.exe

ifeq ($(OS),Windows_NT)
    RM = del /q
    MD = mkdir
else
    RM = rm -rf
    MD = mkdir -p
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	$(MD) $(OBJDIR)

clean:
	$(RM) $(OBJDIR)\*.o $(TARGET)
