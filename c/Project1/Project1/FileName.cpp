#include <stdio.h>
#include <easyx.h>


int main(){

	initgraph(1000,500 );


	//��ȡ���ڵĻ�ͼ�豸�ı��
	HWND testhd= GetDesktopWindow();
	//��ȡ���ڵĻ�ͼ�豸
	HDC hdeskdc = GetWindowDC(testhd);
	/*while (1) {
		Rectangle(hdeskdc, 100, 100, 200, 200);
	}*/

	//��ȡ�����С
	int nwidth = GetDeviceCaps(hdeskdc, HORZRES);
	int nheight = GetDeviceCaps(hdeskdc, VERTRES);
	nwidth = 1920;
	nheight = 1080;
	//������ͼƬ
	IMAGE backG(nwidth, nheight);
	HDC himgdc = GetImageHDC(&backG);
	while (1) {
		
		//��ͼƬ�����п���-BitBIt   dworp rop��� -SRCCOPY
		BitBlt(himgdc, 0, 0, nwidth,nheight, hdeskdc, 0, 0, SRCCOPY);
		//printf("%d %d\n", nwidth, nheight);
		saveimage(L"1.jpg", &backG);
		loadimage(&backG, L"1.jpg",1000,500);
		putimage(0, 0, 1000, 500, &backG, 0, 0);
	}

	return 0;
}