FROM gcc:12.2.0

# Install cpputest
WORKDIR /app/ex-led-scheduler/

# Copy the bash script that installs CppUTest framework
COPY install-cpputest.sh ./

# Make the bash script executable
RUN chmod +x ./install-cpputest.sh

# Run the bash script
RUN ./install-cpputest.sh

# Set the working directory for the following commands
WORKDIR /app/ex-led-scheduler/

# Copy the led-scheduler header and source files
COPY inc/ ./inc/
COPY src/ ./src/

# Copy the application level main.c and makefile
COPY main.c ./
COPY Makefile ./

# Copy the test files and makefile
COPY ./ex-unit-tests/*.cpp ./
COPY ./ex-unit-tests/makefile ./

# Set the working directory for the following commands
WORKDIR /app/ex-led-scheduler/

# Copy the bash script that installs cpputest-starter-project
COPY install-cpputest-starter-project.sh ./

# Make the bash script executable
RUN chmod +x ./install-cpputest-starter-project.sh

# Run the bash script
RUN ./install-cpputest-starter-project.sh

# Change the working directory to set environment variable
WORKDIR /app/ex-led-scheduler/unit-tests/

# Set the environment variable
ENV CPPUTEST_HOME=../cpputest

# Change the working directory to run the project makefile
WORKDIR /app/ex-led-scheduler/

CMD ["/bin/sh", "-c", "make test"]