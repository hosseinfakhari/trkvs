build:
	bazel build src/main:TKVS
run:
	bazel run src/main:TKVS  
test:
	bazel test tests:kvslib_test
clean:
	bazel clean
