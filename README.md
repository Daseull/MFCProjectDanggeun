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

프로젝트>속성>고급>문자집합>멀티 바이트 문자집합 사용

**디버깅 설정**

x64로 설정. 상단 툴바에서 선택 가능하다.

**DB 설정**

- db 이름
  pch.h 헤더 내
  DB_FILE_NAME에 해당하는 db가 *프로젝트 폴더(Danggeun_Client) 에 생성된다. 
- dll 에러
  https://enddldishfwk.tistory.com/8

- 그 외 레퍼런스
  https://www.notion.so/a17d7fb72db641a09c989aad5247ce19?v=64508266086f443b97330a230d835e28

**필요 파일들**

프로젝트 폴더의 res 폴더 내에

- bitmap1.bmp
- filled_1.bmp
- not_filled_2.bmp
- Danggeun_Client.ico
- DanggeunClient.rc2



업로드할 사진은 200*200 사이즈가 권장!
사이즈가 맞는 이미지파일들은 testimage폴더에 있습니다.

