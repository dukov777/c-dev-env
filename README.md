# c-dev-env
Template for conteinerazed development enviorment in C

## x86 ##

docker build --target build -t ImageNameXYZ --no-cache --platform=linux/**amd64** .

## ARM ##

docker build --target build -t ImageNameXYZ --no-cache --platform=linux/**arm64** .

## Specifing the target **Stage** ##

docker build **--target build** -t ImageNameXYZ  --platform linux/arm64 --no-cache --platform=linux/amd64 .

## Build with all options ##
docker build -t ImageNameXYZ --build-arg SSH_PRIVATE_KEY="$(cat ~/.ssh/id_ed25519)" --build-arg SSH_PUBLIC_KEY="$(cat ~/.ssh/id_ed25519.pub)" --build-arg KNOWN_HOSTS="$(cat ~/.ssh/known_hosts)" --platform linux/arm64 .

## Specifing Dockerfile ##

docker build **-f ./lunar-conteiner-dev-env/Dockerfile** -t c-dev-env-1 --build-arg SSH_PRIVATE_KEY="$(cat ~/.ssh/id_ed25519)" --build-arg SSH_PUBLIC_KEY="$(cat ~/.ssh/id_ed25519.pub)" --build-arg KNOWN_HOSTS="$(cat ~/.ssh/known_hosts)"  .

# Steps to build project #

docker build --target development -t c-dev-env . 

docker run --mount type=bind,source="$(pwd)/project",target=/app/ -it --rm c-dev-env

Open VS Code
Connect to container

