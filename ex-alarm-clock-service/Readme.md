This is an exercise on Test Driven Development for embedded systems. The cpputest framework from [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) is used to test the alarm clock service mentioned in **Put the Knowledge to Work** section at the end chapter 8 of the book.<br />

---
## **Build using Autotools -- GNU toolchain**

This is an exercise on Test Driven Development for embedded systems. The cpputest framework from [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) is used to test the Led scheduler example in chapter 8 of the book.

---
## **Build using Autotools -- GNU toolchain**

1.) Pull this git repo <br />
```git pull origin main```

2.) Clone the CPPUTest framework into the project directory <br />
```git clone https://github.com/cpputest/cpputest.git```

3.) Clone the cpputest-starter-project into the ```unit-tests``` directory <br />
```git clone https://github.com/jwgrenning/cpputest-starter-project.git unit-tests```


4.) Build CPPUTEST using Autotools <br />
```cd /cpputest``` <br />
```autoreconf . -i``` <br />
```./configure``` <br />
```make tdd```

Change to the unit-tests directory <br />
5.) ```cd ex-led-scheduler/unit-tests```

6.) Set the path of the environment variable CPPUTEST_HOME for successful compilation: <br >
```EXPORT CPPUTEST_HOME=../cpputest```

The cpputest is compiled according to the instructions mentioned in [Using CppUTest with Makefileworker.mk and gcc](https://cpputest.github.io/). Refer [readme](https://github.com/jwgrenning/cpputest-starter-project/blob/master/readme/cpputest-starter-kit-readme.pdf) file of [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) by James W. Grenning for more details about  steps 2 to 6.

7.) Change to project directory <br />
```cd ..```

8.) Build the production code and generate the ```app.elf``` output file <br />
```make all``` 

9.) Run the application <br />
```./build/app.elf``` 

10.) Run the unit-tests<br />
```make test```

11.) Cleanup <br />
```make clean```<br />
```make clean_test```

---

## **Build using Docker (Recommended)**

Ensure that you have docker engine installed in your system. If not, visit [Install Docker Engine](https://docs.docker.com/engine/install/) for the installation guide.

Run the following commands in the terminal

Pull this git repo <br />
```git pull origin main```

Build using docker. Omit sudo if the **user** has been added to **docker** group <br />
```sudo docker build -t ex-led-scheduler:latest ./```. <br /> 

Run using the docker engine <br />
```sudo docker run ex-led-scheduler```