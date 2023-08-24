# FROM gcc:12.2.0
FROM ubuntu:22.04

# Install build tools
RUN apt update && \
    apt install -y wget build-essential autoconf automake libtool && \
    apt install -y git

# Install cpputest
WORKDIR /app/ex-alarm-clock-service/

# Copy the bash script that installs CppUTest framework
COPY install-cpputest.sh ./

# Make the bash script executable and run it
RUN chmod +x ./install-cpputest.sh
RUN ./install-cpputest.sh

# Set the working directory for the following commands
WORKDIR /app/ex-alarm-clock-service/

# Copy the alarm-clock-service header and source files
COPY inc/ ./inc/
COPY src/ ./src/

# Copy the application level main.c and makefile
COPY main.c ./
COPY Makefile ./

# Copy the test files and test makefile
# COPY ex-unit-tests/*.cpp ./
# COPY ex-unit-tests/makefile ./
COPY ex-unit-tests/ ./ex-unit-tests/

# Set the working directory for the following commands
# WORKDIR /app/ex-alarm-clock-service/

# # Copy the bash script that installs cpputest-starter-project
# COPY install-cpputest-starter-project.sh ./

# # Make the bash script executable
# RUN chmod +x ./install-cpputest-starter-project.sh

# # Run the bash script
# RUN ./install-cpputest-starter-project.sh

# # Change the working directory to run the makefile
# WORKDIR /app/ex-alarm-clock-service/unit-tests/

# # Set the environment variable
# ENV CPPUTEST_HOME=../cpputest

CMD ["/bin/sh", "-c", "make test"]