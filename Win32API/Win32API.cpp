// vs19_WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"
#include "framework.h"
#include "Win32API.h"

#include "CCore.h" // 프로그램의 핵심역할로 설계 중..

#include <crtdbg.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND      g_hwnd; // 메인 윈도우 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//SAL , 주석언어 ex) _In_ , _In_opt_ , APIENTRY ...//사용시 실제로 무시됨, 적어놓음으로써 주석과 같은 정보를 얻기위한 용도
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,        // _In_ : 입력된다라는 식의 정보인지, hInstance : 실행된 프로세스의 시작주소
    _In_opt_ HINSTANCE hPrevInstance, // _In_opt_ : 입력해도되고 안해도되는 옵션이다라는 추측가능 , hPrevInstance : 이전의 실행된 인스턴스가 있다면 해당 주소 반환 => 현재 시스템상 의미는 없음

    // 예를 들어 프로그램을 여러개 실행했다면 hPrevInstance를 기반으로 hInstance가 실행된다
    // 예전엔 여러 hInstance 를 실행하고 메모리주소를 달리했지만 현재는 가상메모리를 사용하고 있어 같은 메모리주소를 보여준다(가상으로 잡아줌)
    // 프로세스별로 서로의 실제주소를 알수없다 => 같은 주소를 사용하더라도 다른 프로세스라면 물리적인 주소는 다르다

    _In_ LPWSTR    lpCmdLine, // 프로그램이 실행될때 cmd 입력값을 받아옴
    _In_ int       nCmdShow)
{

    //메모리 릭(누수) 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(53465461456416) //문제가 생겼을때 해당지점에 중단점 걸어주는 함수






    UNREFERENCED_PARAMETER(hPrevInstance);  // 아무의미없이 일단 적어줌 사실상 없어도 됨 
    UNREFERENCED_PARAMETER(lpCmdLine);      // 매크로 사용법 알려주려 하는듯

    // TODO: 여기에 코드를 입력합니다.


    // 전역 문자열을 초기화합니다. // szTitle, szWindowClass 에 정보넣기
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32API, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보등록(어떤 형태를 띄울것인지)
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다: 윈도우 생성
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화

    if (FAILED(CCore::GetInst()->init(g_hwnd, POINT{ 1280,768 })))
    {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);
        return FALSE;
    }




    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32API));

    MSG msg;
    // GetMessage : 메세지 큐에서 메세지 확인 될 때까지 대기, msg.message == WM_QUIT 이면 false 반환 -> 프로그램종료
    // PeekMessage : 메세지 유무와 관계없이 반환 // 메세지가 있는지 보고 있지만 확인한 메세지가 있을경우 큐에서 제거 // 메세지가 없어도 반환되기에 while문 조건에 넣지 못함
    //             : 메세지큐에서 메세지를 확인한 경우 true, 메세지가 없는 경우 false 반환 
    // 메세지큐 이벤트 : 포커싱 되어있지 않은 경우 메세지 큐가 들어오지 않음 => 비동기 이벤트로 변경

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))// 반환시 메세지가 있으면 true, 없으면 false
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // TranslateAccelerator 단축키 // 리소스뷰의 Menu, Accelerator 폴더들 열어보자
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); // 멀티스레드로 메세지 처리함수 실행
            }

        }
        //메세지가 발생하지 않는 대부분의 시간
        else // 기존엔 timer로 강제 메세지큐를 실행했다면 메세지가 없어도 호출받을 수 있음 
        {
            // Game 코드 수행
            // 디자인패턴 : 싱글톤
            CCore::GetInst()->progress();


        }
    }

    return (int)msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // 구조체 내용에 각각 초기화

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32API));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32API);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 윈도우에서 실제 실행되는 코드(숨김처리되어있음)
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    g_hwnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hwnd)
    {
        return FALSE;
    }

    ShowWindow(g_hwnd, nCmdShow);// ID를 받은 윈도우 객체(핸들러)를 보이게(true), 안보이게(false) 해라
    UpdateWindow(g_hwnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // wParam = 키보드 입력 값 , LParam = 마우스 좌표 = 총 4바이트 // 2바이트씩 x,y 좌표 => 비트연산
{
    switch (message) // 메세지가 없으면 화면을 그리지 않는다는 문제 => 강제로 메세지를 발생시키는 방법: 핸들러 전역변수로 설정 -> 타이머호출 or PeekMessage 호출
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT: // 무효화 영역이 발생한경우 
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);



        EndPaint(hWnd, &ps);
    }
    break;

    case WM_KEYDOWN: // 계속 누르고 있을 경우 1~2초 간격두고 움직임(시간간격 두고 누르고 있는지 파악 후 이벤트 지속발생)
    {

    }
    break;

    case WM_LBUTTONDOWN:
    {
    }
    break;
    case WM_MOUSEMOVE:
    {
    }
    break;
    case WM_LBUTTONUP:
    {
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 플레이어 미사일 종류추가
// 몬스터 미사일 패턴