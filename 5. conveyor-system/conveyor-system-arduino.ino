#include <AccelStepper.h> // AccelStepper 라이브러리를 포함하여 스텝모터 제어 기능을 사용

// 핀 번호 정의
#define enablePin 8       // 스텝모터 드라이버의 Enable 핀
#define dirxPin 2         // 모터의 회전 방향 제어 핀
#define stepxPin 5        // 스텝 펄스 신호 핀
#define motorInterfaceType 1  // 1: Driver interface type (step + direction)
#define cmdxPin 13        // 외부 장치에 명령 신호를 전달하는 출력 핀
#define sensorx 9         // 센서 입력 핀 (예: 리미트 스위치, 근접 센서 등)

// AccelStepper 클래스 인스턴스를 생성 (인터페이스 타입, 스텝핀, 방향핀)
AccelStepper stepperx = AccelStepper(motorInterfaceType, stepxPin, dirxPin);

// 센서 입력 상태를 저장할 변수
int statex;

void setup()
{  
  // 핀 모드 설정
  pinMode(enablePin, OUTPUT);     // 모터 드라이버 Enable 핀을 출력으로 설정
  pinMode(sensorx, INPUT_PULLUP); // 센서 핀을 내부 풀업 저항을 사용해 입력으로 설정
  pinMode(cmdxPin, OUTPUT);       // 외부 명령 신호 핀을 출력으로 설정

  // 초기 핀 상태 설정
  digitalWrite(enablePin, LOW);   // 모터 드라이버를 활성화 (LOW가 Enable)
  digitalWrite(cmdxPin, HIGH);    // 명령 핀 초기 상태를 HIGH로 설정
  digitalWrite(sensorx, HIGH);    // 풀업 상태 유지 (사실상 필요 없음, 안전 코드로 보임)

  // 모터 속도 설정
  stepperx.setMaxSpeed(1000);     // 최대 속도 설정
  stepperx.setSpeed(900);         // 초기 모터 속도 설정 (가속 없이 일정 속도)
}

void loop()
{  
   // 센서 입력 상태를 읽음
   statex = digitalRead(sensorx);

   // 센서가 HIGH인 경우 (예: 작동 중지 조건)
   if (statex == HIGH) {
    digitalWrite(cmdxPin, LOW);   // 외부 장치에 '멈춤' 명령을 보냄
    stepperx.stop();              // 모터를 즉시 정지시킴
   } else {
    // 센서가 LOW인 경우 (예: 작동 조건)
    digitalWrite(cmdxPin, HIGH);  // 외부 장치에 '작동' 명령을 보냄
    stepperx.setSpeed(900);       // 모터 속도 유지
    stepperx.runSpeed();          // 지정된 속도로 모터를 계속 회전시킴
   }
}
