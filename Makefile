build:	config
	cd server && make build

config:
	cd server && make config

clean:
	cd server && make clean

run:	build
	cd server && make run
