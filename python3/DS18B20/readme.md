# 第一步：
 编译生成共享库文件： 
```
gcc -fPIC -shared -o ds18b20.so ds18b20.c -lwiringPi
```
# 第二步：
python读取数据：
```
python3 p-c.py
```
注意：读取的结果是3位数，需要自己转换—除以10得到整数部分，取余10得到小数部分。