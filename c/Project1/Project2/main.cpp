#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <easyx.h>
#pragma comment(lib,"ws2_32.lib")

struct pack_header
{
	int type;//0-文本 1-图片
	int size;
};

SOCKET create_listen_socket(unsigned short port) {
	//2创建一个用来监听的socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	if (INVALID_SOCKET == sock) {
		printf("create socker fail\n");
		return -1;
	}
	//3绑定ip和端口
	struct sockaddr_in local = { 0 };
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr("0.0.0.0");
	if (-1 == bind(sock, (struct sockaddr*)&local, sizeof(local))) {
		printf("bind socket fail\n");
		return -1;
	}
	//4给socket开启监听属性
	if (-1 == listen(sock, 10)) {
		printf("listen sock fail\n");
		return -1;
	}
	return sock;
}

int main(int argc, char* argv[]) {
	initgraph(1280, 720);
	IMAGE img(1280, 720);

	//1开启网络权限
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//234-》2 创建listen_socket
	SOCKET listen_socket = create_listen_socket(8080);
	
	//3 等待客户端连接
	struct sockaddr_in client_addr;
	int socklen = sizeof(struct sockaddr_in);
	while (true) {
		SOCKET client_socket = accept(listen_socket, (struct sockaddr*)&client_addr, &socklen);
		if (INVALID_SOCKET == client_socket)
			continue;
		
		
		printf("new connect,ip:%s,port:%d", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		while (1) {
			//循环接收图片信息
			struct pack_header hdr;
			int ret = recv(client_socket,(char *)&hdr, sizeof(hdr), 0);
			if (ret <= 0)break;
			if (hdr.type == 0) {

			}
			else if (hdr.type == 1) {
				int size = hdr.size;//还剩余多少数据没有接受
				FILE* fp = fopen("s.jpg", "wb");
				char buffer[4096] = { 0 };
				while (size > 0) {
					//ret =recv(client_socket, buffer, size < 4096 ? size : 0,0);
					ret = recv(client_socket, buffer, size <= 4096 ? size : 4096, 0);
					if (ret <= 0) {
						fclose(fp);
						goto end;
					}
					size -= ret;
					if (nullptr != fp) 
						fwrite(buffer, 1, ret, fp);
					
				}
				if (nullptr != fp)
					fclose(fp);

			}
			//循环输出显示
			loadimage(&img, L"s.jpg", getwidth(), getheight());
			putimage(0, 0, 1280, 720, &img, 0, 0);
		}
	end:
		closesocket(client_socket);
	}

	
	
	
	
	return 0;


}