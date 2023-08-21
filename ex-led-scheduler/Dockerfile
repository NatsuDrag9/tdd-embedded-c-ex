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

# Copy the test files and makefile
COPY ./*.cpp ./
COPY ./makefile ./

# Set the working directory for the following commands
WORKDIR /app/ex-led-scheduler/

# Copy the bash script that installs cpputest-starter-project
COPY install-cpputest-starter-project.sh ./

# Make the bash script executable
RUN chmod +x ./install-cpputest-starter-project.sh

# Run the bash script
RUN ./install-cpputest-starter-project.sh

# Change the working directory to run the makefile
WORKDIR /app/ex-led-scheduler/cpputest-starter-project/

# Set the environment variable
ENV CPPUTEST_HOME=../cpputest

CMD ["make"]