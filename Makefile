build:	config
	cd server && make build
	cd client && make build

config:
	cd server && make config
	cd client && make config

clean:
	cd server && make clean
	cd client && make clean
