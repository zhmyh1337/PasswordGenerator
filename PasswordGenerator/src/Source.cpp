#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include <chrono>
#include <random>

void SetClipboardText(LPCSTR text)
{
	const size_t len = strlen(text) + 1;
	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), text, len);
	GlobalUnlock(hMem);
	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
	GlobalFree(hMem);
}

std::string GetDictionary()
{
	std::ostringstream ss;
	
	for (char ch = 'a'; ch <= 'z'; ++ch)
	{
		ss << ch;
	}

	for (char ch = 'A'; ch <= 'Z'; ++ch)
	{
		ss << ch;
	}

	for (char ch = '0'; ch <= '9'; ++ch)
	{
		ss << ch;
	}

	ss << "~`!@#$%^&*()-_=+<>,.?/\\|;:[]{}";

	return ss.str();
}

std::string GeneratePassword(size_t length, std::mt19937 rng)
{
	std::ostringstream ss;
	std::string dictionary = GetDictionary();

	for (size_t i = 0; i < length; i++)
	{
		ss << dictionary[rng() % dictionary.length()];
	}

	return ss.str();
}

int main()
{
	constexpr size_t length = 20;
	std::mt19937 rng((uint32_t)std::chrono::high_resolution_clock::now().time_since_epoch().count());

	SetClipboardText(GeneratePassword(length, rng).c_str());
}
