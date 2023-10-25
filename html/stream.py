from flask import Flask, render_template, request, jsonify, Response
import picamera
import io
import serial

app = Flask(__name__)
ser = serial.Serial('/dev/ttyACM0', 9600)

def gen_camera():
    with picamera.PiCamera() as camera:
        camera.resolution = (640, 480)
        camera.framerate = 30
        stream = io.BytesIO()
        for _ in camera.capture_continuous(stream, 'jpeg', use_video_port=True):
            yield (b'--frame\r\n'
                   b'Content-Type: image/jpeg\r\n\r\n' + stream.getvalue() + b'\r\n')
            stream.seek(0)
            stream.truncate()

@app.route('/video_feed')
def video_feed():
    return Response(gen_camera(), mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/send_command', methods=['POST'])
def send_command():
    command = request.form.get('command')
    ser.write(command.encode())
    response = ser.readline().decode('utf-8').strip()
    return jsonify(response=response)

@app.route('/')
def index():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(host='192.168.0.42', port=4242, debug=True)
