# 주식투자 자동 투자 프로그램
-----------------------------------


### slacker 이용 메세지 보내기
    from slacker import Slacker

    slack = Slacker('<your-slack-api-token-goes-here>')

    # Send a message to #general channel 메세지 보내는 함수
    slack.chat.post_message('#stock', '보낼내용')

![image](https://user-images.githubusercontent.com/54137044/102801488-a4287f80-43f8-11eb-9893-4f408ed42cfd.png)

### 주가 정보 slack으로 보내기
    # 연결 여부 체크
        objCpCybos = win32com.client.Dispatch("CpUtil.CpCybos")
        bConnect = objCpCybos.IsConnect
        if (bConnect == 0):
            print("PLUS가 정상적으로 연결되지 않음. ")
            exit()
 
    # 현재가 객체 구하기
        objStockMst = win32com.client.Dispatch("DsCbo1.StockMst")
        objStockMst.SetInputValue(0, 'A005930')   #종목 코드 - 삼성전자
        objStockMst.BlockRequest()

### 크레온 자동 로그인 코드
    from pywinauto import application
    import time
    import os

    os.system('taskkill /IM coStarter* /F /T')
    os.system('taskkill /IM CpStart* /F /T')
    os.system('wmic process where "name like \'%coStarter%\'" call terminate')
    os.system('wmic process where "name like \'%CpStart%\'" call terminate')
    time.sleep(5)        

    app = application.Application()
    app.start('C:\CREON\STARTER\coStarter.exe /prj:cp /id:hwangho0 /pwd:nasca0.. /pwdcert:5099jina.. /autostart')
    time.sleep(60)