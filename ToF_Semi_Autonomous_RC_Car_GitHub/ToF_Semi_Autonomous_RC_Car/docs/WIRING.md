# 배선 안내

## Arduino 핀 배치

| 기능 | Arduino 핀 |
|---|---:|
| 왼쪽 앞 모터 A | D2 |
| 왼쪽 앞 모터 B | D3 |
| 왼쪽 뒤 모터 A | D4 |
| 왼쪽 뒤 모터 B | D5 |
| 오른쪽 앞 모터 A | D6 |
| 오른쪽 앞 모터 B | D7 |
| 오른쪽 뒤 모터 A | D8 |
| 오른쪽 뒤 모터 B | D9 |
| HC-06 TXD → Arduino RX | D10 |
| HC-06 RXD ← Arduino TX | D11 |
| MG90S Signal | D12 |
| VL53L0X SDA | A4 |
| VL53L0X SCL | A5 |

## ToF 센서

| VL53L0X | 연결 |
|---|---|
| VIN | 5V 스텝다운 |
| GND | 공통 GND |
| SDA | Arduino A4 |
| SCL | Arduino A5 |

## 서보모터

| MG90S 선 | 연결 |
|---|---|
| 신호선 | Arduino D12 |
| VCC | 5V 스텝다운 |
| GND | 공통 GND |

## HC-06

| HC-06 | 연결 |
|---|---|
| TXD | Arduino D10 |
| RXD | Arduino D11 |
| VCC | 5V 스텝다운 |
| GND | 공통 GND |

SoftwareSerial 선언은 `SoftwareSerial bluetooth(10, 11);`이며 순서는 Arduino의 RX, TX입니다.

## 모터 드라이버

왼쪽 L9110S는 왼쪽 앞·뒤 모터를, 오른쪽 L9110S는 오른쪽 앞·뒤 모터를 제어합니다.

L9110S 전원은 6V 스텝다운 출력에 연결하고 Arduino와 GND를 공통으로 연결합니다.

## 전원

- 배터리: 11.1V Li-Po
- 제어부: 5V 스텝다운
- 모터부: 6V 스텝다운
- 모든 GND 공통 연결

## 방향이 반대로 움직일 때

특정 바퀴만 반대로 회전하면 해당 모터의 두 출력선을 서로 바꿉니다.

차량 전체가 전진 명령에서 후진하면 `moveForward()`와 `moveBackward()`의 HIGH/LOW 조합을 반대로 수정합니다.
