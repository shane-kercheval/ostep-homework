FROM python:3.11

# Install necessary packages for building software
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    software-properties-common \
    man-db \
    zsh \
    lsof \
    gcc \
    g++ \
    gdb \
    make \
    cmake \
    curl \
    libgtest-dev \
    clang-tidy

# Build and install Google Test
RUN cd /usr/src/gtest && \
    cmake CMakeLists.txt && \
    make && \
    cp lib/*.a /usr/lib

# Set default shell to zsh (optional, depends on your preference)
RUN echo "dash dash/sh boolean false" | debconf-set-selections && dpkg-reconfigure dash

# Clean up to reduce image size
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /code
ENV PYTHONPATH "${PYTHONPATH}:/code"

ENV PYDEVD_WARN_EVALUATION_TIMEOUT 1000

RUN apt-get update -y && apt-get install zsh -y
RUN PATH="$PATH:/usr/bin/zsh"

RUN apt-get install lsof

RUN python -m pip install --upgrade pip
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt
RUN rm requirements.txt
