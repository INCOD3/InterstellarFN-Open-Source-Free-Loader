#include "imports.h"

/*
		  Credits:

   Base64: Ren� Nyffenegger
   Modmap: BTBD
   Driver Mapper: Alxbrn
   Vulnerable Driver: Gigabyte
   This base: ZeraX#1337

*/


int main()
{
	//stopping anti-cheats, fn, epic

	system("taskkill /f /im EpicGamesLauncher.exe");
	system("taskkill /f /im FortniteClient-Win64-Shipping.exe");
	system("taskkill /f /im FortniteClient-Win64-Shipping_EAC");
	system("taskkill /f /im FortniteClient-Win64-Shipping_BE");
	system("taskkill /f /im UnrealCEFSubProcess.exe");

	system("net stop beservice");
	system("net stop easyanticheat");

	//clear the screen, i started from the bottom up so im tired as fuck..... so cba to add a method for this
	system("cls");

	//get handle of console output so we can use setconsoletextattribute to change the color of the text
	items::ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//change console title 
	SetConsoleTitleA("Interstellar Open Source Loader - github.com/furiosdestruct");

#pragma region getdllfromgithub

	//change color of text to light magenta
	SetConsoleTextAttribute(items::ConsoleHandle, LIGHTMAGENTA);

	cout << "\n\n\n	[+] Initializing Interstellar Free Open Source!" << endl;

	//get dll bytes from github so we can inject dll obvsly lul, i base64'ed it because downloading raw binary from a webserver is aids...
	string bytes = base64_decode((char*)Internet::Download("https://raw.githubusercontent.com/furiosdestruct/Interstellar-Open-Source-Free/master/loader_updater").c_str(), true);

	//check mz headers of the bytes in case it was fucked while downloading the bytes
	if (bytes.data()[0] != 'M' || bytes.data()[1] != 'Z')
	{
		//the dll in memory was either modified or an issue occured while downloading it

		SetConsoleTextAttribute(items::ConsoleHandle, RED);

		cout << "	[-] Failed To Load DLL In Memory! Exiting In 5 Seconds!" << endl;

		Sleep(5000);

		exit(1);
	}

	//dll downloaded fine


	//change color of text to green
	SetConsoleTextAttribute(items::ConsoleHandle, GREEN);

	cout << "	[+] Loaded Dll In Memory!" << endl;

	Sleep(2000);

#pragma endregion getdllfromgithub

#pragma region mappastedriver

	//change color of text to light magenta
	SetConsoleTextAttribute(items::ConsoleHandle, LIGHTMAGENTA);

	cout << "	[+] Mapping Driver!\n\n" << endl;

	//change color of text to cyan
	SetConsoleTextAttribute(items::ConsoleHandle, CYAN);

	//removing files
	remove("a.exe");
	remove("b.sys");
	remove("c.sys");

	//writing pasted mapper
	ofstream a;
	a.open("a.exe", ios::binary | ios::out);
	a.write((char*)&one, sizeof(one));
	a.close();

	//writing pasted driver
	ofstream b;
	b.open("b.sys", ios::binary | ios::out);
	b.write((char*)&two, sizeof(two));
	b.close();

	//writing pasted driver
	ofstream c;
	c.open("c.sys", ios::binary | ios::out);
	c.write((char*)&three, sizeof(three));
	c.close();

	//wait for some time
	Sleep(100);

	//map the pasted driver using pasted mapper
	system("a.exe b.sys c.sys");

	//wait for some time
	Sleep(300);

	//delete files
	remove("a.exe");
	remove("b.sys");
	remove("c.sys");

	//wait again
	Sleep(200);

#pragma endregion mappasteddriver


#pragma region modmapinject

	if (!Comm::Setup()) 
	{
		//the communication had an error and was unsuccessful

		SetConsoleTextAttribute(items::ConsoleHandle, RED);

		cout << "	[-] Failed To Setup Communication Between Driver And Modmap! Exiting In 5 Seconds!" << endl;

		Sleep(5000);

		exit(1);
	}

	//change color of text to light magenta
	SetConsoleTextAttribute(items::ConsoleHandle, LIGHTMAGENTA);

	cout << "\n\n	[+] Open Fortnite!" << endl;

	while (true)
	{
		Sleep(10);
		if (items::processexists(L"FortniteClient-Win64-Shipping.exe"))
			break;
	}



	//change color of text to green
	SetConsoleTextAttribute(items::ConsoleHandle, GREEN);

	cout << "	[+] Found FortniteClient-Win64-Shipping.exe!" << endl;



	//change color of text to light magenta
	SetConsoleTextAttribute(items::ConsoleHandle, LIGHTMAGENTA);

	cout << "	[+] Press F2 In Lobby To Inject!\n\n" << endl;

	while (true)
	{
		//wait for 10ms otherwise it will blow up cpu lmfao
		Sleep(10);

		//check if f2 key pressed
		if (GetAsyncKeyState(VK_F2))
		{
			Comm::Process process(L"FortniteClient-Win64-Shipping.exe");

			auto entry = Map::ExtendMap(process, (char*)bytes.data(), L"dxgi.dll");
			if (!entry)
			{
				//something went wrong while mapping the headers and sections to fortnite

				SetConsoleTextAttribute(items::ConsoleHandle, RED);

				cout << "	[-] Failed To Extend! Exiting In 5 Seconds!" << endl;

				Sleep(5000);

				exit(1);
			}

			if (!Hijack::HijackViaHook(process, entry, L"user32.dll", "PeekMessageW"))
			{
				//something went wrong while the shellcode procedure

				SetConsoleTextAttribute(items::ConsoleHandle, RED);

				cout << "	[-] Failed To Hijack! Exiting In 5 Seconds!" << endl;

				Sleep(5000);

				exit(1);
			}

			break;
		}
	}
#pragma endregion modmapinject

	//should be injected by now

	//change color of text to green
	SetConsoleTextAttribute(items::ConsoleHandle, GREEN);

	cout << "\n\n	[+] Successfully Injected! Exiting In 5 Seconds!" << endl;

	Sleep(5000);

	exit(0);
}	