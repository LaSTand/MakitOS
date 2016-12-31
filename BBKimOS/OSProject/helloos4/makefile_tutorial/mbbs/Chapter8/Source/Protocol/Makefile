# Makefile of MyProtocol

include $(PROJ_ROOT)/IncludePre.mk

SUB_DIRS = $(ROOT_SRC_DIR)/Thread \
	$(ROOT_SRC_DIR)/Network \

LIB_NAME = MyProtocol
LIB_SRCS = MyProtocol.c 
TARGET_SRCS = MyClient.c TestConnection.c TestDataChange.c TestDrinking.c

# 의존성 규칙에 포함시킬 라이브러리입니다.
DEPEND_LIBS = -lMyThread -lMyNetwork

# 외부 시스템 라이브러리입니다.
LIBS += -lpthread

include $(PROJ_ROOT)/IncludePost.mk
