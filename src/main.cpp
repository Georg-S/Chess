#pragma once

#ifdef _WIN32 
#undef main // Undef main because of SDL library
#endif

int main(int argc, char* argv[])
{
	return 0;
}