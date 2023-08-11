This is an exercise on Test Driven Development for embedded systems. The cpputest framework from [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) is used to test the Led scheduler example in chapter 8 of the book.

---
## **Build using Autotools -- GNU toolchain**

1.) Pull this git repo <br />
```git pull origin main```

2.) Build CPPUTEST using Autotools <br />
```cd /cpputest``` <br />
```autoreconf . -i``` <br />
```./configure``` <br />
```make tdd```

The cpputest is compiled according to the instructions mentioned in [Using CppUTest with Makefileworker.mk and gcc](https://cpputest.github.io/).

3.) ```cd ex-led-scheduler/unit-tests```

4.) Set the path of the environment variable CPPUTEST_HOME for successful compilation: <br >
```EXPORT CPPUTEST_HOME=../cpputest```

5.) Run ```make all```

Refer [readme](https://github.com/jwgrenning/cpputest-starter-project/blob/master/readme/cpputest-starter-kit-readme.pdf) file of [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) by James W. Grenning for more details about  steps 3 to 5.

---

## **Build using Docker**

Ensure that you have docker engine installed in your system. If not, visit [Install Docker Engine](https://docs.docker.com/engine/install/) for the installation guide.

Run the following commands in the terminal

Pull this git repo <br />
```git pull origin main```

Build using docker. Omit sudo if the **user** has been added to **docker** group
```sudo docker build -t ex-led-scheduler:latest ./```. <br /> 

Run using the docker engine
```sudo docker run ex-led-scheduler```