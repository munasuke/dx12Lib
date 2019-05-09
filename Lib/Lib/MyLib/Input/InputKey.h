#pragma once

enum class Key
{
	//マウス左
	LButton = 1,
	//マスス右
	RButton = 2,
	//マウス中央
	MButton = 4,
	//バックスペース
	Back = 8,
	//TABキー
	Tab = 9,
	//Enterキー
	Return = 13,
	//Shift
	Shift = 16,
	//Ctrl
	Ctrl = 17,
	//Alt
	Menu = 18,
	//Pause
	Pause = 19,
	//CapsLock
	Capital = 20,
	//カナ
	Hangle = 21,
	//漢字
	Hanja = 25,
	//エスケープ
	Escape = 27,
	//変換
	Convert = 28,
	//無変換
	NonConvert = 29,
	//スペースバー
	Space = 32,
	//PageUp
	Prior = 33,
	//PageDown
	Next = 34,
	//End
	End = 35,
	//Home
	Home = 36,
	//左キー
	Left = 37,
	//上キー
	Up = 38,
	//右キー
	Right = 39,
	//下キー
	Down = 40,
	//PrintScreen
	SnapShot = 44,
	//Insert
	Insert = 45,
	//Delete
	Delete = 46,
	//0
	_0 = 48,
	//1
	_1 = 49,
	//2
	_2 = 50,
	//3
	_3 = 51,
	//4
	_4 = 52,
	//5
	_5 = 53,
	//6
	_6 = 54,
	//7
	_7 = 55,
	//8
	_8 = 56,
	//9
	_9 = 57,
	//A
	A = 65,
	//B
	B = 66,
	//C
	C = 67,
	//D
	D = 68,
	//E
	E = 69,
	//F
	F = 70,
	//G
	G = 71,
	//H
	H = 72,
	//I
	I = 73,
	//J
	J = 74,
	//K
	K = 75,
	//L
	L = 76,
	//M
	M = 77,
	//N
	N = 78,
	//O
	O = 79,
	//P
	P = 80,
	//Q
	Q = 81,
	//R
	R = 82,
	//S
	S = 83,
	//T
	T = 84,
	//U
	U = 85,
	//V
	V = 86,
	//W
	W = 87,
	//X
	X = 88,
	//Y
	Y = 89,
	//ZS
	Z = 90,
	//左WINキー
	LWin = 91,
	//右WINキー
	RWin = 92,
	//アプリケーションキー
	Apps = 93,
	//Num0
	Num0 = 96,
	//Num1
	Num1 = 97,
	//Num2
	Num2 = 98,
	//Num3
	Num3 = 99,
	//Num4
	Num4 = 100,
	//Num5
	Num5 = 101,
	//Num6
	Num6 = 102,
	//Num7
	Num7 = 103,
	//Num8
	Num8 = 104,
	//Num9
	Num9 = 105,
	//Num*
	Multi = 106,
	//Num+
	Add = 107,
	//Num,
	Separator = 108,
	//Num-
	Sub = 109,
	//Num.
	Decimal = 110,
	//Num/
	Divide = 111,
	//F1
	F1 = 112,
	//F2
	F2 = 113,
	//F3
	F3 = 114,
	//F4
	F4 = 115,
	//F5
	F5 = 116,
	//F6
	F6 = 117,
	//F7
	F7 = 118,
	//F8
	F8 = 119,
	//F9
	F9 = 120,
	//F10
	F10 = 121,
	//F11
	F11 = 122,
	//F12
	F12 = 123,
	//F13
	F13 = 124,
	//F14
	F14 = 125,
	//F15
	F15 = 126,
	//F16
	F16 = 127,
	//F17
	F17 = 128,
	//F18
	F18 = 129,
	//F19
	F19 = 130,
	//F20
	F20 = 131,
	//F21
	F21 = 132,
	//F22
	F22 = 133,
	//F23
	F23 = 134,
	//F24
	F24 = 135,
	//NumLock
	NumLock = 144,
	//ScrollLock
	Scroll = 145,
	//左Shift
	LShift = 160,
	//右Shift
	RShift = 161,
	//左Ctrl
	LCtrl = 162,
	//右Ctrl
	RCtrl = 163,
	//左Alt
	LMenu = 164,
	//右Alt
	RMenu = 165,
	//:
	Ome_1 = 186,
	//;
	Ome_Plus = 187,
	//,
	Ome_Comma = 188,
	//-
	Ome_Minus = 189,
	//.
	Ome_Period = 190,
	///
	Ome_2 = 191,
	//@
	Ome_3 = 192,
	//[
	Ome_4 = 219,
	//¥
	Ome_5 = 220,
	//]
	Ome_6 = 221,
	//^
	Ome_7 = 222,
	//_
	Ome_8 = 223,
	//_
	Ome_102 = 226,
};