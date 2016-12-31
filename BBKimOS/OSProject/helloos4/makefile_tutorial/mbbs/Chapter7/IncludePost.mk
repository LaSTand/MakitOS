# MakefilePost.mk

LIB_FULL_NAME = $(ROOT_LIB_DIR)/$(OBJS_DIR)/lib$(LIB_NAME).a
LIB_OBJS = $(LIB_SRCS:%.c=$(OBJS_DIR)/%.o)

ALL_LIBS = -l$(LIB_NAME) $(LIBS)
ALL_LIBS += -lpthread

TARGET_OBJS = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%.o)
TARGET_NAMES = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%)

.SUFFIXES : .c .o

all : $(LIB_FULL_NAME) $(TARGET_NAMES)

$(LIB_FULL_NAME) : $(LIB_OBJS)
	@`[ -d $(ROOT_LIB_DIR)/$(OBJS_DIR) ] || $(MKDIR) -p $(ROOT_LIB_DIR)/$(OBJS_DIR)`
	$(AR) rcv $@ $(LIB_OBJS)
	$(RANLIB) $@

$(OBJS_DIR)/%.o : %.c
	@echo "==================================================="
	@echo "= Compiling $@ "
	@echo "==================================================="
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) $(OBJS_DIR)`
	$(CC) $(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) -c $< -o $@

.SECONDEXPANSION:
$(TARGET_NAMES): $$@.o
	@echo "==================================================="
	@echo "= Linking $@ "
	@echo "==================================================="
ifeq ($(LIBS_CYCLING_DEPEND),1)
	$(CC) -o $@ $< $(LIB_DIRS) -Wl,-\( $(ALL_LIBS) -Wl,-\)
else
	$(CC) -o $@ $< $(LIB_DIRS) $(ALL_LIBS)
endif

depend :
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) $(OBJS_DIR)`
	@$(RM) -f $(DEPEND_FILE)
	@for FILE in $(LIB_SRCS:%.c=%) $(TARGET_SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c \
			$(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) >> $(DEPEND_FILE); \
	done

clean :
	$(RM) -fr $(OBJS_DIR) $(LIB_FULL_NAME)

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif