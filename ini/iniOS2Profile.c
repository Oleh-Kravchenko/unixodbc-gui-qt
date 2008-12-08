/***********************************************************
*
* OS/2 profile functions for the ini file handling
*
* Copyright Lorne Sunley 2004
*
* released under the LGPL
*
************************************************************/

#ifdef __OS2__


#define     INI_SUCCESS             1
#define     INI_ERROR               0

#include <stdlib.h>
#define INCL_WINSHELLDATA
#include <os2.h>

int iniOS2Open (PSZ pszFileName)
{

    HAB hab;
    HINI    hini;

#ifdef __OS2DEBUG__
    printf("Entered iniOS2Open %s \n", pszFileName);
#endif

    hab = WinInitialize(0);

    hini = PrfOpenProfile( hab, pszFileName );

#ifdef __OS2DEBUG__
    printf("Leaving iniOS2Open %s hini is %d\n", pszFileName, hini);
#endif

    return hini;
}

int iniOS2Close (HINI hini)

{

#ifdef __OS2DEBUG__
    printf("Entered iniOS2Close \n");
#endif

    return(PrfCloseProfile( hini));

}

int iniOS2Write (HINI hini, PSZ objectname, PSZ propertyname, PSZ propertyvalue)

{

    return(PrfWriteProfileString(hini, objectname, propertyname, propertyvalue));

}

void *iniOS2Read (HINI hini, PSZ objectname, PSZ propertyname)
{
    ULONG uDatalen;
    VOID *databuffer;
    ULONG ulBufferMax = 1000;

#ifdef __OS2DEBUG__
    printf("Entered iniOS2Read \n");
#endif

    databuffer = calloc(1, ulBufferMax);

    uDatalen = PrfQueryProfileString(hini, objectname, propertyname, NULL, databuffer , ulBufferMax);

#ifdef __OS2DEBUG__
    printf("iniOS2Read property is % \n",databuffer);
#endif


    return databuffer;

}

VOID *iniOS2LoadObjectList ( HINI hini,  PULONG numberObject )
{
    VOID  *ObjectList;
    ULONG   ulBufferMax;
    ULONG   ulBufferNeeded;
    ULONG   ulLength;
    BOOL    rc;

#ifdef __OS2DEBUG__
    printf("Entered iniOS2LoadObjectList \n");
#endif

    rc = PrfQueryProfileSize( hini, NULL, NULL, &ulBufferNeeded);
    if ( !rc )
        return 0;


    ObjectList = calloc(1, ulBufferNeeded + 1);


    ulLength = PrfQueryProfileString( hini, NULL, NULL, NULL,  ObjectList, ulBufferNeeded);

    *numberObject = ulLength;


    return ObjectList;

}


VOID *iniOS2LoadPropertyList ( HINI hini, PSZ objectname,  PULONG numberProperty )
{
    VOID    *PropertyList;
    ULONG   ulBufferMax;
    ULONG   ulBufferNeeded;
    ULONG   ulLength;
    BOOL    rc;

#ifdef __OS2DEBUG__
    printf("Entered iniOS2LoadPropertyList \n");
#endif


    rc = PrfQueryProfileSize( hini, objectname, NULL, &ulBufferNeeded);
    if ( !rc )
        return 0;

    PropertyList = calloc(1, ulBufferNeeded + 1);

    ulLength = PrfQueryProfileString( hini, objectname, NULL, NULL, PropertyList, ulBufferNeeded);

    *numberProperty = ulLength;
    return PropertyList;



}


#endif /* end of __OS2__ */
