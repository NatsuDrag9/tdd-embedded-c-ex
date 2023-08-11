This is an exercise on Test Driven Development for embedded systems. The cpputest framework from [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) is used to test the Led scheduler example in chapter 8 of the book.

---
Build using Autotools -- GNU toolchain 

1.) Pull this git repo <br />
```git pull origin main```

2.) First compile CPPUTEST <br />
The cpputest is compiled using Autotools according to the instructions mentioned in the [readme](https://github.com/jwgrenning/cpputest-starter-project/blob/master/readme/cpputest-starter-kit-readme.pdf) file of [cpputest-starter-project](https://github.com/jwgrenning/cpputest-starter-project) by James W. Grenning.

3.) ```cd ex-led-scheduler/unit-tests```

4.) Set the path of the environment variable CPPUTEST_HOME for successful compilation: <br >
```EXPORT CPPUTEST_HOME=../cpputest```

5.) Run ```make all```

---

Build using docker 
