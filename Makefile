ifeq ($(OS),Windows_NT) 
RM = cmd --% /c del /f
CP = copy /Y
ifdef ComSpec
SHELL := $(ComSpec)
endif
ifdef COMSPEC
SHELL := $(COMSPEC)
endif
else
RM = rm -rf
CP = cp -f
endif

CC := gcc
CFLAGS := -W -Wall -Wextra

DFSDIR = DFS
DFSSRCS = $(wildcard $(DFSDIR)/*.c)
DFSOBJS = $(patsubst $(DFSDIR)/%.c, $(DFSDIR)/%.o, $(DFSSRCS))
DFSBIN = $(DFSDIR)/programa.exe

$(DFSDIR)/%.o: $(DFSDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(DFSBIN): $(DFSOBJS)

all: dfs

dfs: clean $(DFSBIN)
	gcc $(DFSOBJS) -o $(DFSBIN)


clean: 
	-$(RM) DFS\DFS.o DFS\principal.o DFS\programa.exe

.PHONY: clean