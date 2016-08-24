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


void lengthzGet_ P(( void));

#if WSPROTOTYPES
static int _tr0( WSLINK mlp)
#else
static int _tr0(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthzGet_();

	res = 1;

L0:	return res;
} /* _tr0 */


void lengthfzGet_ P(( void));

#if WSPROTOTYPES
static int _tr1( WSLINK mlp)
#else
static int _tr1(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthfzGet_();

	res = 1;

L0:	return res;
} /* _tr1 */


void print_ P(( void));

#if WSPROTOTYPES
static int _tr2( WSLINK mlp)
#else
static int _tr2(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	print_();

	res = 1;

	return res;
} /* _tr2 */


void printv_ P(( void));

#if WSPROTOTYPES
static int _tr3( WSLINK mlp)
#else
static int _tr3(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printv_();

	res = 1;

	return res;
} /* _tr3 */


void printd_ P(( void));

#if WSPROTOTYPES
static int _tr4( WSLINK mlp)
#else
static int _tr4(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printd_();

	res = 1;

	return res;
} /* _tr4 */


void assertEachInRange_ P(( void));

#if WSPROTOTYPES
static int _tr5( WSLINK mlp)
#else
static int _tr5(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertEachInRange_();

	res = 1;

	return res;
} /* _tr5 */


void axpyWithReindexing_ P(( void));

#if WSPROTOTYPES
static int _tr6( WSLINK mlp)
#else
static int _tr6(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	axpyWithReindexing_();

	res = 1;

	return res;
} /* _tr6 */


void extract_ P(( void));

#if WSPROTOTYPES
static int _tr7( WSLINK mlp)
#else
static int _tr7(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	extract_();

	res = 1;

	return res;
} /* _tr7 */


void writeFx_ P(( void));

#if WSPROTOTYPES
static int _tr8( WSLINK mlp)
#else
static int _tr8(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	writeFx_();

	res = 1;

	return res;
} /* _tr8 */


void readZ_ P(( void));

#if WSPROTOTYPES
static int _tr9( WSLINK mlp)
#else
static int _tr9(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	readZ_();

	res = 1;

	return res;
} /* _tr9 */


void readZandSetFxRow_ P(( void));

#if WSPROTOTYPES
static int _tr10( WSLINK mlp)
#else
static int _tr10(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	readZandSetFxRow_();

	res = 1;

	return res;
} /* _tr10 */


void setFxRow_ P(( void));

#if WSPROTOTYPES
static int _tr11( WSLINK mlp)
#else
static int _tr11(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	setFxRow_();

	res = 1;

	return res;
} /* _tr11 */


void buildFx_ P(( void));

#if WSPROTOTYPES
static int _tr12( WSLINK mlp)
#else
static int _tr12(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFx_();

	res = 1;

L0:	return res;
} /* _tr12 */


void norm2Fx_ P(( void));

#if WSPROTOTYPES
static int _tr13( WSLINK mlp)
#else
static int _tr13(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	norm2Fx_();

	res = 1;

L0:	return res;
} /* _tr13 */


void addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_ P(( void));

#if WSPROTOTYPES
static int _tr14( WSLINK mlp)
#else
static int _tr14(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_();

	res = 1;

L0:	return res;
} /* _tr14 */


void getY_ P(( void));

#if WSPROTOTYPES
static int _tr15( WSLINK mlp)
#else
static int _tr15(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	getY_();

	res = 1;

	return res;
} /* _tr15 */


void buildFxAndJFxAndSolveRepeatedly_ P(( void));

#if WSPROTOTYPES
static int _tr16( WSLINK mlp)
#else
static int _tr16(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedly_();

	res = 1;

	return res;
} /* _tr16 */


void receiveAndPrintOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr17( WSLINK mlp)
#else
static int _tr17(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveAndPrintOptimizationData_();

	res = 1;

	return res;
} /* _tr17 */


void makeAndPrintSparseMatrix_ P(( void));

#if WSPROTOTYPES
static int _tr18( WSLINK mlp)
#else
static int _tr18(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	makeAndPrintSparseMatrix_();

	res = 1;

	return res;
} /* _tr18 */


void testMain_ P(( void));

#if WSPROTOTYPES
static int _tr19( WSLINK mlp)
#else
static int _tr19(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	testMain_();

	res = 1;

L0:	return res;
} /* _tr19 */


void xx43_ P(( void));

#if WSPROTOTYPES
static int _tr20( WSLINK mlp)
#else
static int _tr20(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx43_();

	res = 1;

L0:	return res;
} /* _tr20 */


void get42_ P(( void));

#if WSPROTOTYPES
static int _tr21( WSLINK mlp)
#else
static int _tr21(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	get42_();

	res = 1;

L0:	return res;
} /* _tr21 */


void add_ P(( void));

#if WSPROTOTYPES
static int _tr22( WSLINK mlp)
#else
static int _tr22(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	add_();

	res = 1;

	return res;
} /* _tr22 */


void addf_ P(( void));

#if WSPROTOTYPES
static int _tr23( WSLINK mlp)
#else
static int _tr23(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addf_();

	res = 1;

	return res;
} /* _tr23 */


void multiout_ P(( void));

#if WSPROTOTYPES
static int _tr24( WSLINK mlp)
#else
static int _tr24(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	multiout_();

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


void receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly_ P(( void));

#if WSPROTOTYPES
static int _tr26( WSLINK mlp)
#else
static int _tr26(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly_();

	res = 1;

	return res;
} /* _tr26 */


void lengthzGet_CUDA P(( void));

#if WSPROTOTYPES
static int _tr27( WSLINK mlp)
#else
static int _tr27(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthzGet_CUDA();

	res = 1;

	return res;
} /* _tr27 */


void lengthfzGet_CUDA P(( void));

#if WSPROTOTYPES
static int _tr28( WSLINK mlp)
#else
static int _tr28(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthfzGet_CUDA();

	res = 1;

	return res;
} /* _tr28 */


void print_CUDA P(( void));

#if WSPROTOTYPES
static int _tr29( WSLINK mlp)
#else
static int _tr29(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	print_CUDA();

	res = 1;

	return res;
} /* _tr29 */


void printv_CUDA P(( void));

#if WSPROTOTYPES
static int _tr30( WSLINK mlp)
#else
static int _tr30(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printv_CUDA();

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


void assertEachInRange_CUDA P(( void));

#if WSPROTOTYPES
static int _tr32( WSLINK mlp)
#else
static int _tr32(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	assertEachInRange_CUDA();

	res = 1;

	return res;
} /* _tr32 */


void axpyWithReindexing_CUDA P(( void));

#if WSPROTOTYPES
static int _tr33( WSLINK mlp)
#else
static int _tr33(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	axpyWithReindexing_CUDA();

	res = 1;

	return res;
} /* _tr33 */


void extract_CUDA P(( void));

#if WSPROTOTYPES
static int _tr34( WSLINK mlp)
#else
static int _tr34(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	extract_CUDA();

	res = 1;

	return res;
} /* _tr34 */


void writeFx_CUDA P(( void));

#if WSPROTOTYPES
static int _tr35( WSLINK mlp)
#else
static int _tr35(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	writeFx_CUDA();

	res = 1;

	return res;
} /* _tr35 */


void readZ_CUDA P(( void));

#if WSPROTOTYPES
static int _tr36( WSLINK mlp)
#else
static int _tr36(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	readZ_CUDA();

	res = 1;

	return res;
} /* _tr36 */


void readZandSetFxRow_CUDA P(( void));

#if WSPROTOTYPES
static int _tr37( WSLINK mlp)
#else
static int _tr37(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	readZandSetFxRow_CUDA();

	res = 1;

	return res;
} /* _tr37 */


void setFxRow_CUDA P(( void));

#if WSPROTOTYPES
static int _tr38( WSLINK mlp)
#else
static int _tr38(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	setFxRow_CUDA();

	res = 1;

	return res;
} /* _tr38 */


void buildFx_CUDA P(( void));

#if WSPROTOTYPES
static int _tr39( WSLINK mlp)
#else
static int _tr39(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFx_CUDA();

	res = 1;

	return res;
} /* _tr39 */


void norm2Fx_CUDA P(( void));

#if WSPROTOTYPES
static int _tr40( WSLINK mlp)
#else
static int _tr40(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	norm2Fx_CUDA();

	res = 1;

	return res;
} /* _tr40 */


void addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_CUDA P(( void));

#if WSPROTOTYPES
static int _tr41( WSLINK mlp)
#else
static int _tr41(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_CUDA();

	res = 1;

	return res;
} /* _tr41 */


void getY_CUDA P(( void));

#if WSPROTOTYPES
static int _tr42( WSLINK mlp)
#else
static int _tr42(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	getY_CUDA();

	res = 1;

	return res;
} /* _tr42 */


void buildFxAndJFxAndSolveRepeatedly_CUDA P(( void));

#if WSPROTOTYPES
static int _tr43( WSLINK mlp)
#else
static int _tr43(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedly_CUDA();

	res = 1;

	return res;
} /* _tr43 */


void receiveAndPrintOptimizationData_CUDA P(( void));

#if WSPROTOTYPES
static int _tr44( WSLINK mlp)
#else
static int _tr44(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveAndPrintOptimizationData_CUDA();

	res = 1;

	return res;
} /* _tr44 */


void makeAndPrintSparseMatrix_CUDA P(( void));

#if WSPROTOTYPES
static int _tr45( WSLINK mlp)
#else
static int _tr45(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	makeAndPrintSparseMatrix_CUDA();

	res = 1;

	return res;
} /* _tr45 */


void testMain_CUDA P(( void));

#if WSPROTOTYPES
static int _tr46( WSLINK mlp)
#else
static int _tr46(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	testMain_CUDA();

	res = 1;

	return res;
} /* _tr46 */


void xx43_CUDA P(( void));

#if WSPROTOTYPES
static int _tr47( WSLINK mlp)
#else
static int _tr47(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx43_CUDA();

	res = 1;

	return res;
} /* _tr47 */


void get42_CUDA P(( void));

#if WSPROTOTYPES
static int _tr48( WSLINK mlp)
#else
static int _tr48(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	get42_CUDA();

	res = 1;

	return res;
} /* _tr48 */


void add_CUDA P(( void));

#if WSPROTOTYPES
static int _tr49( WSLINK mlp)
#else
static int _tr49(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	add_CUDA();

	res = 1;

	return res;
} /* _tr49 */


void addf_CUDA P(( void));

#if WSPROTOTYPES
static int _tr50( WSLINK mlp)
#else
static int _tr50(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addf_CUDA();

	res = 1;

	return res;
} /* _tr50 */


void multiout_CUDA P(( void));

#if WSPROTOTYPES
static int _tr51( WSLINK mlp)
#else
static int _tr51(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	multiout_CUDA();

	res = 1;

	return res;
} /* _tr51 */


void dprintEnabled_get P(( void));

#if WSPROTOTYPES
static int _tr52( WSLINK mlp)
#else
static int _tr52(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_get();

	res = 1;

L0:	return res;
} /* _tr52 */


void lengthP_get P(( void));

#if WSPROTOTYPES
static int _tr53( WSLINK mlp)
#else
static int _tr53(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthP_get();

	res = 1;

L0:	return res;
} /* _tr53 */


void xx_get P(( void));

#if WSPROTOTYPES
static int _tr54( WSLINK mlp)
#else
static int _tr54(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_get();

	res = 1;

L0:	return res;
} /* _tr54 */


void a_get P(( void));

#if WSPROTOTYPES
static int _tr55( WSLINK mlp)
#else
static int _tr55(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_get();

	res = 1;

L0:	return res;
} /* _tr55 */


void b_get P(( void));

#if WSPROTOTYPES
static int _tr56( WSLINK mlp)
#else
static int _tr56(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_get();

	res = 1;

L0:	return res;
} /* _tr56 */


void yy_get P(( void));

#if WSPROTOTYPES
static int _tr57( WSLINK mlp)
#else
static int _tr57(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_get();

	res = 1;

L0:	return res;
} /* _tr57 */


void x_get P(( void));

#if WSPROTOTYPES
static int _tr58( WSLINK mlp)
#else
static int _tr58(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_get();

	res = 1;

L0:	return res;
} /* _tr58 */


void minusFx_get P(( void));

#if WSPROTOTYPES
static int _tr59( WSLINK mlp)
#else
static int _tr59(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	minusFx_get();

	res = 1;

L0:	return res;
} /* _tr59 */


void h_get P(( void));

#if WSPROTOTYPES
static int _tr60( WSLINK mlp)
#else
static int _tr60(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	h_get();

	res = 1;

L0:	return res;
} /* _tr60 */


void yIndices_get P(( void));

#if WSPROTOTYPES
static int _tr61( WSLINK mlp)
#else
static int _tr61(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yIndices_get();

	res = 1;

L0:	return res;
} /* _tr61 */


void dprintEnabled_set P(( void));

#if WSPROTOTYPES
static int _tr62( WSLINK mlp)
#else
static int _tr62(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_set();

	res = 1;

	return res;
} /* _tr62 */


void lengthP_set P(( void));

#if WSPROTOTYPES
static int _tr63( WSLINK mlp)
#else
static int _tr63(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthP_set();

	res = 1;

	return res;
} /* _tr63 */


void xx_set P(( void));

#if WSPROTOTYPES
static int _tr64( WSLINK mlp)
#else
static int _tr64(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_set();

	res = 1;

	return res;
} /* _tr64 */


void a_set P(( void));

#if WSPROTOTYPES
static int _tr65( WSLINK mlp)
#else
static int _tr65(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_set();

	res = 1;

	return res;
} /* _tr65 */


void b_set P(( void));

#if WSPROTOTYPES
static int _tr66( WSLINK mlp)
#else
static int _tr66(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_set();

	res = 1;

	return res;
} /* _tr66 */


void yy_set P(( void));

#if WSPROTOTYPES
static int _tr67( WSLINK mlp)
#else
static int _tr67(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_set();

	res = 1;

	return res;
} /* _tr67 */


void x_set P(( void));

#if WSPROTOTYPES
static int _tr68( WSLINK mlp)
#else
static int _tr68(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_set();

	res = 1;

	return res;
} /* _tr68 */


void minusFx_set P(( void));

#if WSPROTOTYPES
static int _tr69( WSLINK mlp)
#else
static int _tr69(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	minusFx_set();

	res = 1;

	return res;
} /* _tr69 */


void h_set P(( void));

#if WSPROTOTYPES
static int _tr70( WSLINK mlp)
#else
static int _tr70(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	h_set();

	res = 1;

	return res;
} /* _tr70 */


void yIndices_set P(( void));

#if WSPROTOTYPES
static int _tr71( WSLINK mlp)
#else
static int _tr71(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yIndices_set();

	res = 1;

	return res;
} /* _tr71 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((WSLINK));
	const char  *f_name;
	} _tramps[72] = {
		{ 0, 0, _tr0, "lengthzGet_" },
		{ 0, 0, _tr1, "lengthfzGet_" },
		{ 0, 2, _tr2, "print_" },
		{ 0, 2, _tr3, "printv_" },
		{ 0, 2, _tr4, "printd_" },
		{ 0, 2, _tr5, "assertEachInRange_" },
		{ 0, 2, _tr6, "axpyWithReindexing_" },
		{ 0, 2, _tr7, "extract_" },
		{ 0, 2, _tr8, "writeFx_" },
		{ 0, 2, _tr9, "readZ_" },
		{ 0, 2, _tr10, "readZandSetFxRow_" },
		{ 0, 2, _tr11, "setFxRow_" },
		{ 0, 0, _tr12, "buildFx_" },
		{ 0, 0, _tr13, "norm2Fx_" },
		{ 0, 0, _tr14, "addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_" },
		{ 0, 2, _tr15, "getY_" },
		{ 0, 2, _tr16, "buildFxAndJFxAndSolveRepeatedly_" },
		{ 0, 2, _tr17, "receiveAndPrintOptimizationData_" },
		{ 0, 2, _tr18, "makeAndPrintSparseMatrix_" },
		{ 0, 0, _tr19, "testMain_" },
		{ 0, 0, _tr20, "xx43_" },
		{ 0, 0, _tr21, "get42_" },
		{ 0, 2, _tr22, "add_" },
		{ 0, 2, _tr23, "addf_" },
		{ 0, 2, _tr24, "multiout_" },
		{ 0, 2, _tr25, "receiveOptimizationData_" },
		{ 0, 2, _tr26, "receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly_" },
		{ 0, 2, _tr27, "lengthzGet_CUDA" },
		{ 0, 2, _tr28, "lengthfzGet_CUDA" },
		{ 0, 2, _tr29, "print_CUDA" },
		{ 0, 2, _tr30, "printv_CUDA" },
		{ 0, 2, _tr31, "printd_CUDA" },
		{ 0, 2, _tr32, "assertEachInRange_CUDA" },
		{ 0, 2, _tr33, "axpyWithReindexing_CUDA" },
		{ 0, 2, _tr34, "extract_CUDA" },
		{ 0, 2, _tr35, "writeFx_CUDA" },
		{ 0, 2, _tr36, "readZ_CUDA" },
		{ 0, 2, _tr37, "readZandSetFxRow_CUDA" },
		{ 0, 2, _tr38, "setFxRow_CUDA" },
		{ 0, 2, _tr39, "buildFx_CUDA" },
		{ 0, 2, _tr40, "norm2Fx_CUDA" },
		{ 0, 2, _tr41, "addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore_CUDA" },
		{ 0, 2, _tr42, "getY_CUDA" },
		{ 0, 2, _tr43, "buildFxAndJFxAndSolveRepeatedly_CUDA" },
		{ 0, 2, _tr44, "receiveAndPrintOptimizationData_CUDA" },
		{ 0, 2, _tr45, "makeAndPrintSparseMatrix_CUDA" },
		{ 0, 2, _tr46, "testMain_CUDA" },
		{ 0, 2, _tr47, "xx43_CUDA" },
		{ 0, 2, _tr48, "get42_CUDA" },
		{ 0, 2, _tr49, "add_CUDA" },
		{ 0, 2, _tr50, "addf_CUDA" },
		{ 0, 2, _tr51, "multiout_CUDA" },
		{ 0, 0, _tr52, "dprintEnabled_get" },
		{ 0, 0, _tr53, "lengthP_get" },
		{ 0, 0, _tr54, "xx_get" },
		{ 0, 0, _tr55, "a_get" },
		{ 0, 0, _tr56, "b_get" },
		{ 0, 0, _tr57, "yy_get" },
		{ 0, 0, _tr58, "x_get" },
		{ 0, 0, _tr59, "minusFx_get" },
		{ 0, 0, _tr60, "h_get" },
		{ 0, 0, _tr61, "yIndices_get" },
		{ 0, 2, _tr62, "dprintEnabled_set" },
		{ 0, 2, _tr63, "lengthP_set" },
		{ 0, 2, _tr64, "xx_set" },
		{ 0, 2, _tr65, "a_set" },
		{ 0, 2, _tr66, "b_set" },
		{ 0, 2, _tr67, "yy_set" },
		{ 0, 2, _tr68, "x_set" },
		{ 0, 2, _tr69, "minusFx_set" },
		{ 0, 2, _tr70, "h_set" },
		{ 0, 2, _tr71, "yIndices_set" }
		};

static const char* evalstrs[] = {
	"BeginPackage@\"SOPCompiled`Private`\";",
	(const char*)0,
	"lengthzGet::usage = \"lengthz\"",
	(const char*)0,
	"lengthfzGet::usage = \"lengthfz\"",
	(const char*)0,
	"print::usage = \"prints a string to stdout\"",
	(const char*)0,
	"printv::usage = \"dprints a vector of doubles, space separated an",
	"d newline terminated\"",
	(const char*)0,
	"printd::usage = \"dprints a vector of integers, space separated a",
	"nd newline terminated\"",
	(const char*)0,
	"assertEachInRange::usage = \"computes the same as BoolEval[min <=",
	" v <= max]\"",
	(const char*)0,
	"axpyWithReindexing::usage = \"targetBase[[targetIndices]] += a * ",
	"addedValues. Repeated indices are not supported, so addedValues ",
	"cannot be longer than the target.Note that not necessarily all o",
	"f target is updated\"",
	(const char*)0,
	"extract::usage = \"target = source[[sourceIndices]]. Note that al",
	"l of target is updated\"",
	(const char*)0,
	"writeFx::usage = \"F(x)_i = val\"",
	(const char*)0,
	"readZ::usage = \"compute and store Fx[[rowfz;;rowfz+lengthfz-1]] ",
	"= f(z) and return the z required for that\"",
	(const char*)0,
	"readZandSetFxRow::usage = \"compute and store Fx[[rowfz;;rowfz+le",
	"ngthfz-1]] = f(z) and return the z required for that\"",
	(const char*)0,
	"setFxRow::usage = \"compute and store Fx[[rowfz;;rowfz+lengthfz-1",
	"]]\"",
	(const char*)0,
	"buildFx::usage = \"from the current x, computes F(x)\"",
	(const char*)0,
	"norm2Fx::usage = \"Assuming F(x) is computed, returns ||F(x)||_2^",
	"2\"",
	(const char*)0,
	"addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBe",
	"fore::usage = \"scales h such that F(x0 + h) < F(x) in the 2-norm",
	" and updates x = x0 + hreturns total energy delta achieved\"",
	(const char*)0,
	"getY::usage = \"Extracts from x the elements that are ylengthY mu",
	"st match the length passed at initializationTODO make WSTP suppo",
	"rt having global variables specify the necessary array length, s",
	"upport non size_t lengths\"",
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
	"g where to put the corresponding values. Note: This is a prototy",
	"ping function without any further purpose\"",
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
	"multiout::usage = \"return more than one thing\"",
	(const char*)0,
	"receiveOptimizationData::usage = \"Receives x, sparseDerivativeZt",
	"oYIndices, xIndices and yIndicesAppropriately sized vectors for ",
	"receiving these data items is allocated in __managed__ memory, h",
	"ence this is a CPU only function\"",
	(const char*)0,
	"receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly::usage = ",
	"\"Receives x, sparseDerivativeZtoYIndices, xIndices and yIndicesA",
	"ppropriately sized vectors for receiving these data items is all",
	"ocated in __managed__ memory, hence this is a CPU only functionc",
	"urrently also builds F(x), JF(x), but that could also be done on",
	" the GPU laterit also calls solve, because J is built in local m",
	"emory so it would be lost later\"",
	(const char*)0,
	"lengthzGetCUDA::usage = \"lengthz\"",
	(const char*)0,
	"lengthfzGetCUDA::usage = \"lengthfz\"",
	(const char*)0,
	"printCUDA::usage = \"prints a string to stdout\"",
	(const char*)0,
	"printvCUDA::usage = \"dprints a vector of doubles, space separate",
	"d and newline terminated\"",
	(const char*)0,
	"printdCUDA::usage = \"dprints a vector of integers, space separat",
	"ed and newline terminated\"",
	(const char*)0,
	"assertEachInRangeCUDA::usage = \"computes the same as BoolEval[mi",
	"n <= v <= max]\"",
	(const char*)0,
	"axpyWithReindexingCUDA::usage = \"targetBase[[targetIndices]] += ",
	"a * addedValues. Repeated indices are not supported, so addedVal",
	"ues cannot be longer than the target.Note that not necessarily a",
	"ll of target is updated\"",
	(const char*)0,
	"extractCUDA::usage = \"target = source[[sourceIndices]]. Note tha",
	"t all of target is updated\"",
	(const char*)0,
	"writeFxCUDA::usage = \"F(x)_i = val\"",
	(const char*)0,
	"readZCUDA::usage = \"compute and store Fx[[rowfz;;rowfz+lengthfz-",
	"1]] = f(z) and return the z required for that\"",
	(const char*)0,
	"readZandSetFxRowCUDA::usage = \"compute and store Fx[[rowfz;;rowf",
	"z+lengthfz-1]] = f(z) and return the z required for that\"",
	(const char*)0,
	"setFxRowCUDA::usage = \"compute and store Fx[[rowfz;;rowfz+length",
	"fz-1]]\"",
	(const char*)0,
	"buildFxCUDA::usage = \"from the current x, computes F(x)\"",
	(const char*)0,
	"norm2FxCUDA::usage = \"Assuming F(x) is computed, returns ||F(x)|",
	"|_2^2\"",
	(const char*)0,
	"addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBe",
	"foreCUDA::usage = \"scales h such that F(x0 + h) < F(x) in the 2-",
	"norm and updates x = x0 + hreturns total energy delta achieved\"",
	(const char*)0,
	"getYCUDA::usage = \"Extracts from x the elements that are ylength",
	"Y must match the length passed at initializationTODO make WSTP s",
	"upport having global variables specify the necessary array lengt",
	"h, support non size_t lengths\"",
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
	"fying where to put the corresponding values. Note: This is a pro",
	"totyping function without any further purpose\"",
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
	"multioutCUDA::usage = \"return more than one thing\"",
	(const char*)0,
	"dprintEnabledGet::usage = \"if true, dprintf writes to stdout, ot",
	"herwise dprintf does nothingIt would be more efficient to compil",
	"e with dprintf defined to nothing of course\"",
	(const char*)0,
	"lengthPGet::usage = \"amount of 'points' at which the function f ",
	"is evaluated.lengthP * lengthz is the length of xIndices, and sp",
	"arseDerivativeZtoYIndices contains lengthP sequences of the form",
	" (k [k many] [k many]) \"",
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
	"minusFxGet::usage = \"-F(x)\"",
	(const char*)0,
	"hGet::usage = \"h, the update to y, subset of x, the parameters c",
	"urrently optimized over\"",
	(const char*)0,
	"yIndicesGet::usage = \"the indices into x that indicate where the",
	" y are\"",
	(const char*)0,
	"dprintEnabledSet::usage = \"if true, dprintf writes to stdout, ot",
	"herwise dprintf does nothingIt would be more efficient to compil",
	"e with dprintf defined to nothing of course\"",
	(const char*)0,
	"lengthPSet::usage = \"amount of 'points' at which the function f ",
	"is evaluated.lengthP * lengthz is the length of xIndices, and sp",
	"arseDerivativeZtoYIndices contains lengthP sequences of the form",
	" (k [k many] [k many]) \"",
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
	"minusFxSet::usage = \"-F(x)\"",
	(const char*)0,
	"hSet::usage = \"h, the update to y, subset of x, the parameters c",
	"urrently optimized over\"",
	(const char*)0,
	"yIndicesSet::usage = \"the indices into x that indicate where the",
	" y are\"",
	(const char*)0,
	"EndPackage[];",
	(const char*)0,
	(const char*)0
};
#define CARDOF_EVALSTRS 74

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
	if (_res) _res = _definepattern(mlp, (char *)"lengthzGet[]", (char *)"{}", 0);
	if (_res) _res = _doevalstr( mlp, 1);
	if (_res) _res = _definepattern(mlp, (char *)"lengthfzGet[]", (char *)"{}", 1);
	if (_res) _res = _doevalstr( mlp, 2);
	if (_res) _res = _definepattern(mlp, (char *)"print[x : _String]", (char *)"{x}", 2);
	if (_res) _res = _doevalstr( mlp, 3);
	if (_res) _res = _definepattern(mlp, (char *)"printv[v : {___Real}]", (char *)"{v}", 3);
	if (_res) _res = _doevalstr( mlp, 4);
	if (_res) _res = _definepattern(mlp, (char *)"printd[v : {___Integer}]", (char *)"{v}", 4);
	if (_res) _res = _doevalstr( mlp, 5);
	if (_res) _res = _definepattern(mlp, (char *)"assertEachInRange[v : {___Integer}, min : _Integer, max : _Integer]", (char *)"{v, min, max}", 5);
	if (_res) _res = _doevalstr( mlp, 6);
	if (_res) _res = _definepattern(mlp, (char *)"axpyWithReindexing[targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]", (char *)"{targetBase, a, addedValues, targetIndices}", 6);
	if (_res) _res = _doevalstr( mlp, 7);
	if (_res) _res = _definepattern(mlp, (char *)"extract[source : {___Real}, sourceIndices : {___Integer}]", (char *)"{source, sourceIndices}", 7);
	if (_res) _res = _doevalstr( mlp, 8);
	if (_res) _res = _definepattern(mlp, (char *)"writeFx[i : _Integer, val : _Real]", (char *)"{i, val}", 8);
	if (_res) _res = _doevalstr( mlp, 9);
	if (_res) _res = _definepattern(mlp, (char *)"readZ[rowz : _Integer]", (char *)"{rowz}", 9);
	if (_res) _res = _doevalstr( mlp, 10);
	if (_res) _res = _definepattern(mlp, (char *)"readZandSetFxRow[rowz : _Integer, rowfz : _Integer]", (char *)"{rowz, rowfz}", 10);
	if (_res) _res = _doevalstr( mlp, 11);
	if (_res) _res = _definepattern(mlp, (char *)"setFxRow[rowz : _Integer, rowfz : _Integer]", (char *)"{rowz, rowfz}", 11);
	if (_res) _res = _doevalstr( mlp, 12);
	if (_res) _res = _definepattern(mlp, (char *)"buildFx[]", (char *)"{}", 12);
	if (_res) _res = _doevalstr( mlp, 13);
	if (_res) _res = _definepattern(mlp, (char *)"norm2Fx[]", (char *)"{}", 13);
	if (_res) _res = _doevalstr( mlp, 14);
	if (_res) _res = _definepattern(mlp, (char *)"addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBefore[]", (char *)"{}", 14);
	if (_res) _res = _doevalstr( mlp, 15);
	if (_res) _res = _definepattern(mlp, (char *)"getY[lengthY : _Integer]", (char *)"{lengthY}", 15);
	if (_res) _res = _doevalstr( mlp, 16);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedly[iterations : _Integer]", (char *)"{iterations}", 16);
	if (_res) _res = _doevalstr( mlp, 17);
	if (_res) _res = _definepattern(mlp, (char *)"receiveAndPrintOptimizationData[lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]", (char *)"{lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}", 17);
	if (_res) _res = _doevalstr( mlp, 18);
	if (_res) _res = _definepattern(mlp, (char *)"makeAndPrintSparseMatrix[m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]", (char *)"{m, n, x, ij}", 18);
	if (_res) _res = _doevalstr( mlp, 19);
	if (_res) _res = _definepattern(mlp, (char *)"testMain[]", (char *)"{}", 19);
	if (_res) _res = _doevalstr( mlp, 20);
	if (_res) _res = _definepattern(mlp, (char *)"xx43[]", (char *)"{}", 20);
	if (_res) _res = _doevalstr( mlp, 21);
	if (_res) _res = _definepattern(mlp, (char *)"get42[]", (char *)"{}", 21);
	if (_res) _res = _doevalstr( mlp, 22);
	if (_res) _res = _definepattern(mlp, (char *)"add[x : _Integer, y : _Integer]", (char *)"{x, y}", 22);
	if (_res) _res = _doevalstr( mlp, 23);
	if (_res) _res = _definepattern(mlp, (char *)"addf[x : _Real, y : _Real]", (char *)"{x, y}", 23);
	if (_res) _res = _doevalstr( mlp, 24);
	if (_res) _res = _definepattern(mlp, (char *)"multiout[x : {___Integer}]", (char *)"{x}", 24);
	if (_res) _res = _doevalstr( mlp, 25);
	if (_res) _res = _definepattern(mlp, (char *)"receiveOptimizationData[xI : {___Real}, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}]", (char *)"{xI, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI}", 25);
	if (_res) _res = _doevalstr( mlp, 26);
	if (_res) _res = _definepattern(mlp, (char *)"receiveOptimizationDataBuildFxAndJFxAndSolveRepeatedly[xI : {___Real}, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}, iterations : _Integer]", (char *)"{xI, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI, iterations}", 26);
	if (_res) _res = _doevalstr( mlp, 27);
	if (_res) _res = _definepattern(mlp, (char *)"lengthzGetCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 27);
	if (_res) _res = _doevalstr( mlp, 28);
	if (_res) _res = _definepattern(mlp, (char *)"lengthfzGetCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 28);
	if (_res) _res = _doevalstr( mlp, 29);
	if (_res) _res = _definepattern(mlp, (char *)"printCUDA[gridDim_Integer, blockDim_Integer, x : _String]", (char *)"{gridDim, blockDim, x}", 29);
	if (_res) _res = _doevalstr( mlp, 30);
	if (_res) _res = _definepattern(mlp, (char *)"printvCUDA[gridDim_Integer, blockDim_Integer, v : {___Real}]", (char *)"{gridDim, blockDim, v}", 30);
	if (_res) _res = _doevalstr( mlp, 31);
	if (_res) _res = _definepattern(mlp, (char *)"printdCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}]", (char *)"{gridDim, blockDim, v}", 31);
	if (_res) _res = _doevalstr( mlp, 32);
	if (_res) _res = _definepattern(mlp, (char *)"assertEachInRangeCUDA[gridDim_Integer, blockDim_Integer, v : {___Integer}, min : _Integer, max : _Integer]", (char *)"{gridDim, blockDim, v, min, max}", 32);
	if (_res) _res = _doevalstr( mlp, 33);
	if (_res) _res = _definepattern(mlp, (char *)"axpyWithReindexingCUDA[gridDim_Integer, blockDim_Integer, targetBase : {___Real}, a : _Real, addedValues : {___Real}, targetIndices : {___Integer}]", (char *)"{gridDim, blockDim, targetBase, a, addedValues, targetIndices}", 33);
	if (_res) _res = _doevalstr( mlp, 34);
	if (_res) _res = _definepattern(mlp, (char *)"extractCUDA[gridDim_Integer, blockDim_Integer, source : {___Real}, sourceIndices : {___Integer}]", (char *)"{gridDim, blockDim, source, sourceIndices}", 34);
	if (_res) _res = _doevalstr( mlp, 35);
	if (_res) _res = _definepattern(mlp, (char *)"writeFxCUDA[gridDim_Integer, blockDim_Integer, i : _Integer, val : _Real]", (char *)"{gridDim, blockDim, i, val}", 35);
	if (_res) _res = _doevalstr( mlp, 36);
	if (_res) _res = _definepattern(mlp, (char *)"readZCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer]", (char *)"{gridDim, blockDim, rowz}", 36);
	if (_res) _res = _doevalstr( mlp, 37);
	if (_res) _res = _definepattern(mlp, (char *)"readZandSetFxRowCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer, rowfz : _Integer]", (char *)"{gridDim, blockDim, rowz, rowfz}", 37);
	if (_res) _res = _doevalstr( mlp, 38);
	if (_res) _res = _definepattern(mlp, (char *)"setFxRowCUDA[gridDim_Integer, blockDim_Integer, rowz : _Integer, rowfz : _Integer]", (char *)"{gridDim, blockDim, rowz, rowfz}", 38);
	if (_res) _res = _doevalstr( mlp, 39);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 39);
	if (_res) _res = _doevalstr( mlp, 40);
	if (_res) _res = _definepattern(mlp, (char *)"norm2FxCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 40);
	if (_res) _res = _doevalstr( mlp, 41);
	if (_res) _res = _definepattern(mlp, (char *)"addContinuouslySmallerMultiplesOfHtoXUntilNorm2FxIsSmallerThanBeforeCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 41);
	if (_res) _res = _doevalstr( mlp, 42);
	if (_res) _res = _definepattern(mlp, (char *)"getYCUDA[gridDim_Integer, blockDim_Integer, lengthY : _Integer]", (char *)"{gridDim, blockDim, lengthY}", 42);
	if (_res) _res = _doevalstr( mlp, 43);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedlyCUDA[gridDim_Integer, blockDim_Integer, iterations : _Integer]", (char *)"{gridDim, blockDim, iterations}", 43);
	if (_res) _res = _doevalstr( mlp, 44);
	if (_res) _res = _definepattern(mlp, (char *)"receiveAndPrintOptimizationDataCUDA[gridDim_Integer, blockDim_Integer, lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]", (char *)"{gridDim, blockDim, lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}", 44);
	if (_res) _res = _doevalstr( mlp, 45);
	if (_res) _res = _definepattern(mlp, (char *)"makeAndPrintSparseMatrixCUDA[gridDim_Integer, blockDim_Integer, m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]", (char *)"{gridDim, blockDim, m, n, x, ij}", 45);
	if (_res) _res = _doevalstr( mlp, 46);
	if (_res) _res = _definepattern(mlp, (char *)"testMainCUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 46);
	if (_res) _res = _doevalstr( mlp, 47);
	if (_res) _res = _definepattern(mlp, (char *)"xx43CUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 47);
	if (_res) _res = _doevalstr( mlp, 48);
	if (_res) _res = _definepattern(mlp, (char *)"get42CUDA[gridDim_Integer, blockDim_Integer]", (char *)"{gridDim, blockDim}", 48);
	if (_res) _res = _doevalstr( mlp, 49);
	if (_res) _res = _definepattern(mlp, (char *)"addCUDA[gridDim_Integer, blockDim_Integer, x : _Integer, y : _Integer]", (char *)"{gridDim, blockDim, x, y}", 49);
	if (_res) _res = _doevalstr( mlp, 50);
	if (_res) _res = _definepattern(mlp, (char *)"addfCUDA[gridDim_Integer, blockDim_Integer, x : _Real, y : _Real]", (char *)"{gridDim, blockDim, x, y}", 50);
	if (_res) _res = _doevalstr( mlp, 51);
	if (_res) _res = _definepattern(mlp, (char *)"multioutCUDA[gridDim_Integer, blockDim_Integer, x : {___Integer}]", (char *)"{gridDim, blockDim, x}", 51);
	if (_res) _res = _doevalstr( mlp, 52);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledGet[]", (char *)"{}", 52);
	if (_res) _res = _doevalstr( mlp, 53);
	if (_res) _res = _definepattern(mlp, (char *)"lengthPGet[]", (char *)"{}", 53);
	if (_res) _res = _doevalstr( mlp, 54);
	if (_res) _res = _definepattern(mlp, (char *)"xxGet[]", (char *)"{}", 54);
	if (_res) _res = _doevalstr( mlp, 55);
	if (_res) _res = _definepattern(mlp, (char *)"aGet[]", (char *)"{}", 55);
	if (_res) _res = _doevalstr( mlp, 56);
	if (_res) _res = _definepattern(mlp, (char *)"bGet[]", (char *)"{}", 56);
	if (_res) _res = _doevalstr( mlp, 57);
	if (_res) _res = _definepattern(mlp, (char *)"yyGet[]", (char *)"{}", 57);
	if (_res) _res = _doevalstr( mlp, 58);
	if (_res) _res = _definepattern(mlp, (char *)"xGet[]", (char *)"{}", 58);
	if (_res) _res = _doevalstr( mlp, 59);
	if (_res) _res = _definepattern(mlp, (char *)"minusFxGet[]", (char *)"{}", 59);
	if (_res) _res = _doevalstr( mlp, 60);
	if (_res) _res = _definepattern(mlp, (char *)"hGet[]", (char *)"{}", 60);
	if (_res) _res = _doevalstr( mlp, 61);
	if (_res) _res = _definepattern(mlp, (char *)"yIndicesGet[]", (char *)"{}", 61);
	if (_res) _res = _doevalstr( mlp, 62);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledSet[dprintEnabled : _Integer]", (char *)"{dprintEnabled}", 62);
	if (_res) _res = _doevalstr( mlp, 63);
	if (_res) _res = _definepattern(mlp, (char *)"lengthPSet[lengthP : _Integer]", (char *)"{lengthP}", 63);
	if (_res) _res = _doevalstr( mlp, 64);
	if (_res) _res = _definepattern(mlp, (char *)"xxSet[xx : _Integer]", (char *)"{xx}", 64);
	if (_res) _res = _doevalstr( mlp, 65);
	if (_res) _res = _definepattern(mlp, (char *)"aSet[a : _Real]", (char *)"{a}", 65);
	if (_res) _res = _doevalstr( mlp, 66);
	if (_res) _res = _definepattern(mlp, (char *)"bSet[b : _Real]", (char *)"{b}", 66);
	if (_res) _res = _doevalstr( mlp, 67);
	if (_res) _res = _definepattern(mlp, (char *)"yySet[yy : _Real]", (char *)"{yy}", 67);
	if (_res) _res = _doevalstr( mlp, 68);
	if (_res) _res = _definepattern(mlp, (char *)"xSet[x : {___Real}]", (char *)"{x}", 68);
	if (_res) _res = _doevalstr( mlp, 69);
	if (_res) _res = _definepattern(mlp, (char *)"minusFxSet[minusFx : {___Real}]", (char *)"{minusFx}", 69);
	if (_res) _res = _doevalstr( mlp, 70);
	if (_res) _res = _definepattern(mlp, (char *)"hSet[h : {___Real}]", (char *)"{h}", 70);
	if (_res) _res = _doevalstr( mlp, 71);
	if (_res) _res = _definepattern(mlp, (char *)"yIndicesSet[yIndices : {___Integer}]", (char *)"{yIndices}", 71);
	if (_res) _res = _doevalstr( mlp, 72);
	if (_res) _res = _doevalstr( mlp, 73);
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
	return _WSDoCallPacket( mlp, _tramps, 72);
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
 
