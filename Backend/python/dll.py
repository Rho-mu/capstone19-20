import ctypes
from ctypes import cdll

mydll = ctypes.CDLL(r'G:\ACGCA-master\ACGCA\src\ACGCA.dll')
growth = mydll.growthloop
sum = mydll.sum
print(sum(1,2))
