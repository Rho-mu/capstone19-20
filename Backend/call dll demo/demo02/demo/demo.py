#! python3

import ctypes
from ctypes import *

mydll = ctypes.WinDLL(r'C:/Users/user、/Desktop/capstone/demo/demo.dll')
Hello = mydll.Hello
Hello.argtypes = [c_char_p]
Hello.restype = c_char_p

res = Hello(" Isaac".encode("utf-8")).decode()
print (res)

