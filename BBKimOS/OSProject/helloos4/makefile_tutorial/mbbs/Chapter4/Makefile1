DEPEND_FILE = depend_file

CC = gcc
AR = ar
RANLIB = ranlib

LIB_NAME = MyProtocol
LIB_FULL_NAME = lib$(LIB_NAME).a

LIB_SRCS = MySocket.c MyMutex.c MySemaphore.c MyThread.c MyProtocol.c 
LIB_OBJS = $(LIB_SRCS:%.c=%.o)

LIBS = -lpthread
LIBS += -l$(LIB_NAME)
LIB_DIR = -L.

TARGET_SRCS = MyClient.c TestConnection.c TestDataChange.c TestDrinking.c 
TARGET_OBJS = $(TARGET_SRCS:%.c=%.o)
TARGET_NAMES = $(TARGET_SRCS:%.c=%)

.SUFFIXES : .c .o

all : $(LIB_FULL_NAME) $(TARGET_NAMES)

$(LIB_FULL_NAME) : $(LIB_OBJS)
	$(AR) rcv $@ $(LIB_OBJS)
	$(RANLIB) $@

.SECONDEXPANSION:
$(TARGET_NAMES): $$@.o
	$(CC) -o $@ $< $(LIB_DIR) $(LIBS)

depend :
	$(CC) -MM $(LIB_SRCS) $(TARGET_SRCS) > $(DEPEND_FILE)

clean :
	rm -f $(LIB_FULL_NAME) $(LIB_OBJS) $(TARGET_NAMES) $(TARGET_OBJS) $(DEPEND_FILE)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif
