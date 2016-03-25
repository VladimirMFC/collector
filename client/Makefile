build:	config
	cd temp && make

config:
	mkdir -p temp && cd temp && qmake -o Makefile ..

clean:
	rm -rfv temp

run:	build
	./temp/clc
