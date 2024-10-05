import serial
import mediapipe
import time
import cv2

ser = serial.Serial("COM3", 115200, timeout = 1)

mpHands = mediapipe.solutions.hands
hands = mpHands.Hands(max_num_hands = 1, min_detection_confidence = 0.7)
mpDraw = mediapipe.solutions.drawing_utils  

capture = cv2.VideoCapture(0) # 0 referse to the camera used to capture the video
while True:
    is_open, frame = capture.read() # is_open is True/False (frame captured or not)
    if not is_open: break

    x, y, z = frame.shape # x - height, y - width, z - rgb

    # Detect hand keypoints
    frameRGB = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB) # MediaPipe works with RGB images but OpenCV reads images in BGR format. So, using cv2.cvtCOLOR() function it converts the frame to RGB format.
    result = hands.process(frameRGB)

    if result.multi_hand_landmarks:
        for hand_landmarks in result.multi_hand_landmarks:

            mpDraw.draw_landmarks(frame, hand_landmarks, mpHands.HAND_CONNECTIONS) # draw landmarks on the frame

            #counting fingers
            finger_tips_ids = [8, 12, 16, 20]
            finger_count = 0
            for tip in finger_tips_ids:
                if hand_landmarks.landmark[tip].y < hand_landmarks.landmark[tip - 2].y: finger_count += 1
            if hand_landmarks.landmark[4].x > hand_landmarks.landmark[2].x: finger_count += 1
            
            ser.write(bytes(str(finger_count), 'utf-8')) 

            cv2.putText(frame, str(finger_count), (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.5, (160, 32, 24), 3) 
    else:
        ser.write(bytes('0', 'utf-8')) 

    cv2.imshow("Show me your hands!", frame) # shows the captured frame
    if cv2.waitKey(1) == ord('q'): break # 1 milisecond wait for break key

capture.release()
cv2.destroyAllWindows()
ser.close()