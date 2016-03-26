build:	config
	cd temp && make

config:
	mkdir -p temp && cd temp && cmake ..

clean:
	rm -rfv temp

run:	build
	./temp/cld -c cld.conf -p temp/cld.pid
