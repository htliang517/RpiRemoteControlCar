'''
Code created by Matt Richardson 
for details, visit:  http://mattrichardson.com/Raspberry-Pi-Flask/inde
'''
from flask import Flask, render_template, request
import datetime
import sys
import time
# import serial
app = Flask(__name__)
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)
print("Serial started on port: "+ser.name)


@app.route("/")
def interface():
    now = datetime.datetime.now()
    timeString = now.strftime("%Y-%m-%d %H:%M")
    templateData = {
        'title': 'PiCar',
        'time': timeString
    }
    return render_template('index.html', **templateData)


@app.route("/commands")
def update_command():
    command = request.args.get('input', 'b')
    print(command, file=sys.stderr)

    if command == "w":
        ser.write(b'w')
    elif command == "a":
        ser.write(b'a')
    elif command == "s":
        ser.write(b's')
    elif command == "d":
        ser.write(b'd')
    elif command == "i":
        ser.write(b'i')
    elif command == "k":
        ser.write(b'k')
    elif command == "b":
        ser.write(b'b')
    elif command == "c":
        ser.write(b'c')
    elif command == "r":
        ser.write(b'r')
    elif command == "t":
        ser.write(b't')
    elif command == "y":
        ser.write(b'y')
    elif command == "u":
        ser.write(b'u')
    else:
        ser.write(b'b')
    return 'success'


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80, debug=True, threaded=True)
