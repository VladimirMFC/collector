build:	config
	cd temp && make

config:
	mkdir -p temp && cd temp && cmake -DCMAKE_BUILD_TYPE=Debug ..

clean:
	rm -rfv temp

run:	build
	./temp/cld -c conf/cld.conf -p temp/cld.pid
