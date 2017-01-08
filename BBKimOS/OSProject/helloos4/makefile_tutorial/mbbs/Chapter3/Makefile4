DEPEND_FILE = depend_file

CC = gcc

SRCS = MySocket.c MyMutex.c MySemaphore.c MyThread.c MyClient.c
OBJS = $(SRCS:%.c=%.o)

LIBS = -lpthread

TARGET = MyClient

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
		  $(CC) -o $@ $(OBJS) $(LIBS)

depend :
	   $(CC) -MM $(SRCS) > $(DEPEND_FILE)

clean :
	  rm -f $(OBJS) $(TARGET) $(DEPEND_FILE)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(SRCS),)
-include $(DEPEND_FILE)
endif
endif
endif