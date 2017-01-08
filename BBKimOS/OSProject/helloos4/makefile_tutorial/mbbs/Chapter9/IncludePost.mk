# IncludePost.mk

ifeq ($(IS_SHARED),1)
SHARED_FLAGS = -fPIC
SHARED_SO_NAME = lib$(LIB_NAME).so.$(MAJOR_VERSION)
SHARED_REAL_NAME = $(SHARED_SO_NAME).$(MINOR_VERSION)
LIB_FULL_NAME = $(ROOT_LIB_DIR)/$(OBJS_DIR)/$(SHARED_REAL_NAME)
else
LIB_FULL_NAME = $(ROOT_LIB_DIR)/$(OBJS_DIR)/lib$(LIB_NAME).a
endif

LIB_OBJS = $(LIB_SRCS:%.c=$(OBJS_DIR)/%.o)

ALL_LIBS = -l$(LIB_NAME) $(DEPEND_LIBS) $(LIBS)

TARGET_OBJS = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%.o)
TARGET_NAMES = $(TARGET_SRCS:%.c=$(OBJS_DIR)/%)

.SUFFIXES : .c .o

all : lib subdirs targets

subdirs : 
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir all; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

lib : $(LIB_FULL_NAME)

liball : $(LIB_FULL_NAME) 
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir liball; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

targets : $(TARGET_NAMES)

$(LIB_FULL_NAME) : $(LIB_OBJS)
	@`[ -d $(ROOT_LIB_DIR)/$(OBJS_DIR) ] || $(MKDIR) -p $(ROOT_LIB_DIR)/$(OBJS_DIR)`
ifeq ($(IS_SHARED),1)
	$(CC) -shared -Wl,-soname,$(SHARED_SO_NAME) -o $@ $(LIB_OBJS)
	$(LN) -fs $(SHARED_REAL_NAME) $(SHARED_SO_NAME)
	$(LN) -fs $(SHARED_SO_NAME) lib$(LIB_NAME).so
	$(MV) $(SHARED_SO_NAME) lib$(LIB_NAME).so $(ROOT_LIB_DIR)/$(OBJS_DIR)/
else
	$(AR) rcv $@ $(LIB_OBJS)
	$(RANLIB) $@
endif

$(OBJS_DIR)/%.o : %.c
	@echo "==================================================="
	@echo "= Compiling $@"
	@echo "==================================================="
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) -p $(OBJS_DIR)`
	$(if $(findstring $<, $(TARGET_SRCS)), \
		$(CC) $(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) -c $< -o $@, \
		$(CC) $(CFLAGS) $(DBG_FLAGS) $(SHARED_FLAGS) $(INC_DIRS) -c $< -o $@)

.SECONDEXPANSION:
$(TARGET_NAMES): $$@.o
	@echo "==================================================="
	@echo "= Linking $@"
	@echo "==================================================="
ifeq ($(LIBS_CYCLING_DEPEND),1)
	$(CC) -o $@ $< $(LIB_DIRS) -Wl,-\( $(ALL_LIBS) -Wl,-\)
else
	$(CC) -o $@ $< $(LIB_DIRS) $(ALL_LIBS)
endif

depend :
	@`[ -d $(OBJS_DIR) ] || $(MKDIR) $(OBJS_DIR)`
	@$(RM) -f $(DEPEND_FILE)
	@for FILE in $(LIB_SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c $(CFLAGS) $(DBG_FLAGS) $(SHARED_FLAGS) $(INC_DIRS) >> $(DEPEND_FILE); \
	done
	@for FILE in $(TARGET_SRCS:%.c=%); do \
		$(CC) -MM -MT $(OBJS_DIR)/$$FILE.o $$FILE.c $(CFLAGS) $(DBG_FLAGS) $(INC_DIRS) >> $(DEPEND_FILE); \
	done

dependall : depend
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir dependall; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

clean :
	$(RM) -fr $(OBJS_DIR) $(LIB_FULL_NAME)
ifeq ($(IS_SHARED),1)
	$(RM) -f $(ROOT_LIB_DIR)/$(OBJS_DIR)/lib$(LIB_NAME).so*
endif

cleanall : clean
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir cleanall; \
		if [ $$? != 0 ]; then exit 1; fi; \
	done

$(TARGET_NAMES) : $(LIB_FULL_NAME) \
	$(patsubst -l%, $(wildcard %.*), $(DEPEND_LIBS))

ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), cleanall)
ifneq ($(MAKECMDGOALS), depend)
ifneq ($(MAKECMDGOALS), dependall)
ifneq ($(strip $(LIB_SRCS) $(TARGET_SRCS)),)
-include $(DEPEND_FILE)
endif
endif
endif
endif
endif