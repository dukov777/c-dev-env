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

- Build conteiner:

```
docker build --target development -t c-dev-env . 
```

- Run Container and mount to current directory (VS code project is working with this setup - Do not change `source="$(pwd)"`)

`docker run --mount type=bind,source="$(pwd)",target=/app/ -it --rm c-dev-env`

- Open VS Code

- Connect to container

- Follow the steps in https://code.visualstudio.com/docs/cpp/cmake-linux#_prerequisites

- Install all recomended CMake extensions *inside* conteiner.

- **IMPORTANT for debuging install** 

`C/C++ IntelliSense, debugging, and code browsing.`


<img width="400" alt="image" src="https://user-images.githubusercontent.com/10469747/187062877-68d10ce8-9ad4-4263-9035-a440b7fe3878.png">

- Build the project

<img width="400" alt="image" src="https://user-images.githubusercontent.com/10469747/187062339-0fa96c93-9366-4369-96e8-99df197b1bc1.png">


- Select appropriate kit in my case this is C11

<img width="400" alt="image" src="https://user-images.githubusercontent.com/10469747/187062311-7fb4f4b5-5490-4677-a999-16545f8d3d2d.png">

- CMake: Build output should look like this:

```
[main] Building folder: project 
[build] Starting build
[proc] Executing command: /usr/bin/cmake --build /app/project/build --config Debug --target all -j 8 --
[build] [100%] Built target slcan
[build] Build finished with exit code 0
```

- Run the generated executable:

<img width="300" alt="image" src="https://user-images.githubusercontent.com/10469747/187062711-24662234-4a98-442e-99b5-ad08fc4bf3ea.png">


Enjoy!




