FROM public.ecr.aws/docker/library/ubuntu:plucky-20241213 AS so-base


ENV DEBIAN_FRONTEND=noninteractive \
    HOME=/root \
    LANG=en_US.UTF-8 \
    LC_ALL=en_US.UTF-8

    RUN apt-get update && apt-get install -y --no-install-recommends \
    nginx \
    php-fpm \
    php-mysql \
    php-pear \
    php-dev \
    php-xml \
    php-mbstring \
    php-zip \
    build-essential \
    supervisor \
    jq && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
