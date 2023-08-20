FROM gcc:12.2.0

# Install cpputest
WORKDIR /app/ex-alarm-clock-service/

# Copy the bash script that installs CppUTest framework
COPY install-cpputest.sh ./

# Make the bash script executable
RUN chmod +x ./install-cpputest.sh

# Run the bash script
RUN ./install-cpputest.sh

# Set the working directory for the following commands
WORKDIR /app/ex-alarm-clock-service/

# Copy the alarm-clock-service header and source files
COPY inc/ ./inc/
COPY src/ ./src/

# Copy the test files and makefile
COPY unit-tests/tests/*.cpp ./
COPY unit-tests/makefile ./

# Set the working directory for the following commands
WORKDIR /app/ex-alarm-clock-service/

# Copy the bash script that installs cpputest-starter-project
COPY install-cpputest-starter-project.sh ./

# Make the bash script executable
RUN chmod +x ./install-cpputest-starter-project.sh

# Run the bash script
RUN ./install-cpputest-starter-project.sh

# Change the working directory to run the makefile
WORKDIR /app/ex-alarm-clock-service/unit-tests/

# Set the environment variable
ENV CPPUTEST_HOME=../cpputest

CMD ["make"]