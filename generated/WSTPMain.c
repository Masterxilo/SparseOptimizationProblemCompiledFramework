/*
 * This file automatically produced by wsprep from:
 *	generated/WSTPTemplateFile.tm
 * mprep Revision 18 Copyright (c) Wolfram Research, Inc. 1990-2013
 */

#define MPREP_REVISION 18


#include "wstp.h"

int WSAbort = 0;
int WSDone  = 0;
long WSSpecialCharacter = '\0';
HANDLE WSInstance = (HANDLE)0;
HWND WSIconWindow = (HWND)0;

WSLINK stdlink = 0;
WSEnvironment stdenv = 0;
#if WSINTERFACE >= 3
WSYieldFunctionObject stdyielder = (WSYieldFunctionObject)0;
WSMessageHandlerObject stdhandler = (WSMessageHandlerObject)0;
#else
WSYieldFunctionObject stdyielder = 0;
WSMessageHandlerObject stdhandler = 0;
#endif /* WSINTERFACE >= 3 */

#include <windows.h>

#if defined(__GNUC__)

#	ifdef TCHAR
#		undef TCHAR
#	endif
#	define TCHAR char

#	ifdef PTCHAR
#		undef PTCHAR
#	endif
#	define PTCHAR char *

#	ifdef __TEXT
#		undef __TEXT
#	endif
#	define __TEXT(arg) arg

#	ifdef _tcsrchr
#		undef _tcsrchr
#	endif
#	define _tcsrchr strrchr

#	ifdef _tcscat
#		undef _tcscat
#	endif
#	define _tcscat strcat

#	ifdef _tcsncpy
#		undef _tcsncpy
#	endif
#	define _tcsncpy _fstrncpy
#else
#	include <tchar.h>
#endif

#include <stdlib.h>
#include <string.h>
#if (WIN32_WSTP || WIN64_WSTP || __GNUC__) && !defined(_fstrncpy)
#       define _fstrncpy strncpy
#endif

#ifndef CALLBACK
#define CALLBACK FAR PASCAL
typedef LONG LRESULT;
typedef unsigned int UINT;
typedef WORD WPARAM;
typedef DWORD LPARAM;
#endif


LRESULT CALLBACK WSEXPORT
IconProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WSEXPORT
IconProcedure( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg){
	case WM_CLOSE:
		WSDone = 1;
		WSAbort = 1;
		break;
	case WM_QUERYOPEN:
		return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam);
}


#ifdef _UNICODE
#define _APISTR(i) L ## #i
#else
#define _APISTR(i) #i
#endif

#define APISTR(i) _APISTR(i)

HWND WSInitializeIcon( HINSTANCE hInstance, int nCmdShow)
{
	TCHAR path_name[260];
	PTCHAR icon_name;

	WNDCLASS  wc;
	HMODULE hdll;

	WSInstance = hInstance;
	if( ! nCmdShow) return (HWND)0;

	hdll = GetModuleHandle( __TEXT("ml32i" APISTR(WSINTERFACE)));

	(void)GetModuleFileName( hInstance, path_name, 260);

	icon_name = _tcsrchr( path_name, '\\') + 1;
	*_tcsrchr( icon_name, '.') = '\0';


	wc.style = 0;
	wc.lpfnWndProc = IconProcedure;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;

	if( hdll)
		wc.hIcon = LoadIcon( hdll, __TEXT("MLIcon"));
	else
		wc.hIcon = LoadIcon( NULL, IDI_APPLICATION);

	wc.hCursor = LoadCursor( NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)( COLOR_WINDOW + 1);
	wc.lpszMenuName =  NULL;
	wc.lpszClassName = __TEXT("mprepIcon");
	(void)RegisterClass( &wc);

	WSIconWindow = CreateWindow( __TEXT("mprepIcon"), icon_name,
			WS_OVERLAPPEDWINDOW | WS_MINIMIZE, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			(HWND)0, (HMENU)0, hInstance, (void FAR*)0);

	if( WSIconWindow){
		ShowWindow( WSIconWindow, SW_MINIMIZE);
		UpdateWindow( WSIconWindow);
	}
	return WSIconWindow;
}


#if __BORLANDC__
#pragma argsused
#endif

#if WSINTERFACE >= 3
WSYDEFN( int, WSDefaultYielder, ( WSLINK mlp, WSYieldParameters yp))
#else
WSYDEFN( devyield_result, WSDefaultYielder, ( WSLINK mlp, WSYieldParameters yp))
#endif /* WSINTERFACE >= 3 */
{
	MSG msg;

#if !__BORLANDC__
	mlp = mlp; /* suppress unused warning */
	yp = yp; /* suppress unused warning */
#endif

	if( PeekMessage( &msg, (HWND)0, 0, 0, PM_REMOVE)){
		TranslateMessage( &msg);
		DispatchMessage( &msg);
	}
	return WSDone;
}


/********************************* end header *********************************/


void f_ P(( void));

#if WSPROTOTYPES
static int _tr0( WSLINK mlp)
#else
static int _tr0(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	f_();

	res = 1;

	return res;
} /* _tr0 */


void df_ P(( void));

#if WSPROTOTYPES
static int _tr1( WSLINK mlp)
#else
static int _tr1(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	df_();

	res = 1;

	return res;
} /* _tr1 */


void nextEven_ P(( void));

#if WSPROTOTYPES
static int _tr2( WSLINK mlp)
#else
static int _tr2(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	nextEven_();

	res = 1;

	return res;
} /* _tr2 */


void cs_cumsum_ P(( void));

#if WSPROTOTYPES
static int _tr3( WSLINK mlp)
#else
static int _tr3(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	cs_cumsum_();

	res = 1;

	return res;
} /* _tr3 */


void print_ P(( void));

#if WSPROTOTYPES
static int _tr4( WSLINK mlp)
#else
static int _tr4(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	print_();

	res = 1;

	return res;
} /* _tr4 */


void printd_ P(( void));

#if WSPROTOTYPES
static int _tr5( WSLINK mlp)
#else
static int _tr5(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printd_();

	res = 1;

	return res;
} /* _tr5 */


void printv_ P(( void));

#if WSPROTOTYPES
static int _tr6( WSLINK mlp)
#else
static int _tr6(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printv_();

	res = 1;

	return res;
} /* _tr6 */


void assertFinite_ P(( void));

#if WSPROTOTYPES
static int _tr7( WSLINK mlp)
#else
static int _tr7(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertFinite_();

	res = 1;

	return res;
} /* _tr7 */


void lengthzGet_ P(( void));

#if WSPROTOTYPES
static int _tr8( WSLINK mlp)
#else
static int _tr8(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthzGet_();

	res = 1;

L0:	return res;
} /* _tr8 */


void lengthfzGet_ P(( void));

#if WSPROTOTYPES
static int _tr9( WSLINK mlp)
#else
static int _tr9(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthfzGet_();

	res = 1;

L0:	return res;
} /* _tr9 */


void assertEachInRange_ P(( void));

#if WSPROTOTYPES
static int _tr10( WSLINK mlp)
#else
static int _tr10(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertEachInRange_();

	res = 1;

	return res;
} /* _tr10 */


void axpyWithReindexing_ P(( void));

#if WSPROTOTYPES
static int _tr11( WSLINK mlp)
#else
static int _tr11(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	axpyWithReindexing_();

	res = 1;

	return res;
} /* _tr11 */


void extract_ P(( void));

#if WSPROTOTYPES
static int _tr12( WSLINK mlp)
#else
static int _tr12(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	extract_();

	res = 1;

	return res;
} /* _tr12 */


void getY_ P(( void));

#if WSPROTOTYPES
static int _tr13( WSLINK mlp)
#else
static int _tr13(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	getY_();

	res = 1;

	return res;
} /* _tr13 */


void buildFxAndJFxAndSolveRepeatedly_ P(( void));

#if WSPROTOTYPES
static int _tr14( WSLINK mlp)
#else
static int _tr14(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedly_();

	res = 1;

	return res;
} /* _tr14 */


void receiveAndPrintOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr15( WSLINK mlp)
#else
static int _tr15(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveAndPrintOptimizationData_();

	res = 1;

	return res;
} /* _tr15 */


void makeAndPrintSparseMatrix_ P(( void));

#if WSPROTOTYPES
static int _tr16( WSLINK mlp)
#else
static int _tr16(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	makeAndPrintSparseMatrix_();

	res = 1;

	return res;
} /* _tr16 */


void testMain_ P(( void));

#if WSPROTOTYPES
static int _tr17( WSLINK mlp)
#else
static int _tr17(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	testMain_();

	res = 1;

L0:	return res;
} /* _tr17 */


void xx43_ P(( void));

#if WSPROTOTYPES
static int _tr18( WSLINK mlp)
#else
static int _tr18(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx43_();

	res = 1;

L0:	return res;
} /* _tr18 */


void get42_ P(( void));

#if WSPROTOTYPES
static int _tr19( WSLINK mlp)
#else
static int _tr19(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	get42_();

	res = 1;

L0:	return res;
} /* _tr19 */


void add_ P(( void));

#if WSPROTOTYPES
static int _tr20( WSLINK mlp)
#else
static int _tr20(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	add_();

	res = 1;

	return res;
} /* _tr20 */


void addf_ P(( void));

#if WSPROTOTYPES
static int _tr21( WSLINK mlp)
#else
static int _tr21(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addf_();

	res = 1;

	return res;
} /* _tr21 */


void multiout_ P(( void));

#if WSPROTOTYPES
static int _tr22( WSLINK mlp)
#else
static int _tr22(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	multiout_();

	res = 1;

	return res;
} /* _tr22 */


void setPartitions_ P(( void));

#if WSPROTOTYPES
static int _tr23( WSLINK mlp)
#else
static int _tr23(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	setPartitions_();

	res = 1;

	return res;
} /* _tr23 */


void receiveSharedOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr24( WSLINK mlp)
#else
static int _tr24(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveSharedOptimizationData_();

	res = 1;

	return res;
} /* _tr24 */


void receiveOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr25( WSLINK mlp)
#else
static int _tr25(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveOptimizationData_();

	res = 1;

	return res;
} /* _tr25 */


void f_CUDA P(( void));

#if WSPROTOTYPES
static int _tr26( WSLINK mlp)
#else
static int _tr26(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	f_CUDA();

	res = 1;

	return res;
} /* _tr26 */


void df_CUDA P(( void));

#if WSPROTOTYPES
static int _tr27( WSLINK mlp)
#else
static int _tr27(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	df_CUDA();

	res = 1;

	return res;
} /* _tr27 */


void nextEven_CUDA P(( void));

#if WSPROTOTYPES
static int _tr28( WSLINK mlp)
#else
static int _tr28(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	nextEven_CUDA();

	res = 1;

	return res;
} /* _tr28 */


void cs_cumsum_CUDA P(( void));

#if WSPROTOTYPES
static int _tr29( WSLINK mlp)
#else
static int _tr29(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	cs_cumsum_CUDA();

	res = 1;

	return res;
} /* _tr29 */


void print_CUDA P(( void));

#if WSPROTOTYPES
static int _tr30( WSLINK mlp)
#else
static int _tr30(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	print_CUDA();

	res = 1;

	return res;
} /* _tr30 */


void printd_CUDA P(( void));

#if WSPROTOTYPES
static int _tr31( WSLINK mlp)
#else
static int _tr31(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printd_CUDA();

	res = 1;

	return res;
} /* _tr31 */


void printv_CUDA P(( void));

#if WSPROTOTYPES
static int _tr32( WSLINK mlp)
#else
static int _tr32(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printv_CUDA();

	res = 1;

	return res;
} /* _tr32 */


void assertFinite_CUDA P(( void));

#if WSPROTOTYPES
static int _tr33( WSLINK mlp)
#else
static int _tr33(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertFinite_CUDA();

	res = 1;

	return res;
} /* _tr33 */


void lengthzGet_CUDA P(( void));

#if WSPROTOTYPES
static int _tr34( WSLINK mlp)
#else
static int _tr34(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthzGet_CUDA();

	res = 1;

	return res;
} /* _tr34 */


void lengthfzGet_CUDA P(( void));

#if WSPROTOTYPES
static int _tr35( WSLINK mlp)
#else
static int _tr35(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthfzGet_CUDA();

	res = 1;

	return res;
} /* _tr35 */


void assertEachInRange_CUDA P(( void));

#if WSPROTOTYPES
static int _tr36( WSLINK mlp)
#else
static int _tr36(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertEachInRange_CUDA();

	res = 1;

	return res;
} /* _tr36 */


void axpyWithReindexing_CUDA P(( void));

#if WSPROTOTYPES
static int _tr37( WSLINK mlp)
#else
static int _tr37(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	axpyWithReindexing_CUDA();

	res = 1;

	return res;
} /* _tr37 */


void extract_CUDA P(( void));

#if WSPROTOTYPES
static int _tr38( WSLINK mlp)
#else
static int _tr38(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	extract_CUDA();

	res = 1;

	return res;
} /* _tr38 */


void getY_CUDA P(( void));

#if WSPROTOTYPES
static int _tr39( WSLINK mlp)
#else
static int _tr39(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	getY_CUDA();

	res = 1;

	return res;
} /* _tr39 */


void buildFxAndJFxAndSolveRepeatedly_CUDA P(( void));

#if WSPROTOTYPES
static int _tr40( WSLINK mlp)
#else
static int _tr40(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedly_CUDA();

	res = 1;

	return res;
} /* _tr40 */


void receiveAndPrintOptimizationData_CUDA P(( void));

#if WSPROTOTYPES
static int _tr41( WSLINK mlp)
#else
static int _tr41(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveAndPrintOptimizationData_CUDA();

	res = 1;

	return res;
} /* _tr41 */


void makeAndPrintSparseMatrix_CUDA P(( void));

#if WSPROTOTYPES
static int _tr42( WSLINK mlp)
#else
static int _tr42(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	makeAndPrintSparseMatrix_CUDA();

	res = 1;

	return res;
} /* _tr42 */


void testMain_CUDA P(( void));

#if WSPROTOTYPES
static int _tr43( WSLINK mlp)
#else
static int _tr43(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	testMain_CUDA();

	res = 1;

	return res;
} /* _tr43 */


void xx43_CUDA P(( void));

#if WSPROTOTYPES
static int _tr44( WSLINK mlp)
#else
static int _tr44(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx43_CUDA();

	res = 1;

	return res;
} /* _tr44 */


void get42_CUDA P(( void));

#if WSPROTOTYPES
static int _tr45( WSLINK mlp)
#else
static int _tr45(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	get42_CUDA();

	res = 1;

	return res;
} /* _tr45 */


void add_CUDA P(( void));

#if WSPROTOTYPES
static int _tr46( WSLINK mlp)
#else
static int _tr46(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	add_CUDA();

	res = 1;

	return res;
} /* _tr46 */


void addf_CUDA P(( void));

#if WSPROTOTYPES
static int _tr47( WSLINK mlp)
#else
static int _tr47(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addf_CUDA();

	res = 1;

	return res;
} /* _tr47 */


void multiout_CUDA P(( void));

#if WSPROTOTYPES
static int _tr48( WSLINK mlp)
#else
static int _tr48(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	multiout_CUDA();

	res = 1;

	return res;
} /* _tr48 */


void dprintEnabled_get P(( void));

#if WSPROTOTYPES
static int _tr49( WSLINK mlp)
#else
static int _tr49(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_get();

	res = 1;

L0:	return res;
} /* _tr49 */


void xx_get P(( void));

#if WSPROTOTYPES
static int _tr50( WSLINK mlp)
#else
static int _tr50(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_get();

	res = 1;

L0:	return res;
} /* _tr50 */


void a_get P(( void));

#if WSPROTOTYPES
static int _tr51( WSLINK mlp)
#else
static int _tr51(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_get();

	res = 1;

L0:	return res;
} /* _tr51 */


void b_get P(( void));

#if WSPROTOTYPES
static int _tr52( WSLINK mlp)
#else
static int _tr52(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_get();

	res = 1;

L0:	return res;
} /* _tr52 */


void yy_get P(( void));

#if WSPROTOTYPES
static int _tr53( WSLINK mlp)
#else
static int _tr53(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_get();

	res = 1;

L0:	return res;
} /* _tr53 */


void x_get P(( void));

#if WSPROTOTYPES
static int _tr54( WSLINK mlp)
#else
static int _tr54(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_get();

	res = 1;

L0:	return res;
} /* _tr54 */


void dprintEnabled_set P(( void));

#if WSPROTOTYPES
static int _tr55( WSLINK mlp)
#else
static int _tr55(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_set();

	res = 1;

	return res;
} /* _tr55 */


void xx_set P(( void));

#if WSPROTOTYPES
static int _tr56( WSLINK mlp)
#else
static int _tr56(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_set();

	res = 1;

	return res;
} /* _tr56 */


void a_set P(( void));

#if WSPROTOTYPES
static int _tr57( WSLINK mlp)
#else
static int _tr57(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_set();

	res = 1;

	return res;
} /* _tr57 */


void b_set P(( void));

#if WSPROTOTYPES
static int _tr58( WSLINK mlp)
#else
static int _tr58(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_set();

	res = 1;

	return res;
} /* _tr58 */


void yy_set P(( void));

#if WSPROTOTYPES
static int _tr59( WSLINK mlp)
#else
static int _tr59(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_set();

	res = 1;

	return res;
} /* _tr59 */


void x_set P(( void));

#if WSPROTOTYPES
static int _tr60( WSLINK mlp)
#else
static int _tr60(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_set();

	res = 1;

	return res;
} /* _tr60 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((WSLINK));
	const char  *f_name;
	} _tramps[61] = {
		{ 0, 2, _tr0, "f_" },
		{ 0, 2, _tr1, "df_" },
		{ 0, 2, _tr2, "nextEven_" },
		{ 0, 2, _tr3, "cs_cumsum_" },
		{ 0, 2, _tr4, "print_" },
		{ 0, 2, _tr5, "printd_" },
		{ 0, 2, _tr6, "printv_" },
		{ 0, 2, _tr7, "assertFinite_" },
		{ 0, 0, _tr8, "lengthzGet_" },
		{ 0, 0, _tr9, "lengthfzGet_" },
		{ 0, 2, _tr10, "assertEachInRange_" },
		{ 0, 2, _tr11, "axpyWithReindexing_" },
		{ 0, 2, _tr12, "extract_" },
		{ 0, 2, _tr13, "getY_" },
		{ 0, 2, _tr14, "buildFxAndJFxAndSolveRepeatedly_" },
		{ 0, 2, _tr15, "receiveAndPrintOptimizationData_" },
		{ 0, 2, _tr16, "makeAndPrintSparseMatrix_" },
		{ 0, 0, _tr17, "testMain_" },
		{ 0, 0, _tr18, "xx43_" },
		{ 0, 0, _tr19, "get42_" },
		{ 0, 2, _tr20, "add_" },
		{ 0, 2, _tr21, "addf_" },
		{ 0, 2, _tr22, "multiout_" },
		{ 0, 2, _tr23, "setPartitions_" },
		{ 0, 2, _tr24, "receiveSharedOptimizationData_" },
		{ 0, 2, _tr25, "receiveOptimizationData_" },
		{ 0, 2, _tr26, "f_CUDA" },
		{ 0, 2, _tr27, "df_CUDA" },
		{ 0, 2, _tr28, "nextEven_CUDA" },
		{ 0, 2, _tr29, "cs_cumsum_CUDA" },
		{ 0, 2, _tr30, "print_CUDA" },
		{ 0, 2, _tr31, "printd_CUDA" },
		{ 0, 2, _tr32, "printv_CUDA" },
		{ 0, 2, _tr33, "assertFinite_CUDA" },
		{ 0, 2, _tr34, "lengthzGet_CUDA" },
		{ 0, 2, _tr35, "lengthfzGet_CUDA" },
		{ 0, 2, _tr36, "assertEachInRange_CUDA" },
		{ 0, 2, _tr37, "axpyWithReindexing_CUDA" },
		{ 0, 2, _tr38, "extract_CUDA" },
		{ 0, 2, _tr39, "getY_CUDA" },
		{ 0, 2, _tr40, "buildFxAndJFxAndSolveRepeatedly_CUDA" },
		{ 0, 2, _tr41, "receiveAndPrintOptimizationData_CUDA" },
		{ 0, 2, _tr42, "makeAndPrintSparseMatrix_CUDA" },
		{ 0, 2, _tr43, "testMain_CUDA" },
		{ 0, 2, _tr44, "xx43_CUDA" },
		{ 0, 2, _tr45, "get42_CUDA" },
		{ 0, 2, _tr46, "add_CUDA" },
		{ 0, 2, _tr47, "addf_CUDA" },
		{ 0, 2, _tr48, "multiout_CUDA" },
		{ 0, 0, _tr49, "dprintEnabled_get" },
		{ 0, 0, _tr50, "xx_get" },
		{ 0, 0, _tr51, "a_get" },
		{ 0, 0, _tr52, "b_get" },
		{ 0, 0, _tr53, "yy_get" },
		{ 0, 0, _tr54, "x_get" },
		{ 0, 2, _tr55, "dprintEnabled_set" },
		{ 0, 2, _tr56, "xx_set" },
		{ 0, 2, _tr57, "a_set" },
		{ 0, 2, _tr58, "b_set" },
		{ 0, 2, _tr59, "yy_set" },
		{ 0, 2, _tr60, "x_set" }
		};

static const char* evalstrs[] = {
	"BeginPackage@\"SOPCompiled`Private`\";",
	(const char*)0,
	"ClearAll@\"SOPCompiled`Private`*\";",
	(const char*)0,
	"f::usage = \"the local energy vector computing function\"",
	(const char*)0,
	"df::usage = \"the derivatives along the i-th variable of the loca",
	"l energy vector computing function\"",
	(const char*)0,
	"nextEven::usage = \"support even allocation\"",
	(const char*)0,
	"cscumsum::usage = \"p [0..n] = cumulative sum of c [0..n-1], and ",
	"then copy p [0..n-1] into c \"",
	(const char*)0,
	"print::usage = \"prints a string to stdout\"",
	(const char*)0,
	"printd::usage = \"dprints a vector of integers, space separated a",
	"nd newline terminated\"",
	(const char*)0,
	"printv::usage = \"dprints a vector of doubles, space separated an",
	"d newline terminated\"",
	(const char*)0,
	"assertFinite::usage = \"assert that each element in v is finite\"",
	(const char*)0,
	"lengthzGet::usage = \"lengthz\"",
	(const char*)0,
	"lengthfzGet::usage = \"lengthfz\"",
	(const char*)0,
	"assertEachInRange::usage = \"computes the same as BoolEval[min <=",
	" v <= max]\"",
	(const char*)0,
	"axpyWithReindexing::usage = \"targetBase[[targetIndices]] += a * ",
	"addedValues. Repeated indices are not supported, so addedValues ",
	"cannot be longer than the target.Note that not necessarily all o",
	"f target is updated (_Inout_updates_, not _Inout_updates_all_)\"",
	(const char*)0,
	"extract::usage = \"target = source[[sourceIndices]]. Note that al",
	"l of target is initialized (_Out_writes_all_)\"",
	(const char*)0,
	"getY::usage = \"Extracts from x the elements that are ylengthY mu",
	"st match the length passed at initializationTODO make WSTP suppo",
	"rt having global variables specify the necessary array length, s",
	"upport non size_t lengthsthen we wouldn't need to supply the red",
	"undant lengthY here\"",
	(const char*)0,
	"buildFxAndJFxAndSolveRepeatedly::usage = \"using current data, bu",
	"ilds JFx (and Fx) and solves the least squares problemthen does ",
	"a gradient descent stepreapeats this whole process as often as d",
	"esired\"",
	(const char*)0,
	"receiveAndPrintOptimizationData::usage = \"Receives x, sparseDeri",
	"vativeZtoYIndices, xIndices and yIndices, checks and prints them",
	",emulating arbitrary lengthz, lengthfzNote: lengthz, lengthfz ar",
	"e fixed at compile-time for other functionsThis is a prototyping",
	" function that does not allocate or copy anythinguse for testing",
	"\"",
	(const char*)0,
	"makeAndPrintSparseMatrix::usage = \"Creates a sparse matrix from ",
	"a list of values and a list of pairs of (i, j) indices specifyin",
	"g where to put the corresponding values (triplet form)Note: This",
	" is a prototyping function without any further purpose\"",
	(const char*)0,
	"testMain::usage = \"collection of some tests\"",
	(const char*)0,
	"xx43::usage = \"sets xx to 43\"",
	(const char*)0,
	"get42::usage = \"returns the answer to the universe life and ever",
	"ything\"",
	(const char*)0,
	"add::usage = \"x + y\"",
	(const char*)0,
	"addf::usage = \"x + y with floats\"",
	(const char*)0,
	"multiout::usage = \"returns more than one thing: when called via ",
	"WSTP this will return an Association with all results\"",
	(const char*)0,
	"setPartitions::usage = \"set the amount of partitions\"",
	(const char*)0,
	"receiveSharedOptimizationData::usage = \"Receives x\"",
	(const char*)0,
	"receiveOptimizationData::usage = \"Receives sparseDerivativeZtoYI",
	"ndices, xIndices and yIndicesAppropriately sized vectors for rec",
	"eiving these data items are newly allocated in __managed__ memor",
	"y, hence this is a CPU only function\"",
	(const char*)0,
	"fCUDA::usage = \"the local energy vector computing function\"",
	(const char*)0,
	"dfCUDA::usage = \"the derivatives along the i-th variable of the ",
	"local energy vector computing function\"",
	(const char*)0,
	"nextEvenCUDA::usage = \"support even allocation\"",
	(const char*)0,
	"cscumsumCUDA::usage = \"p [0..n] = cumulative sum of c [0..n-1], ",
	"and then copy p [0..n-1] into c \"",
	(const char*)0,
	"printCUDA::usage = \"prints a string to stdout\"",
	(const char*)0,
	"printdCUDA::usage = \"dprints a vector of integers, space separat",
	"ed and newline terminated\"",
	(const char*)0,
	"printvCUDA::usage = \"dprints a vector of doubles, space separate",
	"d and newline terminated\"",
	(const char*)0,
	"assertFiniteCUDA::usage = \"assert that each element in v is fini",
	"te\"",
	(const char*)0,
	"lengthzGetCUDA::usage = \"lengthz\"",
	(const char*)0,
	"lengthfzGetCUDA::usage = \"lengthfz\"",
	(const char*)0,
	"assertEachInRangeCUDA::usage = \"computes the same as BoolEval[mi",
	"n <= v <= max]\"",
	(const char*)0,
	"axpyWithReindexingCUDA::usage = \"targetBase[[targetIndices]] += ",
	"a * addedValues. Repeated indices are not supported, so addedVal",
	"ues cannot be longer than the target.Note that not necessarily a",
	"ll of target is updated (_Inout_updates_, not _Inout_updates_all",
	"_)\"",
	(const char*)0,
	"extractCUDA::usage = \"target = source[[sourceIndices]]. Note tha",
	"t all of target is initialized (_Out_writes_all_)\"",
	(const char*)0,
	"getYCUDA::usage = \"Extracts from x the elements that are ylength",
	"Y must match the length passed at initializationTODO make WSTP s",
	"upport having global variables specify the necessary array lengt",
	"h, support non size_t lengthsthen we wouldn't need to supply the",
	" redundant lengthY here\"",
	(const char*)0,
	"buildFxAndJFxAndSolveRepeatedlyCUDA::usage = \"using current data",
	", builds JFx (and Fx) and solves the least squares problemthen d",
	"oes a gradient descent stepreapeats this whole process as often ",
	"as desired\"",
	(const char*)0,
	"receiveAndPrintOptimizationDataCUDA::usage = \"Receives x, sparse",
	"DerivativeZtoYIndices, xIndices and yIndices, checks and prints ",
	"them,emulating arbitrary lengthz, lengthfzNote: lengthz, lengthf",
	"z are fixed at compile-time for other functionsThis is a prototy",
	"ping function that does not allocate or copy anythinguse for tes",
	"ting\"",
	(const char*)0,
	"makeAndPrintSparseMatrixCUDA::usage = \"Creates a sparse matrix f",
	"rom a list of values and a list of pairs of (i, j) indices speci",
	"fying where to put the corresponding values (triplet form)Note: ",
	"This is a prototyping function without any further purpose\"",
	(const char*)0,
	"testMainCUDA::usage = \"collection of some tests\"",
	(const char*)0,
	"xx43CUDA::usage = \"sets xx to 43\"",
	(const char*)0,
	"get42CUDA::usage = \"returns the answer to the universe life and ",
	"everything\"",
	(const char*)0,
	"addCUDA::usage = \"x + y\"",
	(const char*)0,
	"addfCUDA::usage = \"x + y with floats\"",
	(const char*)0,
	"multioutCUDA::usage = \"returns more than one thing: when called ",
	"via WSTP this will return an Association with all results\"",
	(const char*)0,
	"dprintEnabledGet::usage = \"if true, dprintf writes to stdout, ot",
	"herwise dprintf does nothingIt would be more efficient to compil",
	"e with dprintf defined to nothing of courseDefault: true\"",
	(const char*)0,
	"xxGet::usage = \"xx\"",
	(const char*)0,
	"aGet::usage = \"a\"",
	(const char*)0,
	"bGet::usage = \"b\"",
	(const char*)0,
	"yyGet::usage = \"yy\"",
	(const char*)0,
	"xGet::usage = \"stores the current data vector 'x' which is updat",
	"ed to reduce the energy ||F(x)||^2\"",
	(const char*)0,
	"dprintEnabledSet::usage = \"if true, dprintf writes to stdout, ot",
	"herwise dprintf does nothingIt would be more efficient to compil",
	"e with dprintf defined to nothing of courseDefault: true\"",
	(const char*)0,
	"xxSet::usage = \"xx\"",
	(const char*)0,
	"aSet::usage = \"a\"",
	(const char*)0,
	"bSet::usage = \"b\"",
	(const char*)0,
	"yySet::usage = \"yy\"",
	(const char*)0,
	"xSet::usage = \"stores the current data vector 'x' which is updat",
	"ed to reduce the energy ||F(x)||^2\"",
	(const char*)0,
	"EndPackage[];",
	(const char*)0,
	(const char*)0
};
#define CARDOF_EVALSTRS 64

static int _definepattern P(( WSLINK, char*, char*, int));

static int _doevalstr P(( WSLINK, int));

int  _WSDoCallPacket P(( WSLINK, struct func[], int));


#if WSPROTOTYPES
int WSInstall( WSLINK mlp)
#else
int WSInstall(mlp) WSLINK mlp;
#endif
{
	int _res;
	_res = WSConnect(mlp);
	if (_res) _res = _doevalstr( mlp, 0);
	if (_res) _res = _doevalstr( mlp, 1);
	if (_res) _res = _definepattern(mlp, (char *)"f[input : {___Real}]", (char *)"{input}", 0);
	if (_res) _res = _doevalstr( mlp, 2);
	if (_res) _res = _definepattern(mlp, (char *)"df[i : _Integer, input : {___Real}]", (char *)"{i, input}", 1);
	if (_res) _res = _doevalstr( mlp, 3);
	if (_res) _res = _definepattern(mlp, (char *)"nextEven[i : _Integer]", (char *)"{i}", 2);
	if (_res) _res = _doevalstr( mlp, 4);
	if (_res) _res = _definepattern(mlp, (char *)"cscumsum[p : {___Integer}, c : {___Integer}, n : _Integer]", (char *)"{p, c, n}", 3);
	if (_res) _res = _doevalstr( mlp, 5);
	if (_res) _res = _definepattern(mlp, (char *)"print[x : _String]", (char *)"{x}", 4);
	if (_res) _res = _doevalstr( mlp, 6);
	if (_res) _res = _definepattern(mlp, (char *)"printd[v : {___Integer}]", (char *)"{v}", 5);
	if (_res) _res = _doevalstr( mlp, 7);
	if (_res) _res = _definepattern(mlp, (char *)"printv[v : {___Real}]", (char *)"{v}", 6);
	if (_res) _res = _doevalstr( mlp, 8);
	if (_res) _res = _definepattern(mlp, (char *)"assertFinite[x : {___Real}]", (char *)"{x}", 7);
	if (_res) _res = _doevalstr( mlp, 9);
	if (_res) _res = _definepattern(mlp, (char *)"lengthzGet[]", (char *)"{}", 8);
	if (_res) _res = _doevalstr( mlp, 10);
	if (_res) _res = _definepattern(mlp, (char *)"lengthfzGet[]", (char *)"{}", 9);
	if (_res) _res = _doevalstr( mlp, 11);
	if (_res) _res = _definepattern(mlp, (char *)"assertEachInRange[v : {___Integer}, min : _Integer, max : _Integer]", (char *)"{v, min, max}", 10);
	if (_res) _res = _doevalstr( mlp, 12);
	if (_res) _res = _definepattern(mlp, (char *)"axpyWithReindexing[targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]", (char *)"{targetBase, a, addedValues, targetIndices}", 11);
	if (_res) _res = _doevalstr( mlp, 13);
	if (_res) _res = _definepattern(mlp, (char *)"extract[source : {___Real}, sourceIndices : {___Integer}]", (char *)"{source, sourceIndices}", 12);
	if (_res) _res = _doevalstr( mlp, 14);
	if (_res) _res = _definepattern(mlp, (char *)"getY[partition : _Integer, lengthY : _Integer]", (char *)"{partition, lengthY}", 13);
	if (_res) _res = _doevalstr( mlp, 15);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedly[partition : _Integer, iterations : _Integer]", (char *)"{partition, iterations}", 14);
	if (_res) _res = _doevalstr( mlp, 16);
	if (_res) _res = _definepattern(mlp, (char *)"receiveAndPrintOptimizationData[lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]", (char *)"{lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}", 15);
	if (_res) _res = _doevalstr( mlp, 17);
	if (_res) _res = _definepattern(mlp, (char *)"makeAndPrintSparseMatrix[m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]", (char *)"{m, n, x, ij}", 16);
	if (_res) _res = _doevalstr( mlp, 18);
	if (_res) _res = _definepattern(mlp, (char *)"testMain[]", (char *)"{}", 17);
	if (_res) _res = _doevalstr( mlp, 19);
	if (_res) _res = _definepattern(mlp, (char *)"xx43[]", (char *)"{}", 18);
	if (_res) _res = _doevalstr( mlp, 20);
	if (_res) _res = _definepattern(mlp, (char *)"get42[]", (char *)"{}", 19);
	if (_res) _res = _doevalstr( mlp, 21);
	if (_res) _res = _definepattern(mlp, (char *)"add[x : _Integer, y : _Integer]", (char *)"{x, y}", 20);
	if (_res) _res = _doevalstr( mlp, 22);
	if (_res) _res = _definepattern(mlp, (char *)"addf[x : _Real, y : _Real]", (char *)"{x, y}", 21);
	if (_res) _res = _doevalstr( mlp, 23);
	if (_res) _res = _definepattern(mlp, (char *)"multiout[x : {___Integer}]", (char *)"{x}", 22);
	if (_res) _res = _doevalstr( mlp, 24);
	if (_res) _res = _definepattern(mlp, (char *)"setPartitions[newPartitionsCount : _Integer]", (char *)"{newPartitionsCount}", 23);
	if (_res) _res = _doevalstr( mlp, 25);
	if (_res) _res = _definepattern(mlp, (char *)"receiveSharedOptimizationData[xI : {___Real}]", (char *)"{xI}", 24);
	if (_res) _res = _doevalstr( mlp, 26);
	if (_res) _res = _definepattern(mlp, (char *)"receiveOptimizationData[partition : _Integer, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}]", (char *)"{partition, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI}", 25);
	if (_res) _res = _doevalstr( mlp, 27);
	if (_res) _res = _definepattern(mlp, (char *)"fCUDA[gridDim_Integer, blockDim_Integer, input : {___Real}]", (char *)"{gridDim, blockDim, input}", 26);
	if (_res) _res = _doevalstr( mlp, 28);
	if (_res) _res = _definepattern(mlp, (char *)"dfCUDA[gridDim_Integer, blockDim_Integer, i : _Integer, input : {___Real}]", (char *)"{gridDim, blockDim, i, input}", 27);
	if (_res) _res = _doevalstr( mlp, 29);
	if (_res) _res = _definepattern(mlp, (char *)"nextEvenCUDA[gridDim_Integer, blockDim_Integer, i : _Integer]", (char *)"{gridDim, blockDim, i}", 28);
	if (_res) _res = _doevalstr( mlp, 30);
	if (_res) _res = _definepattern(mlp, (char *)"cscumsumCUDA[gridDim_Integer, blockDim_Integer, p : {___Integer}, c : {___Integer}, n : _Integer]", (char *)"{gridDim, blockDim, p, c, n}", 29);
	if (_res) _res = _doevalstr( mlp, 31);
	if (_res) _res = _definepattern(mlp, (char *)"printCUDA[gridDim_Integer, blockDim_Integer, x : _String]", (char *)"{gridDim, blockDim, x}", 30);
	if (_res) _res = _doevalstr( mlp, 32);
	if (_res) _res = _definepattern(mlp, (char *)"printdCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}]", (char *)"{gridDim, blockDim, v}", 31);
	if (_res) _res = _doevalstr( mlp, 33);
	if (_res) _res = _definepattern(mlp, (char *)"printvCUDA[gridDim_Integer, blockDim_Integer, v : {___Real}]", (char *)"{gridDim, blockDim, v}", 32);
	if (_res) _res = _doevalstr( mlp, 34);
	if (_res) _res = _definepattern(mlp, (char *)"assertFiniteCUDA[gridDim_Integer, blockDim_Integer, x : {___Real}]", (char *)"{gridDim, blockDim, x}", 33);
	if (_res) _res = _doevalstr( mlp, 35);
	if (_res) _res = _definepattern(mlp, (char *)"lengthzGetCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 34);
	if (_res) _res = _doevalstr( mlp, 36);
	if (_res) _res = _definepattern(mlp, (char *)"lengthfzGetCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 35);
	if (_res) _res = _doevalstr( mlp, 37);
	if (_res) _res = _definepattern(mlp, (char *)"assertEachInRangeCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}, min : _Integer, max : _Integer]", (char *)"{gridDim, blockDim, v, min, max}", 36);
	if (_res) _res = _doevalstr( mlp, 38);
	if (_res) _res = _definepattern(mlp, (char *)"axpyWithReindexingCUDA[gridDim_Integer, blockDim_Integer, targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]", (char *)"{gridDim, blockDim, targetBase, a, addedValues, targetIndices}", 37);
	if (_res) _res = _doevalstr( mlp, 39);
	if (_res) _res = _definepattern(mlp, (char *)"extractCUDA[gridDim_Integer, blockDim_Integer, source : {___Real}, sourceIndices : {___Integer}]", (char *)"{gridDim, blockDim, source, sourceIndices}", 38);
	if (_res) _res = _doevalstr( mlp, 40);
	if (_res) _res = _definepattern(mlp, (char *)"getYCUDA[gridDim_Integer, blockDim_Integer, partition : _Integer, lengthY : _Integer]", (char *)"{gridDim, blockDim, partition, lengthY}", 39);
	if (_res) _res = _doevalstr( mlp, 41);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedlyCUDA[gridDim_Integer, blockDim_Integer, partition : _Integer, iterations : _Integer]", (char *)"{gridDim, blockDim, partition, iterations}", 40);
	if (_res) _res = _doevalstr( mlp, 42);
	if (_res) _res = _definepattern(mlp, (char *)"receiveAndPrintOptimizationDataCUDA[gridDim_Integer, blockDim_Integer, lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]", (char *)"{gridDim, blockDim, lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}", 41);
	if (_res) _res = _doevalstr( mlp, 43);
	if (_res) _res = _definepattern(mlp, (char *)"makeAndPrintSparseMatrixCUDA[gridDim_Integer, blockDim_Integer, m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]", (char *)"{gridDim, blockDim, m, n, x, ij}", 42);
	if (_res) _res = _doevalstr( mlp, 44);
	if (_res) _res = _definepattern(mlp, (char *)"testMainCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 43);
	if (_res) _res = _doevalstr( mlp, 45);
	if (_res) _res = _definepattern(mlp, (char *)"xx43CUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 44);
	if (_res) _res = _doevalstr( mlp, 46);
	if (_res) _res = _definepattern(mlp, (char *)"get42CUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 45);
	if (_res) _res = _doevalstr( mlp, 47);
	if (_res) _res = _definepattern(mlp, (char *)"addCUDA[gridDim_Integer, blockDim_Integer, x : _Integer, y : _Integer]", (char *)"{gridDim, blockDim, x, y}", 46);
	if (_res) _res = _doevalstr( mlp, 48);
	if (_res) _res = _definepattern(mlp, (char *)"addfCUDA[gridDim_Integer, blockDim_Integer, x : _Real, y : _Real]", (char *)"{gridDim, blockDim, x, y}", 47);
	if (_res) _res = _doevalstr( mlp, 49);
	if (_res) _res = _definepattern(mlp, (char *)"multioutCUDA[gridDim_Integer, blockDim_Integer, x : {___Integer}]", (char *)"{gridDim, blockDim, x}", 48);
	if (_res) _res = _doevalstr( mlp, 50);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledGet[]", (char *)"{}", 49);
	if (_res) _res = _doevalstr( mlp, 51);
	if (_res) _res = _definepattern(mlp, (char *)"xxGet[]", (char *)"{}", 50);
	if (_res) _res = _doevalstr( mlp, 52);
	if (_res) _res = _definepattern(mlp, (char *)"aGet[]", (char *)"{}", 51);
	if (_res) _res = _doevalstr( mlp, 53);
	if (_res) _res = _definepattern(mlp, (char *)"bGet[]", (char *)"{}", 52);
	if (_res) _res = _doevalstr( mlp, 54);
	if (_res) _res = _definepattern(mlp, (char *)"yyGet[]", (char *)"{}", 53);
	if (_res) _res = _doevalstr( mlp, 55);
	if (_res) _res = _definepattern(mlp, (char *)"xGet[]", (char *)"{}", 54);
	if (_res) _res = _doevalstr( mlp, 56);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledSet[dprintEnabled : _Integer]", (char *)"{dprintEnabled}", 55);
	if (_res) _res = _doevalstr( mlp, 57);
	if (_res) _res = _definepattern(mlp, (char *)"xxSet[xx : _Integer]", (char *)"{xx}", 56);
	if (_res) _res = _doevalstr( mlp, 58);
	if (_res) _res = _definepattern(mlp, (char *)"aSet[a : _Real]", (char *)"{a}", 57);
	if (_res) _res = _doevalstr( mlp, 59);
	if (_res) _res = _definepattern(mlp, (char *)"bSet[b : _Real]", (char *)"{b}", 58);
	if (_res) _res = _doevalstr( mlp, 60);
	if (_res) _res = _definepattern(mlp, (char *)"yySet[yy : _Real]", (char *)"{yy}", 59);
	if (_res) _res = _doevalstr( mlp, 61);
	if (_res) _res = _definepattern(mlp, (char *)"xSet[x : {___Real}]", (char *)"{x}", 60);
	if (_res) _res = _doevalstr( mlp, 62);
	if (_res) _res = _doevalstr( mlp, 63);
	if (_res) _res = WSPutSymbol( mlp, "End");
	if (_res) _res = WSFlush( mlp);
	return _res;
} /* WSInstall */


#if WSPROTOTYPES
int WSDoCallPacket( WSLINK mlp)
#else
int WSDoCallPacket( mlp) WSLINK mlp;
#endif
{
	return _WSDoCallPacket( mlp, _tramps, 61);
} /* WSDoCallPacket */

/******************************* begin trailer ********************************/

#ifndef EVALSTRS_AS_BYTESTRINGS
#	define EVALSTRS_AS_BYTESTRINGS 1
#endif

#if CARDOF_EVALSTRS
static int  _doevalstr( WSLINK mlp, int n)
{
	long bytesleft, charsleft, bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
	long charsnow;
#endif
	char **s, **p;
	char *t;

	s = (char **)evalstrs;
	while( n-- > 0){
		if( *s == 0) break;
		while( *s++ != 0){}
	}
	if( *s == 0) return 0;
	bytesleft = 0;
	charsleft = 0;
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = (long)(t - *p);
		bytesleft += bytesnow;
		charsleft += bytesnow;
#if !EVALSTRS_AS_BYTESTRINGS
		t = *p;
		charsleft -= WSCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
#endif
		++p;
	}


	WSPutNext( mlp, WSTKSTR);
#if EVALSTRS_AS_BYTESTRINGS
	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = (long)(t - *p);
		bytesleft -= bytesnow;
		WSPut8BitCharacters( mlp, bytesleft, (unsigned char*)*p, bytesnow);
		++p;
	}
#else
	WSPut7BitCount( mlp, (long_st)charsleft, (long_st)bytesleft);

	p = s;
	while( *p){
		t = *p; while( *t) ++t;
		bytesnow = t - *p;
		bytesleft -= bytesnow;
		t = *p;
		charsnow = bytesnow - WSCharacterOffset( &t, t + bytesnow, bytesnow);
		/* assert( t == *p + bytesnow); */
		charsleft -= charsnow;
		WSPut7BitCharacters(  mlp, charsleft, *p, bytesnow, charsnow);
		++p;
	}
#endif
	return WSError( mlp) == WSEOK;
}
#endif /* CARDOF_EVALSTRS */


static int  _definepattern( WSLINK mlp, char *patt, char *args, int func_n)
{
	WSPutFunction( mlp, "DefineExternal", (long)3);
	  WSPutString( mlp, patt);
	  WSPutString( mlp, args);
	  WSPutInteger( mlp, func_n);
	return !WSError(mlp);
} /* _definepattern */


int _WSDoCallPacket( WSLINK mlp, struct func functable[], int nfuncs)
{
#if WSINTERFACE >= 4
	int len;
#else
	long len;
#endif
	int n, res = 0;
	struct func* funcp;

	if( ! WSGetInteger( mlp, &n) ||  n < 0 ||  n >= nfuncs) goto L0;
	funcp = &functable[n];

	if( funcp->f_nargs >= 0
#if WSINTERFACE >= 4
	&& ( ! WSTestHead(mlp, "List", &len)
#else
	&& ( ! WSCheckFunction(mlp, "List", &len)
#endif
	     || ( !funcp->manual && (len != funcp->f_nargs))
	     || (  funcp->manual && (len <  funcp->f_nargs))
	   )
	) goto L0;

	stdlink = mlp;
	res = (*funcp->f_func)( mlp);

L0:	if( res == 0)
		res = WSClearError( mlp) && WSPutSymbol( mlp, "$Failed");
	return res && WSEndPacket( mlp) && WSNewPacket( mlp);
} /* _WSDoCallPacket */


wsapi_packet WSAnswer( WSLINK mlp)
{
	wsapi_packet pkt = 0;
#if WSINTERFACE >= 4
	int waitResult;

	while( ! WSDone && ! WSError(mlp)
		&& (waitResult = WSWaitForLinkActivity(mlp),waitResult) &&
		waitResult == WSWAITSUCCESS && (pkt = WSNextPacket(mlp), pkt) &&
		pkt == CALLPKT)
	{
		WSAbort = 0;
		if(! WSDoCallPacket(mlp))
			pkt = 0;
	}
#else
	while( !WSDone && !WSError(mlp) && (pkt = WSNextPacket(mlp), pkt) && pkt == CALLPKT){
		WSAbort = 0;
		if( !WSDoCallPacket(mlp)) pkt = 0;
	}
#endif
	WSAbort = 0;
	return pkt;
}



/*
	Module[ { me = $ParentLink},
		$ParentLink = contents of RESUMEPKT;
		Message[ MessageName[$ParentLink, "notfe"], me];
		me]
*/

static int refuse_to_be_a_frontend( WSLINK mlp)
{
	int pkt;

	WSPutFunction( mlp, "EvaluatePacket", 1);
	  WSPutFunction( mlp, "Module", 2);
	    WSPutFunction( mlp, "List", 1);
		  WSPutFunction( mlp, "Set", 2);
		    WSPutSymbol( mlp, "me");
	        WSPutSymbol( mlp, "$ParentLink");
	  WSPutFunction( mlp, "CompoundExpression", 3);
	    WSPutFunction( mlp, "Set", 2);
	      WSPutSymbol( mlp, "$ParentLink");
	      WSTransferExpression( mlp, mlp);
	    WSPutFunction( mlp, "Message", 2);
	      WSPutFunction( mlp, "MessageName", 2);
	        WSPutSymbol( mlp, "$ParentLink");
	        WSPutString( mlp, "notfe");
	      WSPutSymbol( mlp, "me");
	    WSPutSymbol( mlp, "me");
	WSEndPacket( mlp);

	while( (pkt = WSNextPacket( mlp), pkt) && pkt != SUSPENDPKT)
		WSNewPacket( mlp);
	WSNewPacket( mlp);
	return WSError( mlp) == WSEOK;
}


#if WSINTERFACE >= 3
int WSEvaluate( WSLINK mlp, char *s)
#else
int WSEvaluate( WSLINK mlp, charp_ct s)
#endif /* WSINTERFACE >= 3 */
{
	if( WSAbort) return 0;
	return WSPutFunction( mlp, "EvaluatePacket", 1L)
		&& WSPutFunction( mlp, "ToExpression", 1L)
		&& WSPutString( mlp, s)
		&& WSEndPacket( mlp);
}


#if WSINTERFACE >= 3
int WSEvaluateString( WSLINK mlp, char *s)
#else
int WSEvaluateString( WSLINK mlp, charp_ct s)
#endif /* WSINTERFACE >= 3 */
{
	int pkt;
	if( WSAbort) return 0;
	if( WSEvaluate( mlp, s)){
		while( (pkt = WSAnswer( mlp), pkt) && pkt != RETURNPKT)
			WSNewPacket( mlp);
		WSNewPacket( mlp);
	}
	return WSError( mlp) == WSEOK;
} /* WSEvaluateString */


#if __BORLANDC__
#pragma argsused
#endif

#if WSINTERFACE >= 3
WSMDEFN( void, WSDefaultHandler, ( WSLINK mlp, int message, int n))
#else
WSMDEFN( void, WSDefaultHandler, ( WSLINK mlp, unsigned long message, unsigned long n))
#endif /* WSINTERFACE >= 3 */
{
#if !__BORLANDC__
	mlp = (WSLINK)0; /* suppress unused warning */
	n = 0;          /* suppress unused warning */
#endif

	switch (message){
	case WSTerminateMessage:
		WSDone = 1;
	case WSInterruptMessage:
	case WSAbortMessage:
		WSAbort = 1;
	default:
		return;
	}
}



#if WSINTERFACE >= 3
static int _WSMain( char **argv, char **argv_end, char *commandline)
#else
static int _WSMain( charpp_ct argv, charpp_ct argv_end, charp_ct commandline)
#endif /* WSINTERFACE >= 3 */
{
	WSLINK mlp;
#if WSINTERFACE >= 3
	int err;
#else
	long err;
#endif /* WSINTERFACE >= 3 */

#if WSINTERFACE >= 4
	if( !stdenv)
		stdenv = WSInitialize( (WSEnvironmentParameter)0);
#else
	if( !stdenv)
		stdenv = WSInitialize( (WSParametersPointer)0);
#endif

	if( stdenv == (WSEnvironment)0) goto R0;

	if( !stdyielder)
#if WSINTERFACE >= 3
		stdyielder = (WSYieldFunctionObject)WSDefaultYielder;
#else
		stdyielder = WSCreateYieldFunction( stdenv,
			NewWSYielderProc( WSDefaultYielder), 0);
#endif /* WSINTERFACE >= 3 */


#if WSINTERFACE >= 3
	if( !stdhandler)
		stdhandler = (WSMessageHandlerObject)WSDefaultHandler;
#else
	if( !stdhandler)
		stdhandler = WSCreateMessageHandler( stdenv,
			NewWSHandlerProc( WSDefaultHandler), 0);
#endif /* WSINTERFACE >= 3 */


	mlp = commandline
		? WSOpenString( stdenv, commandline, &err)
#if WSINTERFACE >= 3
		: WSOpenArgcArgv( stdenv, (int)(argv_end - argv), argv, &err);
#else
		: WSOpenArgv( stdenv, argv, argv_end, &err);
#endif
	if( mlp == (WSLINK)0){
		WSAlert( stdenv, WSErrorString( stdenv, err));
		goto R1;
	}

	if( WSIconWindow){
#define TEXTBUFLEN 64
		TCHAR textbuf[TEXTBUFLEN];
		PTCHAR tmlname;
		const char *mlname;
		size_t namelen, i;
		int len;
		len = GetWindowText(WSIconWindow, textbuf, 62 );
		mlname = WSName(mlp);
		namelen = strlen(mlname);
		tmlname = (PTCHAR)malloc((namelen + 1)*sizeof(TCHAR));
		if(tmlname == NULL) goto R2;

		for(i = 0; i < namelen; i++){
			tmlname[i] = mlname[i];
		}
		tmlname[namelen] = '\0';
		
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
		_tcscat_s( textbuf + len, TEXTBUFLEN - len, __TEXT("("));
		_tcsncpy_s(textbuf + len + 1, TEXTBUFLEN - len - 1, tmlname, TEXTBUFLEN - len - 3);
		textbuf[TEXTBUFLEN - 2] = '\0';
		_tcscat_s(textbuf, TEXTBUFLEN, __TEXT(")"));
#else
		_tcscat( textbuf + len, __TEXT("("));
		_tcsncpy( textbuf + len + 1, tmlname, TEXTBUFLEN - len - 3);
		textbuf[TEXTBUFLEN - 2] = '\0';
		_tcscat( textbuf, __TEXT(")"));
#endif
		textbuf[len + namelen + 2] = '\0';
		free(tmlname);
		SetWindowText( WSIconWindow, textbuf);
	}

	if( WSInstance){
		if( stdyielder) WSSetYieldFunction( mlp, stdyielder);
		if( stdhandler) WSSetMessageHandler( mlp, stdhandler);
	}

	if( WSInstall( mlp))
		while( WSAnswer( mlp) == RESUMEPKT){
			if( ! refuse_to_be_a_frontend( mlp)) break;
		}

R2:	WSClose( mlp);
R1:	WSDeinitialize( stdenv);
	stdenv = (WSEnvironment)0;
R0:	return !WSDone;
} /* _WSMain */


#if WSINTERFACE >= 3
int WSMainString( char *commandline)
#else
int WSMainString( charp_ct commandline)
#endif /* WSINTERFACE >= 3 */
{
#if WSINTERFACE >= 3
	return _WSMain( (char **)0, (char **)0, commandline);
#else
	return _WSMain( (charpp_ct)0, (charpp_ct)0, commandline);
#endif /* WSINTERFACE >= 3 */
}

int WSMainArgv( char** argv, char** argv_end) /* note not FAR pointers */
{   
	static char FAR * far_argv[128];
	int count = 0;
	
	while(argv < argv_end)
		far_argv[count++] = *argv++;
		 
#if WSINTERFACE >= 3
	return _WSMain( far_argv, far_argv + count, (char *)0);
#else
	return _WSMain( far_argv, far_argv + count, (charp_ct)0);
#endif /* WSINTERFACE >= 3 */

}

#if WSINTERFACE >= 3
int WSMain( int argc, char **argv)
#else
int WSMain( int argc, charpp_ct argv)
#endif /* WSINTERFACE >= 3 */
{
#if WSINTERFACE >= 3
 	return _WSMain( argv, argv + argc, (char *)0);
#else
 	return _WSMain( argv, argv + argc, (charp_ct)0);
#endif /* WSINTERFACE >= 3 */
}
 
