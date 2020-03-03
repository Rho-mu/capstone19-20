import ctypes 
testlib = ctypes.CDLL(r"C:\Users\user、\Desktop\demo03\demo.dll")
testlib.greet.restype = ctypes.c_char_p
print (testlib.greet("hello world".encode("utf-8")))
