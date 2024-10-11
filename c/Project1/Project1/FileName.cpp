#include <stdio.h>
#include <easyx.h>


int main(){

	initgraph(1000,500 );


	//获取窗口的绘图设备的编号
	HWND testhd= GetDesktopWindow();
	//获取窗口的绘图设备
	HDC hdeskdc = GetWindowDC(testhd);
	/*while (1) {
		Rectangle(hdeskdc, 100, 100, 200, 200);
	}*/

	//获取桌面大小
	int nwidth = GetDeviceCaps(hdeskdc, HORZRES);
	int nheight = GetDeviceCaps(hdeskdc, VERTRES);
	nwidth = 1920;
	nheight = 1080;
	//创建空图片
	IMAGE backG(nwidth, nheight);
	HDC himgdc = GetImageHDC(&backG);
	while (1) {
		
		//将图片将进行拷贝-BitBIt   dworp rop标记 -SRCCOPY
		BitBlt(himgdc, 0, 0, nwidth,nheight, hdeskdc, 0, 0, SRCCOPY);
		//printf("%d %d\n", nwidth, nheight);
		saveimage(L"1.jpg", &backG);
		loadimage(&backG, L"1.jpg",1000,500);
		putimage(0, 0, 1000, 500, &backG, 0, 0);
	}

	return 0;
}