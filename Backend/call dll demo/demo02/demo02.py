#! python3

import ctypes
mydll = ctypes.WinDLL(r'C:\Users\user、\Desktop\demo02\Test.dll')
result = mydll.sum(1,2)
print (result)
