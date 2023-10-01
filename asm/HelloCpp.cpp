int main()
{
	char* outBuffer = (char*)0xFFC00;
	const char* text = "Hello C++\0";
	while (true) {
		int i = 0;
		while (text[i] != '\0')
			outBuffer[i + 1] = text[i++];
		outBuffer[0] = 0;
	}
	return 0;
}
