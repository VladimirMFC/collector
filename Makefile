build:	config
	cd libutils && make build
	cd agent-icmp && make build
	cd server && make build
	cd client && make build

config:
	cd libutils && make config
	cd agent-icmp && make config
	cd server && make config
	cd client && make config

clean:
	cd libutils && make clean
	cd agent-icmp && make clean
	cd server && make clean
	cd client && make clean
