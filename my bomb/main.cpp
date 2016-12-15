#include <windows.h>
#include "common.h"
#include "res.h"
#include <iostream>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
char winName[] = "测试版";

LPRECT lpRect;
PWINDOWINFO pwi;

HDC dc;
HDC MenDC;
HBITMAP hbmp;
HINSTANCE hinst;

short **bomb;



int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
	hinst=hThisInstance;
	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */



	WNDCLASSEX wincl;        /* Data structure for the windowclass */

	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof (WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon (NULL, IDI_ASTERISK);
	wincl.hCursor = LoadCursor (NULL, IDC_CROSS);
	wincl.lpszMenuName ="Menu";                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx (&wincl))
		return 0;

	HMENU hmenuMain=LoadMenuA(hThisInstance,(LPCTSTR)"Menu001");


	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx (
		0 ,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		winName,		       /* Title Text */
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX , /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		262,                /* The programs width */
		289,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		hmenuMain,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);




	lpRect=(LPRECT)malloc(sizeof(RECT));
	pwi=(PWINDOWINFO)malloc(sizeof(WINDOWINFO));


	/* Make the window visible on the screen */
	ShowWindow (hwnd, nCmdShow);

	bomb=(short**)malloc(sizeof(short*)*12);
	for(int i=0;i<12;i++){
		bomb[i]=(short*)malloc(sizeof(short)*18);
		memset(bomb[i],0,18);
	}
	initBombs(bomb,16,10,20);
	showBombs(bomb,16,10);

	/* Run the message loop. It will run until GetMessage() returns 0 */

	while (GetMessage (&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)                  /* handle the messages */
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
			case IDM_ABOUT:
				//DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				MessageBoxA(hwnd,"About","About~~",NULL);
				break;
			case IDM_START:					// 开始
				MessageBox( hwnd, "开始", "操作提示", NULL );
				break;
			case IDM_1ST :					// 停止
				MessageBox( hwnd, "停止", "操作提示", NULL );
				break;
			case IDM_EXIT:					// 关闭
				DestroyWindow(hwnd);
				break;
			default:
				return DefWindowProc(hwnd, message, wParam, lParam);
			}
		break;
	case WM_CREATE:
//		MessageBoxA(hwnd,"asdf","asdf",0);

		return 0;
	case WM_DESTROY:
		PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
		break;
	case WM_KEYDOWN:
		//MessageBoxA(hwnd,"Hello","Hello Majesty",MB_ICONWARNING);
		break;
	case WM_MOUSEMOVE:



//		GetWindowInfo(hwnd,pwi);
//		GetWindowRect(hwnd,lpRect);
//
//		char buff[100];
//		sprintf(buff,"X:%3ld,Y:%3ld",(GetMessagePos() & 0x0000FFFF) - pwi->rcClient.left,
//			(GetMessagePos() & 0xFFFF0000)>>16 - pwi->rcClient.top);
		break;


//		break;
//	case WM_PAINT:
	case WM_LBUTTONDOWN:
	{

		GetWindowInfo(hwnd,pwi);
		GetWindowRect(hwnd,lpRect);

		int i=(GetMessagePos() & 0x0000FFFF) - pwi->rcClient.left;
		int j=(GetMessagePos() & 0xFFFF0000)/0x10000 - pwi->rcClient.top;
		///to make i&j
		int x=(j-2)/24+1,y=(i-3)/16+1;



//
//		char buff[10];
//		sprintf(buff,"x:%d\ty:%d\n",x,y);
//		MessageBoxA(hwnd,buff,buff,0);

		if(-1==clickToOpen(bomb,x,y)) MessageBoxA(hwnd,"BOOB","",0);
	}

	case WM_PAINT:{
		dc=GetDC(hwnd);//获得句柄
		MenDC=CreateCompatibleDC(dc);//建立一个内存DC

		hbmp=CreateCompatibleBitmap(dc,1024,768);//x,y为创建缓冲的宽度和高度 可以用桌面大小
		SelectObject(MenDC,hbmp);
		//绘制内存
		HPEN hp;
		hp=CreatePen(PS_SOLID,1,0x00FFFFFF);
		SelectObject(MenDC,hp);

		POINT pt[3];
		int polycount[1]={3};

		for(int i=1;i<=10;i++){
			for(int j=1;j<=16;j++){
				int k=j-1+(i-1)*10;
				if((bomb[i][j] & 0x0F00) == 0x0000 ) {
					if((i%2==1 && j%2==1) || (i%2==0 && j%2==0)){
						pt[0].x=3+12+15*(j-1);
						pt[0].y=3+24*(i-1);
						pt[1].x=3+12+15*(j-1)-12;
						pt[1].y=3+24*(i-1)+21;
						pt[2].x=3+12+15*(j-1)+12;
						pt[2].y=3+24*(i-1)+21;
					}
					else{
						pt[0].x=3+12+15*(j-1)-12;
						pt[0].y=3+24*(i-1);
						pt[1].x=3+12+15*(j-1)+12;
						pt[1].y=3+24*(i-1);
						pt[2].x=3+12+15*(j-1);
						pt[2].y=3+24*(i-1)+21;
					}
					PolyPolygon(MenDC,pt,polycount,1);
				}
				else{
					RECT rec;
					rec.left=3+12+15*(j-1)-6;
					rec.top=3+24*(i-1)+6;
					rec.right=3+12+15*(j-1)+6;
					rec.bottom=3+24*(i-1)+18 ;
					switch(bomb[i][j]){
					case BOS_NOHAVE_BOMB:
						break;
					case BOS_1:
						DrawTextA(MenDC,"1",1,&rec,DT_TOP);
						break;
					case BOS_2:
						DrawTextA(MenDC,"2",1,&rec,DT_TOP);
						break;
					case BOS_3:
						DrawTextA(MenDC,"3",1,&rec,DT_TOP);
						break;

					}
				}
	//			cout<<bomb[i][j]<<endl;
			}
		}

/*
		HBITMAP hbmpfromfile;
		hbmpfromfile=(HBITMAP)LoadImageA(hinst,"c:\\1.bmp",IMAGE_BITMAP,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
		cout<<hbmpfromfile<<endl;
		SelectObject(MenDC,hbmpfromfile);
*/

	//	DeleteObject(hp);
		//绘制窗口


		BitBlt(dc,0,0,300,300,MenDC,0,0,SRCCOPY);//把图形绘制到桌面
		ReleaseDC(hwnd,(HDC)MenDC);
		ReleaseDC(hwnd,(HDC)dc);

		cout<<".";
//		break;//这个不注释掉会有问题!
	}
	default:                      /* for messages that we don't deal with */
		return DefWindowProc (hwnd, message, wParam, lParam);
	}

	return 0;
}

