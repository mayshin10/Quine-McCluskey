# Minimal Expression Generator using Quine-McCluskey algorithm

### 0. Purpose
##### Input
<img width="400" alt="스크린샷 2021-06-01 오전 12 27 10" src="https://user-images.githubusercontent.com/56920080/120214942-1e92e080-c270-11eb-862a-a7dc95757e7e.png">

###### Output
<img width="200" alt="스크린샷 2021-06-01 오전 12 28 18" src="https://user-images.githubusercontent.com/56920080/120215141-57cb5080-c270-11eb-8abb-4ee3f92727fc.png">

---

### 1. Build
```
/usr/bin/clang++ -std=c++17 -stdlib=libc++ -g MEG.cpp -o MEG 
```
or
```
g++ -std=c++17 -g MEG.cpp -o MEG
``` 

---

### 2. Input method
Line 12 to 14 in MEG.cpp contains input arrays for 3, 4, 5-variable minterms.
<img width="759" alt="스크린샷 2021-06-01 오전 12 38 55" src="https://user-images.githubusercontent.com/56920080/120216270-c230c080-c271-11eb-9963-c4299fc02794.png">

---

### 3. Results

##### 3-variable Minimal Expression
<img width="400" alt="스크린샷 2021-06-01 오전 12 28 18" src="https://user-images.githubusercontent.com/56920080/120215983-636b4700-c271-11eb-8c5e-51e10c87c88f.png">

##### 4-variable Minimal Expression
<img width="400" alt="스크린샷 2021-06-01 오전 12 28 18" src="https://user-images.githubusercontent.com/56920080/120215958-59e1df00-c271-11eb-90ed-69f65c3a69a2.png">


##### 5-variable Minimal Expression
<img width="400" alt="스크린샷 2021-06-01 오전 12 28 18" src="https://user-images.githubusercontent.com/56920080/120215966-5c443900-c271-11eb-99df-ccf44cec546d.png">


 
 


