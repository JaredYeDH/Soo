hine:lvm_main.o lvm_lmachine.o lvm_assembler.o lvm_global.o
		g++ -g  lvm_main.o lvm_lmachine.o lvm_assembler.o lvm_global.o   -o Lvmachine
lvm_main.o:lvm/lvm_main.cpp lvm/lvm_lmachine.h lvm/lvm_assembler.h
		g++ -g -c lvm/lvm_main.cpp
lvm_lmachine.o:lvm/lvm_lmachine.cpp lvm/lvm_lmachine.h
		g++ -g -c lvm/lvm_lmachine.cpp
lvm_assembler.o:lvm/lvm_assembler.cpp lvm/lvm_assembler.h
		g++ -g -c lvm/lvm_assembler.cpp
lvm_global.o:lvm/lvm_global.cpp lvm/lvm_global.h
		g++ -g -c lvm/lvm_global.cpp
clean:
	rm -f lvm_main.o lvm_lmachine.o lvm_assembler.o lvm_global.o Lvmachine
