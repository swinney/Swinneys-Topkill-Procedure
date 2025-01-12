FROM php:8.3-fpm AS so_phpfpm
RUN apt-get update && apt-get install -y \
		locate  \
	&& docker-php-ext-install mysqli \
	&& docker-php-ext-enable mysqli    
RUN pear install DB MDB2#mysql MDB2_Driver_mysqli 
RUN pear upgrade MDB2-beta 
RUN updatedb

WORKDIR /

# Copy PHP configuration file into the container
COPY ./so_phpfpm/etc/php.ini /usr/local/etc/php/php.ini

# Copy web application files into the container
# TODO: rename /web to /app
COPY ../web /app

# Copy custom site libs
COPY ../lib/Swinsite /usr/local/lib/swinney

# Copy PEAR stuff
COPY ../pear/share/pear /pear/share/pear

# Copy vendor stuff
RUN mkdir -p /usr/local/lib/php/vendor
COPY ./so_phpfpm/lib/vendor /usr/local/lib/php/vendor
