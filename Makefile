docker-init:
	boot2docker up
	eval "$$(boot2docker shellinit)"

docker-build:
	docker build -t smallos:0.1 .

docker-stop:
	boot2docker down

clean:
	cd src && make clean

docker-run:
	cd src && make docker-run
