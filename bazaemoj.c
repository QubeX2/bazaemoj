#include <stdio.h>
#include <wchar.h>

int main(int argc, char **argv)
{
    wchar_t *name = L"Jörgen Sütterlünd";
    wprintf("%ls\n", name);
    return 0;
}
