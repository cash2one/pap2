////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : FileEnumerForDirectory.h
//  Version     : 1.0
//  Creator     : Chen Tianhong
//  Create Date : 2009-5-18 10:42:06
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_FILEENUMERFORDIRECTORY_H_
#define _INCLUDE_FILEENUMERFORDIRECTORY_H_

////////////////////////////////////////////////////////////////////////////////
struct ICFileEnumer;
ICFileEnumer* CreateFileEnumerForDirectory(LPCTSTR strDirectory);	//����֮��ҪDelete

#endif //_INCLUDE_FILEENUMERFORDIRECTORY_H_