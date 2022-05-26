#! /bin/sh
docker build -f Dockerfile.dev . -t trkvs-dev
docker run --rm -ti --mount type=bind,source="$(pwd)",target=/home trkvs-dev bash