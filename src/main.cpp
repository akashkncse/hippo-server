#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	// Server Socket Creation
	int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	int port = 8000;
	sockaddr_in info;
	info.sin_port = htons(port);
	info.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &info.sin_addr);

	if (bind(server_fd, (sockaddr *)&info, sizeof(info)))
	{
		perror("bind() failed");
		return 0;
	}

	if (listen(server_fd, 10))
	{
		perror("listen() failed");
		return 0;
	}

	int client_fd = accept(server_fd, nullptr, nullptr);

	char buffer[2048] = {0};
	std::string data;
	std::string headers;
	// int bytesRead = recv(client_fd, buffer, sizeof(buffer), 0);
	int bytesRead = 0;
	while (bytesRead = recv(client_fd, buffer, sizeof(buffer), 0))
	{
		for (int i = 0; i < bytesRead; i++)
		{
			data += buffer[i];
		}
		int pos;
		if (data.find("\r\n\r\n") != std::string::npos)
		{
			pos = data.find("\r\n\r\n");
			headers += data.substr(0, pos);
			break;
		}
	}

	std::cout << "Successful retrieval of headers!" << std::endl;
	std::cout << "----------RAW-----------" << std::endl;
	std::cout << headers << std::endl;

	// if (bytesRead > 0)
	// {
	// 	std::cout << "--------RAW---------" << std::endl;
	// 	std::cout << buffer << std::endl;
	// 	std::cout << "--------END---------" << std::endl;
	// }

	std::string response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 18\r\n"
		"Connection: close\r\n"
		"\r\n"
		"Fastest C++ Server";

	send(client_fd, response.c_str(), response.size(), 0);
	close(server_fd);
	close(client_fd);
}
