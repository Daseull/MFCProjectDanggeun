# 오렌지마켓 (feat. 당근마켓)
세종대학교 2020학년도 동계 계절학기 심화프로그래밍설계 과목의 <야너두팔수있어>팀 프로젝트 결과물 레포입니다.

## 팀 소개
| 이름         | Github                        |
| ------------ | ----------------------------- |
| 이수진(팀장) | https://github.com/rachell7   |
| 김다슬       | https://github.com/Daseull    |
| 이현동       | https://github.com/cmoweg     |
| 조국희       | https://github.com/jokukhee99 |



## 프로젝트 소개

## 개발환경
- Framework: C++ MFC
- DB: SQLite3
- Editor: Visual Studio IDE 2019

## 아키텍처

## 실행 환경 설정
**Project Properties**
```

General(Output Dir): $(ProjectDir)$(Platform)\$(Configuration)\
Debugging(Environment): PATH=$(ProjectDir)SQlite3;%PATH%
C/C++(General/Additional Include Directories): $(ProjectDir)\SQlite3;%(AdditionalIncludeDirectories)
Linker(General/Additional Library Directories): $(ProjectDir)\SQlite3

```

**멀티바이트**

구성 속성 -> 일반 -> 문자 집합 -> 멀티바이트 설정

**디버깅 설정**

x64로 설정. 상단 툴바에서 선택 가능하다.

**DB 설정**

- db 이름
  pch.h 헤더 내
  DB_FILE_NAME에 해당하는 db가 *프로젝트 폴더(Danggeun_Client) 에 생성된다. 
- dll 에러
  https://enddldishfwk.tistory.com/8

