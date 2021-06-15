#pragma once
/** @file main.h
  * @brief
  * @author teng.qing
  * @date 2021/5/13
  */

  // openssl
#include <openssl/ssl.h>
#include <openssl/err.h>

// socket
#ifdef  _WIN32
#include <windows.h> 
#include <WinSock2.h>

#else
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <resolv.h>

#endif

#include <iostream>
#include <thread>

void showCerts(SSL *ssl) {
	X509 *cert;
	char *line;
	cert = SSL_get_peer_certificate(ssl);
	if (cert != nullptr) {
		std::cout << "����֤����Ϣ:" << std::endl;
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		std::cout << "֤��: " << line << std::endl;
		free(line);
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		std::cout << "�䷢��: " << line << std::endl;
		free(line);
		X509_free(cert);
	}
	else {
		std::cout << "��֤����Ϣ��" << std::endl;
	}
}

/** @fn init_openssl
  * @brief ȫ�ֳ�ʼ��openssl�⣬ֻ��Ҫ����һ��
  * @return
  */
void init_openssl() {
	//SSL_library_init();
	SSL_load_error_strings();       // ��������SSL ������Ϣ
	OpenSSL_add_all_algorithms();   // ��������֧�ֵ��㷨
}

/** @fn create_context
  * @brief ����һ��ȫ��SSL_CTX���洢֤�����Ϣ
  * @return
  */
SSL_CTX *create_context() {
	const SSL_METHOD *method;
	SSL_CTX *ctx;

	/* ��SSL V2 �� V3 ��׼���ݷ�ʽ����һ��SSL_CTX ����SSL Content Text */
	/* Ҳ������SSLv2_server_method() ��SSLv3_server_method() ������ʾV2 ��V3 ��׼*/
	//method = SSLv3_server_method();
	method = SSLv23_client_method();

	ctx = SSL_CTX_new(method);
	if (!ctx) {
		perror("Unable to create SSL context");
		ERR_print_errors_fp(stderr);
		exit(EXIT_FAILURE);
	}

	return ctx;
}

/** @fn create_socket
  * @brief ����һ��������socket
  * @param [in]listenPort:�����˿�
  * @return
  */
int create_socket(std::string serverIp, uint16_t serverPort) {
	int sockFd = 0;
	struct sockaddr_in addr {};

	addr.sin_family = AF_INET;
	addr.sin_port = htons(serverPort);
	addr.sin_addr.s_addr = inet_addr(serverIp.c_str());

	sockFd = socket(PF_INET, SOCK_STREAM, 0);
	if (sockFd < 0) {
		printf("create socket error:%d", errno);
		exit(EXIT_FAILURE);
	}

	int ret = connect(sockFd, (struct sockaddr *) &addr, sizeof(sockaddr_in));
	if (ret != 0) {
		std::cout << "Connect err:" << errno << std::endl;
		exit(errno);
	}

	return sockFd;
}

/** @fn opensslErrorCheck
  * @brief opensslErrorCheck
  * @param [in]ssl: SSLʵ��
  * @param [in]retCode: SSL_read/SSL_write����ֵ
  * @param [in]isError: �Ƿ�ȷʵ�����˴���
  * @return
  */
void opensslErrorCheck(SSL *ssl, int retCode, bool &isError) {
	// ����ssl�Ĵ�����
	int sslErr = SSL_get_error(ssl, retCode);
	isError = true;

	switch (sslErr) {
	case SSL_ERROR_WANT_READ:
		std::cout << "SSL_ERROR_WANT_READ" << std::endl;
		isError = false;
		break;
	case SSL_ERROR_WANT_WRITE:
		std::cout << "SSL_ERROR_WANT_WRITE" << std::endl;
		isError = false;
		break;
	case SSL_ERROR_NONE: // û�д������������������û��ô������
		std::cout << "SSL_ERROR_WANT_WRITE" << std::endl;
		break;
	case SSL_ERROR_ZERO_RETURN:// == 0 ,����Զ˹ر�������
		std::cout << "SSL remote close the connection" << std::endl;
		break;
	case SSL_ERROR_SSL:
		std::cout << "SSL error:" << sslErr << std::endl;
		break;
	default:
		std::cout << "SSL unknown error:" << sslErr << std::endl;
		break;
	}
}

int tet_ssl_client() {
	SSL_CTX *ctx = nullptr;

	// ��ʼ��openssl
	init_openssl();
	std::cout << "init openssl success" << std::endl;

	// ��ʼ��socket��ͬ������Զ�˷�����
	//int socketFd = create_socket("10.0.72.202", 8433);
	int socketFd = create_socket("10.80.0.17", 8000);
	std::cout << "tcp connect remote success" << std::endl;

	// ����SSL_CTX������
	ctx = create_context();

	// ��socket�����SSLʵ����
	SSL *ssl = SSL_new(ctx);
	SSL_set_fd(ssl, socketFd);

	std::this_thread::sleep_for(std::chrono::seconds(6));

	// ����SSL���ӣ�����
	std::cout << "SSL_connect 2s later will connect and do hand shake..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "SSL_connect " << std::endl;
	int ret = SSL_connect(ssl);
	if (ret <= 0) {
		ERR_print_errors_fp(stderr);
		return 0;
	}
	std::cout << "handshake success" << std::endl;

	// ��ʾ�Է�֤����Ϣ
	std::cout << "Connected with " << SSL_get_cipher(ssl) << " encryption" << std::endl;
	showCerts(ssl);

	std::cout << "send hello server" << std::endl;

	std::string msg = "hello serve";
	SSL_write(ssl, msg.c_str(), msg.length());

	// wait server response
	char tempBuf[256] = {};
	ret = SSL_read(ssl, tempBuf, sizeof(tempBuf));
	if (ret <= 0) {
		std::cout << "SSL_read return <=0,ret=" << ret << std::endl;

		bool isError = false;
		opensslErrorCheck(ssl, ret, isError);

		if (isError) {
			std::cout << "SSL_read error,close" << std::endl;
		}
	}

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "exit ..." << std::endl;

	SSL_shutdown(ssl); // �ر�SSL����
	SSL_free(ssl);     // �ͷ�SSL��Դ
	close(socketFd);   // �ر�socket�ļ����
	SSL_CTX_free(ctx); // �ͷ�SSL_CTX��������Դ

	return 0;
}