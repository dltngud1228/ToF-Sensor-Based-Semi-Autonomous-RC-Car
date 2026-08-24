# ToF 센서 기반 반자율 주행 RC카

Arduino UNO, VL53L0X ToF 센서, MG90S 서보모터, L9110S 모터 드라이버와 HC-06 블루투스 모듈을 이용한 4WD 반자율 주행 RC카입니다.

## 프로젝트 개요

스마트폰 앱으로 RC카를 직접 조종하는 수동 모드와, 전방 장애물을 감지해 좌우 공간을 확인하고 장애물을 회피하는 반자율 모드를 구현했습니다.

반자율 모드에서 좌우가 모두 막힌 경우에는 후진과 회전을 조합한 ㄷ자 장애물 탈출 동작을 수행합니다.

- 개발 기간: 2026년 6월 ~ 2026년 7월
- 프로젝트: CIR 하계 세미나
- 제어 보드: Arduino UNO
- 개발 언어: Arduino C/C++

## 주요 기능

- 스마트폰 블루투스 원격 조종
- 수동/반자율 모드 전환
- ToF 센서를 이용한 전방 거리 측정
- 서보모터를 이용한 좌우 거리 확인
- 더 넓은 방향을 선택하는 장애물 회피
- 좌우가 모두 막힌 경우 ㄷ자 탈출 동작
- 모터부와 제어부 전원 분리를 통한 통신 안정화

## 명령어

| 명령 | 기능 |
|:---:|---|
| `F` | 전진 / 반자율 주행 시작 |
| `B` | 후진 |
| `L` | 좌회전 |
| `R` | 우회전 |
| `S` | 정지 |
| `M` | 수동·반자율 모드 전환 |

## 저장소 구조

```text
ToF_Semi_Autonomous_RC_Car/
├── README.md
├── LICENSE
├── .gitignore
├── arduino/
│   ├── rc_car_main/
│   │   └── rc_car_main.ino
│   └── tests/
│       ├── tof_sensor_test/
│       │   └── tof_sensor_test.ino
│       ├── servo_test/
│       │   └── servo_test.ino
│       └── motor_bluetooth_test/
│           └── motor_bluetooth_test.ino
├── app/
│   └── README.md
├── docs/
│   ├── WIRING.md
│   ├── ALGORITHM.md
│   ├── COMMANDS.md
│   └── TROUBLESHOOTING.md
├── images/
│   └── README.md
└── presentation/
    └── README.md
```

## 하드웨어

| 부품 | 수량 |
|---|---:|
| Arduino UNO | 1 |
| VL53L0X ToF 센서 | 1 |
| MG90S 서보모터 | 1 |
| L9110S 모터 드라이버 | 2 |
| TT 기어드 모터 | 4 |
| 바퀴 | 4 |
| HC-06 블루투스 모듈 | 1 |
| 11.1V Li-Po 배터리 | 1 |
| DC-DC 스텝다운 모듈 | 2 |
| 3D 프린팅 섀시 및 브라켓 | 1식 |

## 전원 구성

```text
11.1V Li-Po
├── 5V 스텝다운
│   ├── Arduino UNO 5V
│   ├── VL53L0X
│   ├── MG90S
│   └── HC-06
└── 6V 스텝다운
    ├── 왼쪽 L9110S
    └── 오른쪽 L9110S
```

모든 장치의 GND는 공통으로 연결합니다.

## Arduino 라이브러리

Arduino IDE 라이브러리 관리자에서 다음 라이브러리를 설치합니다.

- `VL53L0X`
- `Servo`
- `SoftwareSerial`

`Wire`는 Arduino IDE 기본 라이브러리입니다.

## 실행 순서

1. 배선을 확인합니다.
2. `arduino/tests/`의 개별 테스트 코드를 실행합니다.
3. ToF 센서, 서보모터, 모터와 블루투스가 각각 정상 동작하는지 확인합니다.
4. `arduino/rc_car_main/rc_car_main.ino`를 Arduino UNO에 업로드합니다.
5. 스마트폰에서 HC-06을 페어링합니다.
6. App Inventor 앱에서 HC-06에 연결합니다.
7. 수동 모드 주행을 확인합니다.
8. `M` 명령으로 반자율 모드로 전환합니다.
9. `F` 명령으로 장애물 회피 주행을 시작합니다.



## 주의 사항

- 11.1V 배터리를 Arduino 5V 핀이나 모터에 직접 연결하지 않습니다.
- 5V 제어부와 6V 모터부는 각각 스텝다운 모듈을 사용합니다.
- 모터 전원선에는 점퍼선보다 충분한 굵기의 전선을 사용합니다.
- HC-06과 Arduino의 TX/RX는 서로 교차하여 연결합니다.
- RC카가 반대 방향으로 움직이면 해당 모터의 두 선을 서로 바꾸거나 코드의 HIGH/LOW 방향을 수정합니다.
- 실제 차량의 회전 시간은 바닥 마찰과 배터리 상태에 따라 조정해야 합니다.

## 제작자

- 이수형
- 한국공학대학교 메카트로닉스공학부
- CIR 하계 세미나 프로젝트
