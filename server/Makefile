build:	config
	cd temp && make

config:
	cd ../libutils && make build
	mkdir -p temp && cd temp && cmake -G "Unix Makefiles" ..

clean:
	cd ../libutils && make clean
	rm -rfv temp

run:	build
	./temp/cld -c cld.conf -p temp/cld.pid
