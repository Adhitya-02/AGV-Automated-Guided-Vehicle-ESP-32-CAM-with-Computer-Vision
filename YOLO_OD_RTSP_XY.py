import cv2
from cv2 import dnn
from ultralytics import YOLO
import socket
import threading

def send_data(server, box):
    xywh = box.xywh[0]
    server.send((str(xywh.numpy()) + '\n').encode())

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('192.168.137.207', 81))

url = 1  #sbrt
cap = cv2.VideoCapture(url)

model = YOLO("/weights/yolov8n.pt")

classNames = ["person", "bicycle", "car", "motorbike", "aeroplane", "bus", "train", "truck", "boat",
              "traffic light", "fire hydrant", "stop sign", "parking meter", "bench", "bird", "cat",
              "dog", "horse", "sheep", "cow", "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella",
              "handbag", "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite", "baseball bat",
              "baseball glove", "skateboard", "surfboard", "tennis racket", "bottle", "wine glass", "cup",
              "fork", "knife", "spoon", "bowl", "banana", "apple", "sandwich", "orange", "broccoli",
              "carrot", "hot dog", "pizza", "donut", "cake", "chair", "sofa", "pottedplant", "bed",
              "diningtable", "toilet", "tvmonitor", "laptop", "mouse", "remote", "keyboard", "cell phone",
              "microwave", "oven", "toaster", "sink", "refrigerator", "book", "clock", "vase", "scissors",
              "teddy bear", "hair drier", "toothbrush"
              ]

if (cap.isOpened() == False):
    print("Error opening video on stream")
    exit()

while(cap.isOpened()):
    ret, frame = cap.read()
    if ret == True:
        # Membuat salinan dari frame
        frame_copy = frame.copy()

        # Mendapatkan bentuk gambar
        height, width = frame.shape[:2]

        # Menggambar garis x (horizontal) pada salinan frame
        cv2.line(frame_copy, (0, height//2), (width, height//2), (255, 0, 0), 2)

        # Menggambar garis y (vertikal) pada salinan frame
        cv2.line(frame_copy, (width//2, 0), (width//2, height), (0, 0, 255), 2)

        results = model(frame, stream = True)

        for r in results:
            boxes = r.boxes

            for box in boxes:
                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)

                clss = int(box.cls[0])
                if classNames[clss] == "bottle":
                    cv2.rectangle(frame_copy, (x1, y1), (x2, y2), color =(255, 0, 255), thickness=3)

                    print(box)
                    conf = box.conf[0]
                    
                    print("Class name --->", classNames[clss])

                    text_loc = [x1, y1]
                    font = cv2.FONT_HERSHEY_SIMPLEX
                    fontScale = 1
                    color = (255, 0, 0)
                    thickness =2

                    cv2.putText(frame_copy, classNames[clss], text_loc, font, fontScale, color, thickness)
                    threading.Thread(target=send_data, args=(server, box)).start()
      
        cv2.imshow('ESP32 Wrover Cam Stream', frame_copy)
        
        if cv2.waitKey(25) & 0xFF == ord('q'):
            break
    else:
        break

server.close()
cap.release()
cv2.destroyAllWindows()
