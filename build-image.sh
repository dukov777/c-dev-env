#!/bin/bash

# http://google.github.io/googletest/quickstart-cmake.html

docker build -t c-dev-env-1 \
    --build-arg SSH_PRIVATE_KEY="$(cat ~/.ssh/id_ed25519)" \
    --build-arg SSH_PUBLIC_KEY="$(cat ~/.ssh/id_ed25519.pub)" \
    --build-arg KNOWN_HOSTS="$(cat ~/.ssh/known_hosts)"  \
    .
