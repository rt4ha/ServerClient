#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <time.h>
#include <cmath>

using namespace std;

void menu()
{

	cout << "------------------------------- \n";
	cout << "1 - Hesap özeti \n";
	cout << "2 - Para yatır \n";
	cout << "3 - Para çek \n";
	cout << "4 - Transfer İşlemleri \n";
	cout << "5 - Çıkış \n";
	cout << "------------------------------- \n";


}

void main()
{
	setlocale(LC_ALL, "Turkish");
	
	string ipAddress = "127.0.0.1";			
	int port = 54000;						

	
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock" <<  endl;
		return;
	}

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << endl;
		WSACleanup();
		return;
	}

	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server" << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	char buf[4096];
	string userInput;

	do
	{
	
		cout << "Banka menüsüne erişmek için herhangi bir tuşa basıp giriş yapınız: ";
		
		getline(cin, userInput);

		if (userInput.size() > 0)	
		{

			setlocale(LC_ALL, "Turkish");

			string system_username = "r", system_pass = "1";
			string username, pass;

			cout << "Kullanıcı adı: ";
			cin >> username;
			cout << endl;

			cout << "Parola: ";
			cin >> pass;
			cout << endl;

			{
				if (system_username == username && system_pass == pass)
				{
					system("cls");
					cout << endl;
					cout << "Hoşgeldiniz... İşlem numarasını tuşlayarak devam edebilirsiniz." << endl;
					cout << endl;
				}
				else if (system_username != username && system_pass == pass)
				{
					system("cls");
					cout << endl;
					cout << "Kullanici adi hatali!";
					cout << endl;
					exit(EXIT_FAILURE);
				}
				else if (system_username == username && system_pass != pass)
				{
					system("cls");
					cout << endl;
					cout << "Parolaniz hatali! ";
					cout << endl;
					exit(EXIT_FAILURE);
				}
				else
				{
					system("cls");
					cout << endl;
					cout << "Kullanici adi ve Parola hatali! ";
					cout << endl;
					exit(EXIT_FAILURE);
				}
			}


			int giris;
			double totalbakiye = 1000;
			double yatirim, cekim;


			while (1)
			{
				menu();

				cout << endl;
				cout << "Seceneginiz: ";
				cin >> giris;

				switch (giris)
				{

				case 1:

					system("cls");
					cout << endl;

					cout << "Hesabinizda " << totalbakiye << "TL bulunuyor. \n";
					cout << endl;

					break;

				case 2:

					system("cls");
					cout << endl;
					cout << "Yatirilacak Tutar : ";
					cin >> yatirim;
					totalbakiye += yatirim;
					cout << endl;
					cout << "Para yatırıldı. Hesabinizda " << totalbakiye << "TL bulunuyor. İyi günler. " << endl;
					cout << endl;

					break;

				case 3:

					system("cls");
					cout << endl;
					cout << "Cekilecek Tutar: ";
					cin >> cekim;

					if (cekim > totalbakiye)
					{
						system("cls");
						cout << endl;
						cout << "Yetersiz Bakiye. \n";
					}
					else
					{
						system("cls");
						cout << endl;
						totalbakiye -= cekim;
						cout << "Kalan Bakiye : " << totalbakiye << "TL \n";
					}
					break;

				case 4:

					double gonder;
					int transfer, onay1, onay2;

					system("cls");
					cout << endl;
					cout << "Yapmak istediğiniz gönderim şekli nedir?\n";
					cout << endl;
					cout << "EFT işlemleri için '1' , \n";
					cout << endl;
					cout << "Havale için '2' tuşlayın.\n";
					cout << endl;
					cout << "Seceneginiz: ";
					cin >> transfer;

					if (transfer == 1)
					{
						cout << endl;
						cout << "Göndermek istediğiniz miktar: ";
						cin >> gonder;
						cout << endl;
						cout << "Bankamız EFT için bir miktar para kesecek (1.12TL) onaylıyor musunuz? [evet = 1 / hayır = 2]: ";
						cin >> onay1;

						if (onay1 == 1 && gonder < totalbakiye)
						{
							system("cls");
							totalbakiye = totalbakiye - (gonder + 1.12);
							cout << endl;
							cout << "EFT işleminiz tamamlandı. " << "Hesabınızda " << totalbakiye << "TL bulunuyor." << endl;

						}

						else if (onay1 == 1 && gonder > totalbakiye)
						{
							system("cls");
							cout << endl;
							cout << "Yetersiz Bakiye. \n";
						}

						else if (onay1 == 2)
						{
							system("cls");
							break;
						}
						break;
					}


					if (transfer == 2)
					{
						cout << endl;
						cout << "Göndermek istediğiniz miktar: ";
						cin >> gonder;
						cout << endl;
						cout << "Bankamız havale için bir miktar para kesecek (1.3TL) onaylıyor musunuz? [evet = 1 / hayır = 2]: ";
						cin >> onay2;

						if (onay2 == 1 && gonder < totalbakiye)
						{
							system("cls");
							totalbakiye = totalbakiye - (gonder + 1.3);
							cout << endl;
							cout << "EFT işleminiz tamamlandı. " << "Hesabınızda " << totalbakiye << "TL bulunuyor." << endl;

						}

						else if (onay2 == 1 && gonder > totalbakiye)
						{
							system("cls");
							cout << endl;
							cout << "Yetersiz Bakiye. \n";
						}

						else if (onay2 == 2)
						{
							system("cls");
							break;
						}
						break;

					}

					break;

				case 5:

					exit(EXIT_FAILURE);

					break;


				}
			}
			
			
		}
		
	} while (userInput.size() > 0);
	
	
	closesocket(sock);
	WSACleanup();
}