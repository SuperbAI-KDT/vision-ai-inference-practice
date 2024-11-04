import cv2
import gradio as gr
import requests
import numpy as np
from PIL import Image
from requests.auth import HTTPBasicAuth


# 가상의 비전 AI API URL (예: 객체 탐지 API)
VISION_API_URL = ""
TEAM = ""
ACCESS_KEY = ""


def process_image(image):
    # 이미지를 OpenCV 형식으로 변환
    image = np.array(image)
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)

    # 이미지를 API에 전송할 수 있는 형식으로 변환
    _, img_encoded = cv2.imencode(".jpg", image)

    # API 호출 및 결과 받기 - 실습1

    # API 결과를 바탕으로 박스 그리기 - 실습2

    # BGR 이미지를 RGB로 변환
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    return Image.fromarray(image)


# Gradio 인터페이스 설정
iface = gr.Interface(
    fn=process_image,
    inputs=gr.Image(type="pil"),
    outputs="image",
    title="Vision AI Object Detection",
    description="Upload an image to detect objects using Vision AI.",
)

# 인터페이스 실행
iface.launch()
