CONFIG_MODULE_SIG = n
TARGET_MODULE := fibdrv

obj-m := $(TARGET_MODULE).o
ccflags-y := -std=gnu99 -Wno-declaration-after-statement
$(TARGET_MODULE)-objs := fibdrv_core.o bignumber.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

GIT_HOOKS := .git/hooks/applied

all: $(GIT_HOOKS) client
	$(MAKE) -C $(KDIR) M=$(PWD) modules

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	$(RM) client out final *png
load:
	sudo insmod $(TARGET_MODULE).ko
unload:
	sudo rmmod $(TARGET_MODULE) || true >/dev/null

client: client.c
	$(CC) -o $@ $^

PRINTF = env printf
PASS_COLOR = \e[32;01m
NO_COLOR = \e[0m
pass = $(PRINTF) "$(PASS_COLOR)$1 Passed [-]$(NO_COLOR)\n"

run:
	$(MAKE) unload
	$(MAKE) load
	sudo ./client > out
	$(MAKE) unload

check: all run
	@diff -u out scripts/fibnacci500.txt && $(call pass)
	@scripts/verify.py

splot: all run
	gnuplot stime.gp

plot: all
	$(MAKE) unload
	$(MAKE) load
	@python3 eliminate.py
	$(MAKE) unload
	gnuplot time.gp
