# FASTMATCH Algorithm

**Contents**<br>
[About](#about)<br>
[Documentation](#documentation)<br>
[Unit Testing](#unit-testing)<br>
[Running and Compiling](#running-and-compiling)<br>

## About
Implementation based on the [SoCG 2019 Paper](https://drops.dagstuhl.de/opus/volltexte/2019/10452/pdf/LIPIcs-SoCG-2019-48.pdf) by Lahn and Raghvendra and built on top of [code](https://github.com/JIANCHUJUN/JOCGV3) developed by Ye.

## Documentation
[UML Diagram](https://app.lucidchart.com/documents/edit/326ed988-99a0-45b4-977b-5ea26e415a4c/0_0)
[White Paper](https://www.overleaf.com/read/sfvjzsjdqqtn)

## Unit Testing
Unit tests are done through the [Catch 2 Framework](https://github.com/catchorg/Catch2)

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