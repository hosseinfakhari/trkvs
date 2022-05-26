FROM ubuntu:latest

RUN apt update -y; apt install -y build-essential nodejs npm; npm install -g @bazel/bazelisk; bazelisk

COPY . /home

WORKDIR /home