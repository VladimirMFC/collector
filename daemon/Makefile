build:	config
	cd temp && make

config:
	mkdir -p temp && cd temp && cmake -DCMAKE_BUILD_TYPE=Debug ..

clean:
	rm -rfv temp bin

run:	build
	./bin/cld -c conf/cld.conf -p bin/cld.pid
