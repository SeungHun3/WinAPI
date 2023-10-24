#pragma once
// 프로젝트 속성에서 미리 컴파일된 헤더 만들기로 변경
// 미리 컴파일된 헤더파일 이름명 똑같은 이름으로 헤더명 파일 만들어줌

// 이 프로젝트에서 모든 cpp파일들은 최상단에 pch 헤더파일을 항상 참조해야한다 -> cpp헤더파일에서 pch기능 사용가능
// 참조하지 않으면 컴파일 에러
// 모두가 미리 컴파일된 공통된 헤더를 참조하고 있어 컴파일 속도가 올라감
#include <windows.h>
#include <iostream>

#include <vector>
using std::vector;

#include "define.h"
#include "struct.h"