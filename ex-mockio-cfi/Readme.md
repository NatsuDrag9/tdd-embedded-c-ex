This is an exercise on Test Driven Development for embedded systems. The cpputest framework's MockIO from [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) is used to implement the CFI command in Appendix B of [the device specification](docs/STMicroelectronics/m28w160ect.pdf) mentioned in **Put the Knowledge to Work** section at the end of ***chapter 10*** of the book.<br />

---

1.) Pull this git repo <br />
```git pull origin main```

2.) Clone the CPPUTest framework into the project directory <br />
```git clone https://github.com/cpputest/cpputest.git```

3.) Build CPPUTEST using Autotools <br />
```cd /cpputest``` <br />
```autoreconf . -i``` <br />
```./configure``` <br />
```make tdd```

Change to the unit-tests directory <br />
4.) ```cd ex-mockio-cfi/ex-unit-tests```

5.) Set the path of the environment variable CPPUTEST_HOME for successful compilation: <br >
```EXPORT CPPUTEST_HOME=../cpputest```

The cpputest is compiled according to the instructions mentioned in [Using CppUTest with Makefileworker.mk and gcc](https://cpputest.github.io/). Refer [readme](https://github.com/jwgrenning/cpputest-starter-project/blob/master/readme/cpputest-starter-kit-readme.pdf) file of [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) by James W. Grenning for more details about  steps 2 to 6.

6.) Change to project directory <br />
```cd ..```

7.) Build the production code and generate the ```app.elf``` output file <br />
```make all``` 

8.) Run the application <br />
```./build/app.elf``` 

9.) Run the unit-tests<br />
```make test```

10.) Cleanup <br />
```make clean```<br />
```make clean_test```

---

## **Build using Docker (Recommended)**

Ensure that you have docker engine installed in your system. If not, visit [Install Docker Engine](https://docs.docker.com/engine/install/) for the installation guide.

Run the following commands in the terminal

Pull this git repo <br />
```git pull origin main```

Build using docker. Omit sudo if the **user** has been added to **docker** group <br />
```sudo docker build -t ex-mockio-cfi:latest ./```. <br /> 

Run using the docker engine <br />
```sudo docker run --rm ex-mockio-cfi:latest```

---

**Note - I skipped this exercise. Refer point 3 in [notes.txt](https://github.com/NatsuDrag9/tdd-embedded-c-ex/blob/chp10/ex-mockio-cfi/notes.txt) for the issue. I would be grateful for any help that resolved this issue**