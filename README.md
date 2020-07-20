# FASTMATCH Algorithm

**Contents**<br>
[About](#about)<br>
[Documentation](#documentation)<br>
[Style](#style)<br>
[Testing](#testing)<br>
[Running and Compiling](#running-and-compiling)<br>

## About
Implementation based on the [SoCG 2019 Paper](https://drops.dagstuhl.de/opus/volltexte/2019/10452/pdf/LIPIcs-SoCG-2019-48.pdf) by Lahn and Raghvendra and built on top of [code](https://github.com/JIANCHUJUN/JOCGV3) developed by Ye.

## Documentation
[UML Diagram](https://app.lucidchart.com/invitations/accept/92b8baa4-ec83-4598-b26b-c527b73a966f)<br>
[Formal Write-Up](https://www.overleaf.com/read/sfvjzsjdqqtn)

## Style
The project (tries to) adhere to the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) using their [cpplint.py script](https://raw.githubusercontent.com/google/styleguide/gh-pages/cpplint/cpplint.py).

## Testing
Unit tests are done through the [Catch 2 Framework](https://github.com/catchorg/Catch2). <br>
To check for memory leaks we use [Valgrind](https://valgrind.org/docs/manual/quick-start.html).

## Running and Compiling
### Application
Create a ```build ``` directory<br>
```
mkdir build
```

Run the ```compile.sh``` script in the scripts folder<br>
```
./scripts/compile.sh
```

Run executable ```fastmatch```<br>
```
./build/fastmatch
```

### Unit Tests
Create a ```build ``` directory<br>
```
mkdir build
```

Run the ```test_compile.sh``` script in the scripts folder<br>
```
./scripts/test_compile.sh
```

Run executable ```test_fastmatch```<br>
```
./build/test_fastmatch
```

Run ```cpplint.py```, unit tests, and ```valgrind``` all at once with ```verbose_test.sh``` <br>
```
./scripts/verbose_test.sh [RECENTLY_EDITED_FILE]
```