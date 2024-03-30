#include "WinAPI_Header.h"

int MercuryRadius = 15;
float MercuryOx = 0; MercuryOy = 0;
float MercuryAngle = 0;
HPEN hPenMercury;

int VenusRadius = 30;
float VenusOx = 0; VenusOy = 0;
float VenusAngle = 0;
HPEN hPenVenus;

int EarthRadius = 25;
float EarthOx = 0; EarthOy = 0;
float EarthAngle = 0;
HPEN hPenEarth;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR arg, int ncmdshow)
{
	WNDCLASS SoftWareMainClass;
	SoftWareMainClass = NewClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_HAND), hInst,
		LoadIcon(NULL, IDI_WINLOGO), L"window", SoftWareProcedure);
	if (!RegisterClassW(&SoftWareMainClass))
		return -1;

	MSG	SoftWareMessage = { NULL };
	HWND hWnd;
	hWnd = CreateWindow(L"window", L"Solar System", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		PositionWindows_X, PositionWindows_Y, WidthWindows, HeightWindows, NULL, NULL, NULL, NULL);
	if (!hWnd)
		return -1;

	while (GetMessage(&SoftWareMessage, NULL, NULL, NULL))
	{
		TranslateMessage(&SoftWareMessage);
		DispatchMessage(&SoftWareMessage);
	}

	return 0;
}

LRESULT CALLBACK SoftWareProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	UINT_PTR ptr;
	ptr = SetTimer(hWnd, IDT_TIMER, 1, NULL);

	switch (msg) {

	case WM_CREATE:

		hPenMercury = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hPenVenus   = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		hPenEarth   = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));

		break;

	case WM_TIMER: {

		switch (ptr) {

			case IDT_TIMER: {

				MercuryAngle += 0.07;
				MercuryOx = SolarCentryX + (MercuryRadius + 100) * cos(MercuryAngle);
				MercuryOy = SolarCentryY + (MercuryRadius + 100) * sin(MercuryAngle);

				VenusAngle   += 0.06;
				VenusOx   = SolarCentryX + (VenusRadius + 200) * cos(VenusAngle);
				VenusOy   = SolarCentryY + (VenusRadius + 200) * sin(VenusAngle);

				EarthAngle   += 0.05;
				EarthOx   = SolarCentryX + (EarthRadius + 300) * cos(EarthAngle);
				EarthOy   = SolarCentryY + (EarthRadius + 300) * sin(EarthAngle);


				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
		}
		
	}

	case WM_PAINT: {

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		FillRect(hdc, &ps.rcPaint, GetSysColorBrush(COLOR_GRAYTEXT)); // < -- Удаление предыдущего кадра 

		CreateSolar(hWnd); // < -- Создание Солнца

		SelectObject(hdc, hPenMercury);
		Ellipse(hdc, MercuryOx - MercuryRadius, MercuryOy - MercuryRadius, 
			         MercuryOx + MercuryRadius, MercuryOy + MercuryRadius);

		SelectObject(hdc, hPenVenus);
		Ellipse(hdc, VenusOx - VenusRadius, VenusOy - VenusRadius, 
			         VenusOx + VenusRadius, VenusOy + VenusRadius);

		SelectObject(hdc, hPenEarth);
		Ellipse(hdc, EarthOx - EarthRadius, EarthOy - EarthRadius, 
			         EarthOx + EarthRadius, EarthOy + EarthRadius);

		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:

		KillTimer(hWnd, IDT_TIMER);
		PostQuitMessage(0);
		break;

	default:

		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
