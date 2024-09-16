FROM php:8.2-fpm
RUN apt-get update && apt-get install -y \
		locate  \
	&& docker-php-ext-install mysqli \
	&& docker-php-ext-enable mysqli    
RUN pear install DB MDB2#mysql MDB2_Driver_mysqli 
RUN pear upgrade MDB2-beta 
RUN updatedb