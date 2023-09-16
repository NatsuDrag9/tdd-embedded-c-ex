# FROM gcc:12.2.0
FROM ubuntu:22.04

# Install build tools
RUN apt update && \
    apt install -y wget build-essential autoconf automake libtool && \
    apt install -y git

# Install cpputest
WORKDIR /app/ex-circular-buffer-chp9/

# Copy the bash script that installs CppUTest framework
COPY install-cpputest.sh ./

# Make the bash script executable and run it
RUN chmod +x ./install-cpputest.sh
RUN ./install-cpputest.sh

# Set the working directory for the following commands
WORKDIR /app/ex-circular-buffer-chp9/

# Copy the circular-buffer header and source files
COPY inc/ ./inc/
COPY src/ ./src/

# Copy the application level main.c and makefile
COPY main.c ./
COPY Makefile ./

# Copy the test files and test makefile
COPY ex-unit-tests/ ./ex-unit-tests/

CMD ["/bin/sh", "-c", "make test"]