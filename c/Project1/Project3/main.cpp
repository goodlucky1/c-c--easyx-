#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <easyx.h>
#pragma comment(lib,"ws2_32.lib")
struct pack_header
{
	int type;//0-�ı� 1-ͼƬ
	int size;
};

int main() {
	//��������Ȩ��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);



	//��ȡ���洰��
	HWND ndeskD = GetDesktopWindow();
	//��ȡ�����ͼ�豸
	HDC ndeskDc = GetWindowDC(ndeskD);
	//��ȡ�����С
	int ndeskwidth = GetDeviceCaps(ndeskDc, HORZRES);
	int ndeskheight = GetDeviceCaps(ndeskDc, VERTRES);
	//������ͼƬ
	IMAGE backimg(ndeskwidth, ndeskheight);
	//��ȡͼƬHDC
	HDC nimgDc = GetImageHDC(&backimg);




	//����socket
	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (INVALID_SOCKET == client_socket) {
		printf("create socker fail\n");
		return -1;
	}
		//���ӷ�����
		struct sockaddr_in target = { 0 };
		target.sin_family = AF_INET;
		target.sin_port = htons(8080);
		target.sin_addr.s_addr = inet_addr("127.0.0.1");
		if (-1 == connect(client_socket, (struct sockaddr*)&target, sizeof(struct sockaddr))) {
			printf("connect server fail");
			return -1;
		}
		while (1) {

			//����
			BitBlt(nimgDc, 0, 0, 1920, 1080, ndeskDc, 0, 0, SRCCOPY);

			//����
			saveimage(TEXT("c.jpg"), &backimg);
			//���ͣ�Э����ƣ�
			//�ȷ�������ͷ��
			struct pack_header hdr = { 1 };
			FILE* fp = fopen("c.jpg", "rb");
			if (nullptr == fp) continue;
			//�õ��ı���С
			fseek(fp, 0, SEEK_END);
			hdr.size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			if (hdr.size <= 0) {
				fclose(fp);
				continue;
			}
			//����ͷ
			int ret= send(client_socket, (const char*)&hdr, sizeof(hdr), 0);
			if (ret <= 0) break;
			//����ͼƬ����
			char buffer[1024] = { 0 };
			while (1) {
				ret= fread(buffer, 1, 1024, fp);
				if (ret <= 0)break;
				ret = send(client_socket,buffer, ret, 0);
				if (ret == SOCKET_ERROR) {
					int error = WSAGetLastError();
					printf("Send failed with error: %d\n", error);
					fclose(fp);
					goto end;
				}
				/*if (ret <= 0) {
					fclose(fp);
					goto end;

				}*/
			}
			fclose(fp);

		}
	end:
		closesocket(client_socket);


	return 0;
}