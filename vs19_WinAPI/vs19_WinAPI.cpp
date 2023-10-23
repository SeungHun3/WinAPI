// vs19_WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "vs19_WinAPI.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
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
    UNREFERENCED_PARAMETER(hPrevInstance);  // 아무의미없이 일단 적어줌 사실상 없어도 됨 
    UNREFERENCED_PARAMETER(lpCmdLine);      // 매크로 사용법 알려주려 하는듯

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다. // szTitle, szWindowClass 에 정보넣기
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VS19WINAPI, szWindowClass, MAX_LOADSTRING);

    // 윈도우 정보등록(어떤 형태를 띄울것인지)
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다: 윈도우 생성
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 테이블 정보 로딩
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VS19WINAPI));

    MSG msg;
    msg.message;
    msg.lParam;
    msg.hwnd; // 하나의 프로세스 안에서 창을 여러개 만들 수 있음 // 메세지를 받을 하나의 창
    msg.pt;
    msg.time;
    // 메세지 구조체 메모리에 주소값 넘겨 GetMessage로 값 담아준다
    // 
    // 기본 메시지 루프입니다:
    // 메세지 큐에서 메세지 확인할때까지 대기(while 문 무한루프)
    // 포커싱되어있는 프로그램에 메세지 큐{ 다양한 이벤트들 ex) 클릭메세지(이벤트) }에 담아서 처리 
    // 카톡, 그림판 열림 -> 그림판 포커싱 -> 메세지 큐 그림판 프로그램 담음 -> 클릭이벤트 -> 그림판 -> 드로우
    while (GetMessage(&msg, nullptr, 0, 0))
        // msg.message == WM_QUIT 일경우 false반환 -> 프로그램 종료(while 탈출)
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // TranslateAccelerator 단축키 // 리소스뷰의 Menu, Accelerator 폴더들 열어보자
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); // 멀티스레드로 메세지 처리함수 실행
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex; // 구조체 내용에 각각 초기화

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VS19WINAPI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VS19WINAPI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex); // 윈도우에서 실제 실행되는 코드(숨김처리되어있음)
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);// ID를 받은 윈도우 객체(핸들러)를 보이게(true), 안보이게(false) 해라
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
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
        // 예전엔 화면데이터가 비트맵구조로 되어있어 다른프로그램이 실행되며 창이 가려진 부분이 생기고 다시 포커싱하면 생겨나는 부분이 무효화영역이었음
        // 현재는 프로그램을 최소화하여 아예 보이지 않게했다가 다시 프로그램을 포커싱하면 무효화영역이 발생
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // init instance 로 윈도우를 만들어놓은 객체(윈도우 핸들)를 PAINTSTRUCT 주소에 넘김
            //HDC; // Device Context 란 그리기 동작을 할 수 있게 그리기 작업을 수행하는데 필요한 데이터의 집합체
            //DC의 목적지는 hWnd
            //DC의 기본펜 = black
            //DC의 기본 브러쉬는 White
            
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...



            // 직접 Pen, Brush을 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // SelectObject함수가 범용적이라 brush, pen .. 여러 방면으로 사용됨 => 캐스팅 필수
            // 기본 Pen, Brush ID값을 Default로 받아둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); 
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);


            Rectangle(hdc, 10, 10, 110, 110); //변경된 Pen, Brush으로 사각형 그리기

            // 여기서 픽셀하나하나는 메모리이다. 버퍼에 값을 저장해놓은 후 눈에 보이는 GUI를 표현
            // 픽셀당 3바이트(rgb) : 1920* 1080  = 6,220,800 바이트 (한 화면을 구성하는 메모리)


            // DC의 Pen, Brush을 원래 펜으로 되돌림
            SelectObject(hdc, hDefaultPen);
            SelectObject(hdc, hDefaultBrush);

            //다쓴 RedPen, BlueBrush 삭제요청
            DeleteObject(hRedPen); 
            DeleteObject(hBlueBrush);


            
            EndPaint(hWnd, &ps);
            //그리고 나서 주소 해제

            /* 같은 프로그램의 커널 오브젝트를 여러 구조체(여러 ID값)로 구분지어 놓은 이유 => 개발적으로 구분지어 편하게 사용하기 위한 용도(실수방지)
            * 
            HWND; // 윈도우라는 커널오브젝트 ID값을 받기 위한 값
            HPEN; // PEN이라는 커널 오브젝트 ID값을 받기 위한 값
            HBRUSH;// BRUSH라는 커널 오브젝트 ID값을 받기 위한 값 
            HDC; // Device Context 커널 오브젝트 ID값을 받기 위한 값
            */

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
