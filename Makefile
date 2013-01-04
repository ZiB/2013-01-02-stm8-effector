#==========================================================
#   File:   Makefile for STM8
#   Date:   2011-01-22
#==========================================================

SRC_C  = main.c
SRC_C += macros.c
SRC_C += program.c
SRC_C += task_manager.c
SRC_C += soft_bam.c
SRC_C += stm8_interrupt_vector.c
SRC_C += stm8s_it.c
SRC_C += stm8s_clk.c
SRC_C += stm8s_tim2.c
SRC_C += stm8s_tim4.c

#----------------------------------------------------------

CROSS_PATH = C:/Tools/Cosmic/
CROSS = $(CROSS_PATH)/4.3.7/

INCLUDES += -imcu
INCLUDES += -imcu/peripherals
INCLUDES += -imcu/startup
INCLUDES += -imcu/std_lib/inc
INCLUDES += -imcu/std_lib/src
INCLUDES += -iutility

VPATH += mcu
VPATH += mcu/peripherals
VPATH += mcu/startup
VPATH += mcu/std_lib/inc
VPATH += mcu/std_lib/src
VPATH += utility

#----------------------------------------------------------

FLAGS_C  = +debug +warn +modsl0 -pxp -pp +compact +split -l -gge -pge

#----------------------------------------------------------

all: clean target.elf size

git:
	@C:/Tools/git/bin/git gui

mcu_all: all mcu_program mcu_restart

%.elf: $(SRC_C:%.c=target/%.o)
	@echo '-----------------------------------------------------------'
	@echo linking: $@
	@$(CROSS)clnk -l'$(CROSS)/Lib' -o'target/target.sm8' -m'target/target.map' -sa 'mcu/*.lsf'
	@$(CROSS)cvdwarf target/target.sm8
	@$(CROSS)chex -o target/target.s19 target/target.sm8
	@rm -f target/*.o
	
$(SRC_C:%.c=target/%.o): target/%.o: %.c
	@$(CROSS)cxstm8 $(FLAGS_C) $(INCLUDES) -i. -i$(CROSS)/Hstm8 -cl'target' -co'target' $<

size:
	@echo '-----------------------------------------------------------'
	@$(CROSS)cobj -n target/target.sm8 | $(CROSS_PATH)cosmic_format 'mcu/stm8s003k3.lsf'
	
clean:
	@echo '-----------------------------------------------------------'
	@rm -f target/*.*

mcu_program:
	@C:/Tools/STMicroelectronics/toolset/stvp/apisample.exe -BoardName=ST-LINK -Device=STM8S003K3 -Port=USB -ProgMode=SWIM -no_loop -no_log -FileProg=target/target.s19

mcu_restart:
	@C:/Tools/STMicroelectronics/toolset/stvd/gdb7.exe --quiet --command=mcu/stm8s003k3.ini
	
.PHONY : all clean program