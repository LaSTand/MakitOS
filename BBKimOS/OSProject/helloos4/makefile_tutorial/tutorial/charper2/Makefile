CC = gcc
OBJS = Mysocket.o Myclient.o
TARGET = myClient

.SUFFIXEX : .c .o

all : $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean :
	rm -f $(OBJS) $(TARGET)
