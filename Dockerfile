FROM ubuntu:12.04

RUN apt-get update && \
    apt-get install -y build-essential nasm genisoimage libc6-dev-i386

WORKDIR /code
