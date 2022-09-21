from operator import truediv
import serial
import pyautogui
import webbrowser
import ctypes
import time
from win10toast import ToastNotifier
from plyer import notification

print('start')

try:
    ser = serial.Serial('COM3', 9800, timeout=1)

except:
    raise Exception('Přístup byl odepřen. Připojte zařízení.')

toaster = ToastNotifier()

'''
line = ''
line = ser.readline()

line = str(line)
print(line)
'''

notified = False
mode = 1

#  time.sleep(10)

while True:
    line = ser.readline()

    line = str(line)
    line = line.replace("'", '')
    line = line.replace('b', '')

    print(mode)

    print('line: ' + line)

    if 'o' in line:
        print('doors')

        if mode == 1:
            ctypes.windll.user32.LockWorkStation()
        
        elif mode == 2:
            pyautogui.hotkey('space')
            ctypes.windll.user32.LockWorkStation()

        elif mode == 3:
            pyautogui.hotkey('/')

        elif mode == 4 and notified == False:
            #toaster.show_toast('Někdo otevřel dveře!', 'pozor')
            notification.notify('Někdo otevřel dveře', 'Pozor!')
            time.sleep(10)
            notified = True
            

        elif mode == 0:
            print('sensor was deactivated')
        
        else:
            print('mode error')


        
        

    elif '1' in line:
        print('normal mode')
        mode = 1

    elif '2' in line:
        print('youtube mode')
        mode = 2
    
    elif '3' in line:
        print('dc mode')
        mode = 3

    elif '4' in line:
        print('notify mode')
        mode = 4
    
    elif '0' in line:
        print('deactivated')
        mode = 0   

    elif notified == True:
        notified = False
        print('notification reseted')                                                                              


    '''
    elif 'A' in line:  
        print('aaa')

        while True:
            line = ser.readline()

            line = str(line)
            line = line.replace("'", '')
            line = line.replace('b', '')

            if '1' in line:
                pyautogui.hotkey('ctrl', 'alt', 'num1')
                pyautogui.hotkey('win', 'up')

            elif '2' in line:
                webbrowser.open('https://www.youtube.com/')

            elif '3' in line:
                webbrowser.open('https://mail.google.com/mail/u/0/#inbox')

            elif '#' in line:
                break

    

    else:
        print('else')

        if '1' in line:
            print(1)
            pyautogui.hotkey('ctrl', 'num1')

        elif '2' in line:
            webbrowser.open('https://www.youtube.com/')

        elif '*' in line:
            break
        '''


print('exit')