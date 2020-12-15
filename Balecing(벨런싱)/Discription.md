# 벨런싱 동작

---------------------
## 동작 설명
    자이로 센서와 myrio의 x,y,z 축의 값을 받아와서 각도로 계산 한 뒤 이를 내가 설정한 각도 값과 비교한 뒤
    계속 서있을 수 있도록 모터를 제어한다.
    모터 제어는 PID 제어 방식을 사용한다.
### 사용 프로그램 : Labview 

### 사용 기기 
    1. myRio
    2. DC 모터 2개
    3. 자이로 센서 

### 상부 필터 공식
    accdatx = atan2(accydata/acczdata)
    xang = 0.98*(xang+gyroxdata*dt)+0.02(accdatax)

### 핀 연결도
![pinout](https://user-images.githubusercontent.com/54137044/102230294-0cc2b880-3f30-11eb-98dd-153c1373554e.png)
### Labview 코드 캡쳐
![codecapture](https://user-images.githubusercontent.com/54137044/102230578-675c1480-3f30-11eb-8db9-5ef5bde07d57.png)
### 보완사항
    지금 센서의 값이 너무 계속 바뀌어서 바뀌는 값에 대한 모터 제어가 완벽하지 않다.
    모터의 동작 속도를 조금 더 완만하게 바꾸고 싶은데 D 제어를 하면 모터가 진동을 해서 방안을 찾고 있다.


