target = bin/test

incdirs := rainbow
srcdirs := rainbow tests

#指定源文件列表(由vpath处理路径问题)
srcs := log.cpp util.cpp test.cpp

#指定中间文件目录
objdir := obj

#指定目标文件列表
objlist := $(patsubst %.cpp, $(objdir)/%.o, $(srcs))

#指定gcc头文件路径
INCDIR := $(patsubst %, -std=c++0x -I %, $(incdirs))

#为.c文件指定搜索目录
vpath %.cpp $(srcdirs)
#为.h文件指定搜索目录
vpath %.h $(incdirs)

$(target):$(objlist)
	g++ -o $@ $^ -std=c++0x

objdir:
	@echo "create obj directory"
	-mkdir $(objdir)

$(objdir)/%.o: %.cpp
	g++ -MD $(INCDIR) -c $< -o $@

all: $(objdir) $(objlist)
	@echo compile done

.PHONY: all clean

clean:
	rm $(objdir)/*.o $(objdir)/*.d $(objdir) -rf
