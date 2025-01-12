# Start with the Bitnami NGINX base image
FROM bitnami/nginx:latest AS so_nginx

WORKDIR /

# Copy the default configuration file for NGINX
# Replace the default server block with your custom configuration
COPY ./so_nginx/etc/default.conf /opt/bitnami/nginx/conf/server_blocks/swinney.conf

# Copy FastCGI parameters file
COPY ./so_nginx/etc/fastcgi_params /opt/bitnami/nginx/conf/fastcgi_params

# Expose the ports defined in docker-compose.yml
EXPOSE 80 443

# Start the NGINX server
CMD ["nginx", "-g", "daemon off;"]
