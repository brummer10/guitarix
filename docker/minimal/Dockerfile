FROM debian:bookworm

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y && apt-get install -y \
        build-essential \
    && rm -rf /var/lib/apt/lists/*