#include <CFileLocation.h>

void CFileLocation::Clear(CFileLocationStruct* fl)
{
	memset(fl, 0, 8);
}