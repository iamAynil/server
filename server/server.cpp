#include "xmlrpc/XmlRpc.h"
#include <conio.h>
#include <iostream>

using namespace XmlRpc;
using namespace std;

class Sum : public XmlRpcServerMethod // класс метода суммы, наследуется от XmlRpcServerMethod
{
public:
	explicit Sum(XmlRpcServer* server) : XmlRpcServerMethod("127.0.0.1", server) {} // вызов конструктора XmlRpcServerMethod

	void execute(XmlRpcValue& params, XmlRpcValue& result) override// устанавливаем соединение с клиентом
	{
		cout « "Соединение с клиентом установлено, клиент передал следующие параметры:" « std::endl;
		int sum = 0;
		for (int i = 0; i < params.size(); i++)
		{
			std::cout « params[i] « std::endl; // params - секция, где задаются параметры
			sum += (int)params[i];
		}
		result[0] = sum;
	}
};
int main()
{
	system("chcp 1251");
	int port = 20000; // объявляем переменную - порт, где будем получать подключения от клиентов
	XmlRpcServer server; // создаем класс сервера
	server.bindAndListen(port); // говорим серверу, где слушать
	Sum sumValues(&server); // создаем класс метода суммы(класс сам добавиться внутри сервера)
	server.work(-1.0); // Обрабатывать клиентские запросы в течение указанного времени.
	server.exit(); // Временно прекратите обработку клиентских запросов и выйдите из метода work().
	server.shutdown(); // Закройте все соединения с клиентами и файловым дескриптором сокета.
}