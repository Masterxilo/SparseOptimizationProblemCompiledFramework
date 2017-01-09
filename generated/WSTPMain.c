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


void printd_ P(( void));

#if WSPROTOTYPES
static int _tr3( WSLINK mlp)
#else
static int _tr3(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printd_();

	res = 1;

	return res;
} /* _tr3 */


void printv_ P(( void));

#if WSPROTOTYPES
static int _tr4( WSLINK mlp)
#else
static int _tr4(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	printv_();

	res = 1;

	return res;
} /* _tr4 */


void lengthzGet_ P(( void));

#if WSPROTOTYPES
static int _tr5( WSLINK mlp)
#else
static int _tr5(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthzGet_();

	res = 1;

L0:	return res;
} /* _tr5 */


void lengthfzGet_ P(( void));

#if WSPROTOTYPES
static int _tr6( WSLINK mlp)
#else
static int _tr6(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	lengthfzGet_();

	res = 1;

L0:	return res;
} /* _tr6 */


void getY_ P(( void));

#if WSPROTOTYPES
static int _tr7( WSLINK mlp)
#else
static int _tr7(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	getY_();

	res = 1;

	return res;
} /* _tr7 */


void buildFxAndJFxAndSolveRepeatedly_ P(( void));

#if WSPROTOTYPES
static int _tr8( WSLINK mlp)
#else
static int _tr8(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedly_();

	res = 1;

	return res;
} /* _tr8 */


void buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_ P(( void));

#if WSPROTOTYPES
static int _tr9( WSLINK mlp)
#else
static int _tr9(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_();

	res = 1;

	return res;
} /* _tr9 */


void receiveAndPrintOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr10( WSLINK mlp)
#else
static int _tr10(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveAndPrintOptimizationData_();

	res = 1;

	return res;
} /* _tr10 */


void makeAndPrintSparseMatrix_ P(( void));

#if WSPROTOTYPES
static int _tr11( WSLINK mlp)
#else
static int _tr11(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	makeAndPrintSparseMatrix_();

	res = 1;

	return res;
} /* _tr11 */


void testMain_ P(( void));

#if WSPROTOTYPES
static int _tr12( WSLINK mlp)
#else
static int _tr12(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	testMain_();

	res = 1;

L0:	return res;
} /* _tr12 */


void xx43_ P(( void));

#if WSPROTOTYPES
static int _tr13( WSLINK mlp)
#else
static int _tr13(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx43_();

	res = 1;

L0:	return res;
} /* _tr13 */


void get42_ P(( void));

#if WSPROTOTYPES
static int _tr14( WSLINK mlp)
#else
static int _tr14(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	get42_();

	res = 1;

L0:	return res;
} /* _tr14 */


void add_ P(( void));

#if WSPROTOTYPES
static int _tr15( WSLINK mlp)
#else
static int _tr15(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	add_();

	res = 1;

	return res;
} /* _tr15 */


void addf_ P(( void));

#if WSPROTOTYPES
static int _tr16( WSLINK mlp)
#else
static int _tr16(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	addf_();

	res = 1;

	return res;
} /* _tr16 */


void multiout_ P(( void));

#if WSPROTOTYPES
static int _tr17( WSLINK mlp)
#else
static int _tr17(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	multiout_();

	res = 1;

	return res;
} /* _tr17 */


void mainc_ P(( void));

#if WSPROTOTYPES
static int _tr18( WSLINK mlp)
#else
static int _tr18(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	mainc_();

	res = 1;

L0:	return res;
} /* _tr18 */


void setPartitions_ P(( void));

#if WSPROTOTYPES
static int _tr19( WSLINK mlp)
#else
static int _tr19(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	setPartitions_();

	res = 1;

	return res;
} /* _tr19 */


void receiveSharedOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr20( WSLINK mlp)
#else
static int _tr20(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveSharedOptimizationData_();

	res = 1;

	return res;
} /* _tr20 */


void receiveOptimizationData_ P(( void));

#if WSPROTOTYPES
static int _tr21( WSLINK mlp)
#else
static int _tr21(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	receiveOptimizationData_();

	res = 1;

	return res;
} /* _tr21 */


void dprintEnabled_get P(( void));

#if WSPROTOTYPES
static int _tr22( WSLINK mlp)
#else
static int _tr22(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_get();

	res = 1;

L0:	return res;
} /* _tr22 */


void xx_get P(( void));

#if WSPROTOTYPES
static int _tr23( WSLINK mlp)
#else
static int _tr23(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_get();

	res = 1;

L0:	return res;
} /* _tr23 */


void a_get P(( void));

#if WSPROTOTYPES
static int _tr24( WSLINK mlp)
#else
static int _tr24(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_get();

	res = 1;

L0:	return res;
} /* _tr24 */


void b_get P(( void));

#if WSPROTOTYPES
static int _tr25( WSLINK mlp)
#else
static int _tr25(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_get();

	res = 1;

L0:	return res;
} /* _tr25 */


void yy_get P(( void));

#if WSPROTOTYPES
static int _tr26( WSLINK mlp)
#else
static int _tr26(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_get();

	res = 1;

L0:	return res;
} /* _tr26 */


void x_get P(( void));

#if WSPROTOTYPES
static int _tr27( WSLINK mlp)
#else
static int _tr27(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if ( ! WSNewPacket(mlp) ) goto L0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_get();

	res = 1;

L0:	return res;
} /* _tr27 */


void dprintEnabled_set P(( void));

#if WSPROTOTYPES
static int _tr28( WSLINK mlp)
#else
static int _tr28(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	dprintEnabled_set();

	res = 1;

	return res;
} /* _tr28 */


void xx_set P(( void));

#if WSPROTOTYPES
static int _tr29( WSLINK mlp)
#else
static int _tr29(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	xx_set();

	res = 1;

	return res;
} /* _tr29 */


void a_set P(( void));

#if WSPROTOTYPES
static int _tr30( WSLINK mlp)
#else
static int _tr30(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	a_set();

	res = 1;

	return res;
} /* _tr30 */


void b_set P(( void));

#if WSPROTOTYPES
static int _tr31( WSLINK mlp)
#else
static int _tr31(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	b_set();

	res = 1;

	return res;
} /* _tr31 */


void yy_set P(( void));

#if WSPROTOTYPES
static int _tr32( WSLINK mlp)
#else
static int _tr32(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	yy_set();

	res = 1;

	return res;
} /* _tr32 */


void x_set P(( void));

#if WSPROTOTYPES
static int _tr33( WSLINK mlp)
#else
static int _tr33(mlp) WSLINK mlp;
#endif
{
	int	res = 0;
	if( !mlp) return res; /* avoid unused parameter warning */

	x_set();

	res = 1;

	return res;
} /* _tr33 */


static struct func {
	int   f_nargs;
	int   manual;
	int   (*f_func)P((WSLINK));
	const char  *f_name;
	} _tramps[34] = {
		{ 0, 2, _tr0, "f_" },
		{ 0, 2, _tr1, "df_" },
		{ 0, 2, _tr2, "print_" },
		{ 0, 2, _tr3, "printd_" },
		{ 0, 2, _tr4, "printv_" },
		{ 0, 0, _tr5, "lengthzGet_" },
		{ 0, 0, _tr6, "lengthfzGet_" },
		{ 0, 2, _tr7, "getY_" },
		{ 0, 2, _tr8, "buildFxAndJFxAndSolveRepeatedly_" },
		{ 0, 2, _tr9, "buildFxAndJFxAndSolveRepeatedlyThreadIdPartition_" },
		{ 0, 2, _tr10, "receiveAndPrintOptimizationData_" },
		{ 0, 2, _tr11, "makeAndPrintSparseMatrix_" },
		{ 0, 0, _tr12, "testMain_" },
		{ 0, 0, _tr13, "xx43_" },
		{ 0, 0, _tr14, "get42_" },
		{ 0, 2, _tr15, "add_" },
		{ 0, 2, _tr16, "addf_" },
		{ 0, 2, _tr17, "multiout_" },
		{ 0, 0, _tr18, "mainc_" },
		{ 0, 2, _tr19, "setPartitions_" },
		{ 0, 2, _tr20, "receiveSharedOptimizationData_" },
		{ 0, 2, _tr21, "receiveOptimizationData_" },
		{ 0, 0, _tr22, "dprintEnabled_get" },
		{ 0, 0, _tr23, "xx_get" },
		{ 0, 0, _tr24, "a_get" },
		{ 0, 0, _tr25, "b_get" },
		{ 0, 0, _tr26, "yy_get" },
		{ 0, 0, _tr27, "x_get" },
		{ 0, 2, _tr28, "dprintEnabled_set" },
		{ 0, 2, _tr29, "xx_set" },
		{ 0, 2, _tr30, "a_set" },
		{ 0, 2, _tr31, "b_set" },
		{ 0, 2, _tr32, "yy_set" },
		{ 0, 2, _tr33, "x_set" }
		};

static const char* evalstrs[] = {
	"$oldContextPath = $ContextPath; $ContextPath = {\"System`\"};",
	(const char*)0,
	"Begin@\"SOPCompiled`Private`\";",
	(const char*)0,
	"ClearAll@\"SOPCompiled`Private`*\";",
	(const char*)0,
	"f::usage = \"the local energy fvector computing function\"",
	(const char*)0,
	"df::usage = \"the derivatives along the i-th variable of the loca",
	"l energy fvector computing function\"",
	(const char*)0,
	"print::usage = \"prints a string to stdout\"",
	(const char*)0,
	"printd::usage = \"dprints a fvector of integers, space separated ",
	"and newline terminated\"",
	(const char*)0,
	"printv::usage = \"dprints a fvector of doubles, space separated a",
	"nd newline terminated\"",
	(const char*)0,
	"lengthzGet::usage = \"lengthz\"",
	(const char*)0,
	"lengthfzGet::usage = \"lengthfz\"",
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
	"buildFxAndJFxAndSolveRepeatedlyThreadIdPartition::usage = \"build",
	"FxAndJFxAndSolveRepeatedly on the partition given by linear_glob",
	"al_threadId.does nothing when linear_global_threadId is >= parti",
	"tionsTODO this should be the block id, threads in the same block",
	" should cooperate in the same partition\"",
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
	"g where to put the corresponding values (triplet form) then cs_p",
	"rints it to stdout both in column form and vanilla.The matrix sh",
	"ould be fairly small because the required intermediate storage i",
	"s on the stack.Note: This is a prototyping function without any ",
	"further purpose\"",
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
	"mainc::usage = \"\"",
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
	"xGet::usage = \"stores the current data fvector 'x' which is upda",
	"ted to reduce the energy ||F(x)||^2\"",
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
	"xSet::usage = \"stores the current data fvector 'x' which is upda",
	"ted to reduce the energy ||F(x)||^2\"",
	(const char*)0,
	"End[];",
	(const char*)0,
	"$ContextPath = $oldContextPath;",
	(const char*)0,
	(const char*)0
};
#define CARDOF_EVALSTRS 39

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
	if (_res) _res = _doevalstr( mlp, 2);
	if (_res) _res = _definepattern(mlp, (char *)"f[input : {___Real}]", (char *)"{input}", 0);
	if (_res) _res = _doevalstr( mlp, 3);
	if (_res) _res = _definepattern(mlp, (char *)"df[i : _Integer, input : {___Real}]", (char *)"{i, input}", 1);
	if (_res) _res = _doevalstr( mlp, 4);
	if (_res) _res = _definepattern(mlp, (char *)"print[x : _String]", (char *)"{x}", 2);
	if (_res) _res = _doevalstr( mlp, 5);
	if (_res) _res = _definepattern(mlp, (char *)"printd[v : {___Integer}]", (char *)"{v}", 3);
	if (_res) _res = _doevalstr( mlp, 6);
	if (_res) _res = _definepattern(mlp, (char *)"printv[v : {___Real}]", (char *)"{v}", 4);
	if (_res) _res = _doevalstr( mlp, 7);
	if (_res) _res = _definepattern(mlp, (char *)"lengthzGet[]", (char *)"{}", 5);
	if (_res) _res = _doevalstr( mlp, 8);
	if (_res) _res = _definepattern(mlp, (char *)"lengthfzGet[]", (char *)"{}", 6);
	if (_res) _res = _doevalstr( mlp, 9);
	if (_res) _res = _definepattern(mlp, (char *)"getY[partition : _Integer, lengthY : _Integer]", (char *)"{partition, lengthY}", 7);
	if (_res) _res = _doevalstr( mlp, 10);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedly[partition : _Integer, iterations : _Integer]", (char *)"{partition, iterations}", 8);
	if (_res) _res = _doevalstr( mlp, 11);
	if (_res) _res = _definepattern(mlp, (char *)"buildFxAndJFxAndSolveRepeatedlyThreadIdPartition[iterations : _Integer]", (char *)"{iterations}", 9);
	if (_res) _res = _doevalstr( mlp, 12);
	if (_res) _res = _definepattern(mlp, (char *)"receiveAndPrintOptimizationData[lengthz : _Integer, lengthfz : _Integer, x : {___Real}, sparseDerivativeZtoYIndices : {___Integer}, xIndices : {___Integer}, yIndices : {___Integer}]", (char *)"{lengthz, lengthfz, x, sparseDerivativeZtoYIndices, xIndices, yIndices}", 10);
	if (_res) _res = _doevalstr( mlp, 13);
	if (_res) _res = _definepattern(mlp, (char *)"makeAndPrintSparseMatrix[m : _Integer, n : _Integer, x : {___Real}, ij : {___Integer}]", (char *)"{m, n, x, ij}", 11);
	if (_res) _res = _doevalstr( mlp, 14);
	if (_res) _res = _definepattern(mlp, (char *)"testMain[]", (char *)"{}", 12);
	if (_res) _res = _doevalstr( mlp, 15);
	if (_res) _res = _definepattern(mlp, (char *)"xx43[]", (char *)"{}", 13);
	if (_res) _res = _doevalstr( mlp, 16);
	if (_res) _res = _definepattern(mlp, (char *)"get42[]", (char *)"{}", 14);
	if (_res) _res = _doevalstr( mlp, 17);
	if (_res) _res = _definepattern(mlp, (char *)"add[x : _Integer, y : _Integer]", (char *)"{x, y}", 15);
	if (_res) _res = _doevalstr( mlp, 18);
	if (_res) _res = _definepattern(mlp, (char *)"addf[x : _Real, y : _Real]", (char *)"{x, y}", 16);
	if (_res) _res = _doevalstr( mlp, 19);
	if (_res) _res = _definepattern(mlp, (char *)"multiout[x : {___Integer}]", (char *)"{x}", 17);
	if (_res) _res = _doevalstr( mlp, 20);
	if (_res) _res = _definepattern(mlp, (char *)"mainc[]", (char *)"{}", 18);
	if (_res) _res = _doevalstr( mlp, 21);
	if (_res) _res = _definepattern(mlp, (char *)"setPartitions[newPartitionsCount : _Integer]", (char *)"{newPartitionsCount}", 19);
	if (_res) _res = _doevalstr( mlp, 22);
	if (_res) _res = _definepattern(mlp, (char *)"receiveSharedOptimizationData[xI : {___Real}]", (char *)"{xI}", 20);
	if (_res) _res = _doevalstr( mlp, 23);
	if (_res) _res = _definepattern(mlp, (char *)"receiveOptimizationData[partition : _Integer, sparseDerivativeZtoYIndicesI : {___Integer}, xIndicesI : {___Integer}, yIndicesI : {___Integer}]", (char *)"{partition, sparseDerivativeZtoYIndicesI, xIndicesI, yIndicesI}", 21);
	if (_res) _res = _doevalstr( mlp, 24);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledGet[]", (char *)"{}", 22);
	if (_res) _res = _doevalstr( mlp, 25);
	if (_res) _res = _definepattern(mlp, (char *)"xxGet[]", (char *)"{}", 23);
	if (_res) _res = _doevalstr( mlp, 26);
	if (_res) _res = _definepattern(mlp, (char *)"aGet[]", (char *)"{}", 24);
	if (_res) _res = _doevalstr( mlp, 27);
	if (_res) _res = _definepattern(mlp, (char *)"bGet[]", (char *)"{}", 25);
	if (_res) _res = _doevalstr( mlp, 28);
	if (_res) _res = _definepattern(mlp, (char *)"yyGet[]", (char *)"{}", 26);
	if (_res) _res = _doevalstr( mlp, 29);
	if (_res) _res = _definepattern(mlp, (char *)"xGet[]", (char *)"{}", 27);
	if (_res) _res = _doevalstr( mlp, 30);
	if (_res) _res = _definepattern(mlp, (char *)"dprintEnabledSet[dprintEnabled : _Integer]", (char *)"{dprintEnabled}", 28);
	if (_res) _res = _doevalstr( mlp, 31);
	if (_res) _res = _definepattern(mlp, (char *)"xxSet[xx : _Integer]", (char *)"{xx}", 29);
	if (_res) _res = _doevalstr( mlp, 32);
	if (_res) _res = _definepattern(mlp, (char *)"aSet[a : _Real]", (char *)"{a}", 30);
	if (_res) _res = _doevalstr( mlp, 33);
	if (_res) _res = _definepattern(mlp, (char *)"bSet[b : _Real]", (char *)"{b}", 31);
	if (_res) _res = _doevalstr( mlp, 34);
	if (_res) _res = _definepattern(mlp, (char *)"yySet[yy : _Real]", (char *)"{yy}", 32);
	if (_res) _res = _doevalstr( mlp, 35);
	if (_res) _res = _definepattern(mlp, (char *)"xSet[x : {___Real}]", (char *)"{x}", 33);
	if (_res) _res = _doevalstr( mlp, 36);
	if (_res) _res = _doevalstr( mlp, 37);
	if (_res) _res = _doevalstr( mlp, 38);
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
	return _WSDoCallPacket( mlp, _tramps, 34);
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
 
