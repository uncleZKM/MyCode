import urequests
import ujson
import network

#配置ESP8266工作在STATION模式
wlan=network.WLAN(network.STA_IF)
#允许网络接口
wlan.active()
#连接到设备 users为wifi名称，password为wifi密码
wlan.connect("users","password")

while not wlan.isconnected():
    pass
#请求的URL地址,其中key值xxxxxx为用户注册的密钥
#心知天气API
URL="https://api.seniverse.com/v3/weather/daily.json?key=S-r6aI12XHntuUnFP&location=fuyang&language=zh-Hans&unit=c&start=0&days=3"
#GET请求并且返回
response = urequests.get(URL)
#等待请求完成
while response.status_code == 200:
    pass
#装换成JSON数据
doc=ujson.loads(response.text)

weather = doc['results'][0]
daily=doc['results'][0]['daily'];
