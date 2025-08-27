# fdcan-gui
 


## 개요 
- STM32G4-FDCAN GUI 프로그램 

## 개발환경
- python3
- PySide6 6.5.0

## 설치하기
- 패키지 설치
  ```
  pip install -r requirements.txt

  ```
- 실행하기
  ```
  python fdcan-gui.py
  or
  python3 fdcan-gui.py
  ```

## 스캔 모드 설정

### 개요
btnScan 버튼의 동작을 설정할 수 있는 3가지 모드가 있습니다.

### 모드 종류

1. **모든 COM 포트 표시 모드** (`all_ports`)
   - 시스템에 연결된 모든 COM 포트를 표시
   - 사용자가 직접 원하는 포트를 선택 가능
   - FDCAN 장치는 자동으로 식별되어 표시됨

2. **FDCAN 전용 모드** (`fdcan_only`)
   - FDCAN 장치(VID: 0x0483, PID: 0x5740)만 표시
   - 기존 기능과 동일

3. **라디오 버튼 모드** (`use_radio`)
   - 기존 라디오 버튼에 따라 스캔 동작 결정
   - FDCAN 전용 또는 모든 장치 중 선택

### 설정 방법

#### 1. config.ini 파일에서 설정
```ini
[config]
scan_mode = all_ports
```

#### 2. 코드에서 동적 설정
```python
# 모든 COM 포트 표시
main_window.setScanMode("all_ports")

# FDCAN 전용
main_window.setScanMode("fdcan_only")

# 라디오 버튼 사용
main_window.setScanMode("use_radio")
```

### 기본값
- 기본 스캔 모드: `all_ports` (모든 COM 포트 표시)
  