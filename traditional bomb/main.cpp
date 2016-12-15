#include <windows.h>
#include "common.h"
#include "res.h"
#include <iostream>
using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "CodeBlocksWindowsApp";
char winName[] = "MyWindows";

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
		171,                /* The programs width */
		251,                 /* and height in pixels */
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
		bomb[i]=(short*)malloc(sizeof(short)*12);
		memset(bomb[i],0,12);
	}
	initBombs(bomb,10,10,10);
	showBombs(bomb,10,10);

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
			case IDM_START:					// ��ʼ
				MessageBox( hwnd, "��ʼ", "������ʾ", NULL );
				break;
			case IDM_1ST :					// ֹͣ
				MessageBox( hwnd, "ֹͣ", "������ʾ", NULL );
				break;
			case IDM_EXIT:					// �ر�
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
		int x=(j-45)/16+1,y=(i-3)/16+1;




//		char buff[10];
//		sprintf(buff,"x:%d\ty:%d\n",x,y);
//		MessageBoxA(hwnd,buff,buff,0);
		if(-1==clickToOpen(bomb,x,y)) MessageBoxA(hwnd,"BOOB","",0);
	}

	case WM_PAINT:
		dc=GetDC(hwnd);//��þ��
		MenDC=CreateCompatibleDC(dc);//����һ���ڴ�DC

		hbmp=CreateCompatibleBitmap(dc,800,600);//x,yΪ��������Ŀ�Ⱥ͸߶� �����������С
		SelectObject(MenDC,hbmp);
		//�����ڴ�
		HPEN hp;
		hp=CreatePen(PS_SOLID,1,0x00FFFFFF);
		SelectObject(MenDC,hp);


		for(int i=1;i<=10;i++){
			for(int j=1;j<=10;j++){
				int k=j-1+(i-1)*10;
				if((bomb[i][j] & 0x0F00) == 0x0000 ) {
					Rectangle(MenDC,3+(k%10)*16,45+(k/10)*16,3+(k%10)*16+14,45+(k/10)*16+14);
				}
				else{
					RECT rec;
					rec.left=3+(k%10)*16;
					rec.top=45+(k/10)*16;
					rec.right=3+(k%10)*16+14;
					rec.bottom=45+(k/10)*16+14;
					switch(bomb[i][j]){
					case BOS_NOHAVE_BOMB:
						break;
					case BOS_1:
						DrawTextA(MenDC,"1",1,&rec,DT_CENTER);
						break;
					case BOS_2:
						DrawTextA(MenDC,"2",1,&rec,DT_CENTER);
						break;
					case BOS_3:
						DrawTextA(MenDC,"3",1,&rec,DT_CENTER);
						break;
					case BOS_4:
						DrawTextA(MenDC,"4",1,&rec,DT_CENTER);
						break;
					case BOS_5:
						DrawTextA(MenDC,"5",1,&rec,DT_CENTER);
						break;
					case BOS_6:
						DrawTextA(MenDC,"6",1,&rec,DT_CENTER);
						break;
					case BOS_7:
						DrawTextA(MenDC,"7",1,&rec,DT_CENTER);
						break;
					case BOS_8:
						DrawTextA(MenDC,"8",1,&rec,DT_CENTER);
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
		//���ƴ���


		BitBlt(dc,0,0,300,300,MenDC,0,0,SRCCOPY);//��ͼ�λ��Ƶ�����
		ReleaseDC(hwnd,(HDC)MenDC);
		ReleaseDC(hwnd,(HDC)dc);

		cout<<".";
//		break;//�����ע�͵���������!
	default:                      /* for messages that we don't deal with */
		return DefWindowProc (hwnd, message, wParam, lParam);
	}

	return 0;
}

