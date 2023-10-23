// vs19_WinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "vs19_WinAPI.h"

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
    // GetMessage : 메세지 큐에서 메세지 확인 될 때까지 대기, msg.message == WM_QUIT 이면 false 반환 -> 프로그램종료
    // PeekMessage : 메세지 유무와 관계없이 반환 // 메세지가 있는지 보고 있지만 확인한 메세지가 있을경우 큐에서 제거 // 메세지가 없어도 반환되기에 while문 조건에 넣지 못함
    //             : 메세지큐에서 메세지를 확인한 경우 true, 메세지가 없는 경우 false 반환 

    DWORD dwPrevCount = GetTickCount();
    DWORD dwAccCount = 0;
    while (1) 
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))// 반환시 메세지가 있으면 true, 없으면 false
        {
            int iTime = GetTickCount();

            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // TranslateAccelerator 단축키 // 리소스뷰의 Menu, Accelerator 폴더들 열어보자
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg); // 멀티스레드로 메세지 처리함수 실행
            }

            dwAccCount += (GetTickCount() - iTime);
        }
        else // 기존엔 timer로 강제 메세지큐를 실행했다면 메세지가 없어도 호출받을 수 있음 
        {
            DWORD dwCurCount = GetTickCount();
            if (dwCurCount - dwPrevCount > 1000)
            {
                float fRatio = (float)dwAccCount / 1000.0f;

                wchar_t szBuff[50] = {};
                swprintf_s(szBuff, L"비율 : %f",fRatio); // 실수를 문자열로 바꿔줌
                SetWindowText(g_hwnd, szBuff);// 윈도우 타이틀창

                dwPrevCount = dwCurCount;
            }
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
int g_x = 0;
int g_y = 0;


#include <vector>
using std::vector;

struct tObjInfo
{
    POINT g_ptObjPos;
    POINT g_ptObjScale;
};

vector<tObjInfo> g_vecInfo; // 힙메모리에서 오브젝트를 관리

// 좌상단
POINT g_ptLT;
// 우하단
POINT g_ptRB;

bool bLBtnDown = false;
int test = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // wParam = 키보드 입력 값 , LParam = 마우스 좌표 = 총 4바이트 // 2바이트씩 x,y 좌표 => 비트연산
{
    switch (message) // 메세지가 없으면 화면을 그리지 않는다는 문제 => 강제로 메세지를 발생시키는 방법 => 핸들러 전역변수로 설정 후 타이머호출
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

            //Rectangle(hdc,0,0,test,test);
            //test++; // 크기가 계속 커지는것으로 봤을때 프레임마다 업데이트 되고있음

            // 직접 Pen, Brush을 만들어서 DC에 지급
            HPEN hRedPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));

            // SelectObject함수가 범용적이라 brush, pen .. 여러 방면으로 사용됨 => 캐스팅 필수
            // 기본 Pen, Brush ID값을 Default로 받아둠
            HPEN hDefaultPen = (HPEN)SelectObject(hdc, hRedPen); 
            HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hdc, hBlueBrush);

            if (bLBtnDown)
            {
                Rectangle(hdc,
                    g_ptLT.x, g_ptLT.y,
                    g_ptRB.x, g_ptRB.y); //변경된 Pen, Brush으로 사각형 그리기
            }
            // 여기서 픽셀하나하나는 메모리이다. 버퍼에 값을 저장해놓은 후 눈에 보이는 GUI를 표현
            // 픽셀당 3바이트(rgb) : 1920* 1080  = 6,220,800 바이트 (한 화면을 구성하는 메모리)



            // 추가된 사각형 그리기 => 화면이 매우 깜빡거린다=> 호출속도의 문제가 아닌 사각형이 만들어지는과정에 대한 우리가 인식하는 프레임 타이밍의 문제
            // =>백그라운드에 다그리고 나서 화면을 바꿔치기하는 방법으로 해결
            for (size_t i = 0; i < g_vecInfo.size(); ++i)
            {
                Rectangle(hdc,
                    g_vecInfo[i].g_ptObjPos.x - g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y - g_vecInfo[i].g_ptObjScale.y / 2,
                    g_vecInfo[i].g_ptObjPos.x + g_vecInfo[i].g_ptObjScale.x / 2,
                    g_vecInfo[i].g_ptObjPos.y + g_vecInfo[i].g_ptObjScale.y / 2);
            }

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

    case WM_KEYDOWN: // 계속 누르고 있을 경우 1~2초 간격두고 움직임(시간간격 두고 누르고 있는지 파악 후 이벤트 지속발생)
        {
            switch (wParam)
            {
            case VK_UP: 
                {
                    //g_ptObjectPos.y -= 10; // 드로우가 변경할때마다 업데이트 되지 않는다 => 무효화영역발생때만 드로우 해라는 명령이기때문
                    InvalidateRect(hWnd,nullptr, true); // 강제로 무효화 영역이 발생했다는 이벤트만듦 // 핸들러 지정, 전체영역(nullptr) , 기존영역 지울지 여부(버퍼에 메모리 남아있어서) = true
                }
                break;
            case VK_DOWN:
                {
                    //g_ptObjectPos.y += 10;
                    InvalidateRect(hWnd, nullptr, true);
                }
                break; 

            case VK_LEFT:
                {
                    //g_ptObjectPos.x -= 10; 
                    InvalidateRect(hWnd, nullptr, true); 
                }
                break;
            case VK_RIGHT:
                {
                    //g_ptObjectPos.x += 10; 
                    InvalidateRect(hWnd, nullptr, true);
                }
                break;
            default:
                break;
            }
        }
        break;

    case WM_LBUTTONDOWN:
        {
            g_ptLT.x = LOWORD(lParam);
            g_ptLT.y = HIWORD(lParam);
            bLBtnDown = true;
        }
        break;
    case WM_MOUSEMOVE:
        {
            g_ptRB.x = LOWORD(lParam);
            g_ptRB.y = HIWORD(lParam);
            InvalidateRect(hWnd, nullptr, true);
        }
        break;
    case WM_LBUTTONUP:
    {
        tObjInfo info = {};
        info.g_ptObjPos.x = (g_ptLT.x + g_ptRB.x) / 2;
        info.g_ptObjPos.y = (g_ptLT.y + g_ptRB.y) / 2;

        info.g_ptObjScale.x = abs(g_ptLT.x - g_ptRB.x);
        info.g_ptObjScale.y = abs(g_ptLT.y - g_ptRB.y);

        g_vecInfo.push_back(info);

        bLBtnDown = false;
        InvalidateRect(hWnd, nullptr, true);
    }
    break;

    case WM_TIMER:
        {
        int a = 0;
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
