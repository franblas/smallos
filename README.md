# Small OS
A small 32 bits operating system.

## Setup on MacOS
### Requirements
- virtualbox
- boot2docker

### Initialize and run
Initialize boot2docker
```bash
make docker-init
eval "$(boot2docker shellinit)"
```

Then build one time the docker image
```bash
make docker-build
```

And finally compile the OS
```bash
make docker-run
```

### Run the OS
Create a new VM in VirtualBox:
- Type: other
- Version: other/unknown
- No virtual hard drive

Select `smallos.iso` (into the src folder) and run it.

## Documentation and tutorials
- https://littleosbook.github.io/
- http://www.osdever.net/bkerndev/Docs/title.htm
- http://wiki.osdev.org/Main_Page
