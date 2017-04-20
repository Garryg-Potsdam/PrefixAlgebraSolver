obj = build/Main.o build/Expression.o build/Parser.o build/Types.o

PrefixAlgebra: $(obj)
	cc -o PrefixAlgebra $(obj)
	@echo "make complete."
build/Types.o:source/Types.c headers/Types.h
	cc -c source/Types.c -o build/Types.o

build/Parser.o:source/Parser.c headers/Parser.h
	cc -c source/Parser.c -o build/Parser.o

build/Expression.o:source/Expression.c headers/Expression.h
	cc -c source/Expression.c -o build/Expression.o

build/Main.o:source/Main.c
	mkdir build
	cc -c source/Main.c -o build/Main.o

clean:
	rm -rf build
