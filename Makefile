# target
target := bin/test_iomanager

# compile and lib parameter
CC		:= g++ -std=c++11 -g3 -Wall -pthread
# LIBS	:= -L/usr/local/lib
# INCLUDE := -I/usr/local/include
DEFINES := -lyaml-cpp

incdirs := rainbow
srcdirs := rainbow tests

#指定源文件列表(由vpath处理路径问题)
srcs := timer.cpp iomanager.cpp scheduler.cpp fiber.cpp thread.cpp config.cpp log.cpp util.cpp test_iomanager.cpp

#指定中间文件目录
objdir := obj

#指定目标文件列表
objlist := $(patsubst %.cpp, $(objdir)/%.o, $(srcs))

#指定gcc头文件路径
INCDIR := $(patsubst %, -I %, $(incdirs))

#为.c文件指定搜索目录
vpath %.cpp $(srcdirs)
#为.h文件指定搜索目录
vpath %.h $(incdirs)

# 如果obj文件夹不存在，则创建该文件夹
obj_dir := ./obj
$(shell if [ ! -e $(obj_dir) ];then mkdir -p $(obj_dir); fi)

$(target):$(objlist)
	$(CC) -o $@ $^ $(DEFINES) 

$(objdir)/%.o: %.cpp
	$(CC) -MD $(INCDIR) -c $< -o $@ 

all: $(objdir) $(objlist)
	@echo compile done

.PHONY: all clean

clean:
	rm $(objdir)/*.o $(objdir)/*.d $(objdir) -rf
