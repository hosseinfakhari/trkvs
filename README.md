# Transactional Key-Value Store

## Setting up the environment
this sourcecode use [Bazel](https://bazel.build/) as a build tool. so first step is to install `bazel` to be able to perform the rest of the commands.

* [install bazel on macos](https://bazel.build/install/os-x)
* [install bazel on ubuntu](https://bazel.build/install/ubuntu)

## Running Program
Run with `make` to build / execute / test the program
```
make build
make run
make test
```

## Develope with docker container
if you have docker on your machine, no need to install development tools, just run the below command to get inside the development container
```
./dev-environment.sh
```


### [Check the Arch.md before get into the code](ARCH.md)