# Minimal Expression Generator using Quine-McCluskey algorithm

## 0. Summary 
### Input
<img width="400" alt="스크린샷 2021-06-01 오전 12 27 10" src="https://user-images.githubusercontent.com/56920080/120214942-1e92e080-c270-11eb-862a-a7dc95757e7e.png">

### Output
<img width="200" alt="스크린샷 2021-06-01 오전 12 28 18" src="https://user-images.githubusercontent.com/56920080/120215141-57cb5080-c270-11eb-8abb-4ee3f92727fc.png">

## 1. Build
```
/usr/bin/clang++ -std=c++17 -stdlib=libc++ -g MEG.cpp -o MEG 
```
or
```
g++ -std=c++17 -g MEG.cpp -o MEG
```
 
 
리눅스를 사용하거나 g++ 컴파일러를 사용한다면 다음과 같은 커맨드를 이용하여 컴파일할 수 있다.
1. Build
본 프로젝트의 결과물은 MEG.cpp 라는 소스코드에 담겨져있다. 맥에서 개발을 했기 때문에, clang 컴파일러를 사용했고, c++의 버전은 표준 17을 사용하였다. 다음과 같은 커맨드로 빌드를 할 수 있다.
/usr/bin/clang++ -std=c++17 -stdlib=libc++ -g MEG.cpp -o MEG <     (맥에서 테스트 완료)
리눅스를 사용하거나 g++ 컴파일러를 사용한다면 다음과 같은 커맨드를 이용하여 컴파일할 수 있다.
g++ -std=c++17 -g MEG.cpp -o MEG          (우분투에서 테스트 완료)
윈도우의 Visual Studo 2019를 이용하였을 때는 빌드 과정에서 어려움을 겪을 수 있다. 따라서 맥이나 리눅스를 이용하는 것이 권장된다. (Visual Studio 2019로 컴파일을 하려면 추가 세팅이 필요)
          (우분투에서 테스트 완료)
윈도우의 Visual Studo 2019를 이용하였을 때는 빌드 과정에서 어려움을 겪을 수 있다. 따라서 맥이나 리눅스를 이용하는 것이 권장된다. (Visual Studio 2019로 컴파일을 하려면 추가 세팅이 필요)
![image](https://user-images.githubusercontent.com/56920080/120214774-e2f81680-c26f-11eb-9de6-9ee9c01457fa.png)

Quine–McCluskey algorithm to find out the minimal expression of the minterms.
