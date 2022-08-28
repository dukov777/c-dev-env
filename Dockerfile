# ---------------------------------------------------------

FROM ubuntu:focal AS build

ENV DEBIAN_FRONTEND=noninteractive
ENV DEBCONF_NONINTERACTIVE_SEEN=true

# RUN echo 'tzdata tzdata/Areas select Etc' | debconf-set-selections \
#     echo 'tzdata tzdata/Zones/Etc select UTC' | debconf-set-selections

RUN apt-get clean && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
    bc \
    locales \
    build-essential \
    curl \
    wget \
    apt-transport-https \
    apt-utils \
    xz-utils \
    gnupg \
    ca-certificates \
    python-dev \
    lsb-release && \
    rm -rf /var/lib/apt/lists/* && \
    locale-gen en_US.UTF-8

ENV LANG=en_US.UTF-8 LANGUAGE=en_US:en LC_ALL=en_US.UTF-8

RUN apt-get update && \
    apt-get install -y --no-install-recommends vim && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install -y --no-install-recommends gdb && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install -y --no-install-recommends software-properties-common && \
    add-apt-repository ppa:git-core/ppa -y && \ 
    apt-get update && \
    apt-get install -y --no-install-recommends git && \
    rm -rf /var/lib/apt/lists/*

RUN add-apt-repository -y ppa:ubuntu-toolchain-r/test && apt-get update \
    && apt-get install -y --no-install-recommends \
    g++-11 \
    gcc-11 \
    cmake

# Removing g++, gcc, symlink for default GCC and adding them for GCC-11
RUN rm -f \
    /usr/bin/g++ \
    /usr/bin/gcc \
    && ln -s /usr/bin/g++-11 /usr/bin/g++ \
    && ln -s /usr/bin/gcc-11 /usr/bin/gcc



FROM build AS development

ARG SSH_PRIVATE_KEY
ARG SSH_PUBLIC_KEY
ARG KNOWN_HOSTS

# Authorize SSH Host
RUN mkdir -p /root/.ssh && \
    chmod 0700 /root/.ssh

# Add the keys and set permissions
RUN echo "${SSH_PRIVATE_KEY}" > /root/.ssh/id_ed25519 && \
    echo "${SSH_PUBLIC_KEY}" > /root/.ssh/id_ed25519.pub && \
    echo "${KNOWN_HOSTS}" >> /root/.ssh/known_hosts && \
    chmod 600 /root/.ssh/id_ed25519 && \
    chmod 600 /root/.ssh/id_ed25519.pub

# Uses "robbyrussell" theme (original Oh My Zsh theme), with no plugins
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
    -t robbyrussell
# Uses "Spaceship" theme with some customization. Uses some bundled plugins and installs some more from github
RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
    -t robbyrussell \
    -p git \
    -p history \
    -p https://github.com/zsh-users/zsh-autosuggestions

WORKDIR /app


# ---------------------------------------------------------

FROM development AS compile
RUN git clone git@gitlab.endurosatlab.com:k-band-transceiver/application-layer/LunarOutpostGateWay.git
RUN cd LunarOutpostGateWay && \
    git submodule init && \ 
    git submodule update && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

USER root
ENTRYPOINT [ "/bin/zsh" ]
