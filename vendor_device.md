# 该文件用于存放设备厂商的设备信息
由名称计算出CRC32作为ID
```
printf "0x%08x\n" $(echo -n "st" | cksum | cut -d' ' -f1)
```
# 列表
供应商          供应商ID            设备型号            设备ID                                                  
st              0x9030a898          imx6ull           0xb5a2f729



