# Copyright (C) 2020 Gustavo Salomao
# All rights reserved.

# Setup
FROM debian:buster-slim
LABEL maintainer="Gustavo Salomao <gsalomao.eng@gmail.com>"

# Install system dependencies
RUN apt-get update && apt-get install --no-install-recommends -y \
    cmake \
    gcc-multilib \
    git \
    ninja-build \
    python3 \
    python3-pip

# Install python dependencies
RUN pip3 install setuptools
RUN pip3 install \
    commitizen \
    pre-commit

# Create default user
ARG USER=user
ARG UID=1000
ARG GID=1000
RUN useradd -m ${USER} --uid=${UID}
USER ${UID}:${GID}

# Project workspace
WORKDIR /src
