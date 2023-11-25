// -----------------------------------------------------------
// 
// color palette.
// 
// Copyright 2023 teacha1025
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// 
// -----------------------------------------------------------

#pragma once

#include "color.h"
#include "def.h"

namespace suika {
	/// <summary>
	/// 様々な色をまとめた定数群
	/// </summary>
	/// <details>
	/// 色見本は[こちら](https://www.colordic.org/)を参考にしてください
	/// </details>
	namespace palette {
		/// "aliceblue"
		define aliceblue = color(240, 248, 255);

		/// "antiquewhite"
		define antiquewhite = color(250, 235, 215);

		/// "aqua"
		define aqua = color(0, 255, 255);

		/// "aquamarine"
		define aquamarine = color(127, 255, 212);

		/// "azure"
		define azure = color(240, 255, 255);

		/// "beige"
		define beige = color(245, 245, 220);

		/// "bisque"
		define bisque = color(255, 228, 196);

		/// "black"
		define black = color(0, 0, 0);

		/// "blanchedalmond"
		define blanchedalmond = color(255, 235, 205);

		/// "blue"
		define blue = color(0, 0, 255);

		/// "blueviolet"
		define blueviolet = color(138, 43, 226);

		/// "brown"
		define brown = color(165, 42, 42);

		/// "burlywood"
		define burlywood = color(222, 184, 135);

		/// "cadetblue"
		define cadetblue = color(95, 158, 160);

		/// "chartreuse"
		define chartreuse = color(127, 255, 0);

		/// "chocolate"
		define chocolate = color(210, 105, 30);

		/// "coral"
		define coral = color(255, 127, 80);

		/// "cornflowerblue"
		define cornflowerblue = color(100, 149, 237);

		/// "cornsilk"
		define cornsilk = color(255, 248, 220);

		/// "crimson"
		define crimson = color(220, 20, 60);

		/// "cyan"
		define cyan = color(0, 255, 255);

		/// "darkblue"
		define darkblue = color(0, 0, 139);

		/// "darkcyan"
		define darkcyan = color(0, 139, 139);

		/// "darkgoldenrod"
		define darkgoldenrod = color(184, 134, 11);

		/// "darkgray"
		define darkgray = color(169, 169, 169);

		/// "darkgreen"
		define darkgreen = color(0, 100, 0);

		/// "darkkhaki"
		define darkkhaki = color(189, 183, 107);

		/// "darkmagenta"
		define darkmagenta = color(139, 0, 139);

		/// "darkolivegreen"
		define darkolivegreen = color(85, 107, 47);

		/// "darkorange"
		define darkorange = color(255, 140, 0);

		/// "darkorchid"
		define darkorchid = color(153, 50, 204);

		/// "darkred"
		define darkred = color(139, 0, 0);

		/// "darksalmon"
		define darksalmon = color(233, 150, 122);

		/// "darkseagreen"
		define darkseagreen = color(143, 188, 143);

		/// "darkslateblue"
		define darkslateblue = color(72, 61, 139);

		/// "darkslategray"
		define darkslategray = color(47, 79, 79);

		/// "darkturquoise"
		define darkturquoise = color(0, 206, 209);

		/// "darkviolet"
		define darkviolet = color(148, 0, 211);

		/// "deeppink"
		define deeppink = color(255, 20, 147);

		/// "deepskyblue"
		define deepskyblue = color(0, 191, 255);

		/// "dimgray"
		define dimgray = color(105, 105, 105);

		/// "dodgerblue"
		define dodgerblue = color(30, 144, 255);

		/// "firebrick"
		define firebrick = color(178, 34, 34);

		/// "floralwhite"
		define floralwhite = color(255, 250, 240);

		/// "forestgreen"
		define forestgreen = color(34, 139, 34);

		/// "fuchsia"
		define fuchsia = color(255, 0, 255);

		/// "gainsboro"
		define gainsboro = color(220, 220, 220);

		/// "ghostwhite"
		define ghostwhite = color(248, 248, 255);

		/// "gold"
		define gold = color(255, 215, 0);

		/// "goldenrod"
		define goldenrod = color(218, 165, 32);

		/// "gray"
		define gray = color(128, 128, 128);

		/// "green"
		define green = color(0, 128, 0);

		/// "greenyellow"
		define greenyellow = color(173, 255, 47);

		/// "honeydew"
		define honeydew = color(240, 255, 240);

		/// "hotpink"
		define hotpink = color(255, 105, 180);

		/// "indianred"
		define indianred = color(205, 92, 92);

		/// "indigo"
		define indigo = color(75, 0, 130);

		/// "ivory"
		define ivory = color(255, 255, 240);

		/// "khaki"
		define khaki = color(240, 230, 140);

		/// "lavender"
		define lavender = color(230, 230, 250);

		/// "lavenderblush"
		define lavenderblush = color(255, 240, 245);

		/// "lawngreen"
		define lawngreen = color(124, 252, 0);

		/// "lightyellow"
		define lightyellow = color(255, 255, 224);

		/// "lemonchiffon"
		define lemonchiffon = color(255, 250, 205);

		/// "lightblue"
		define lightblue = color(173, 216, 230);

		/// "lightcoral"
		define lightcoral = color(240, 128, 128);

		/// "lightcyan"
		define lightcyan = color(224, 255, 255);

		/// "lightgoldenrodyellow"
		define lightgoldenrodyellow = color(250, 250, 210);

		/// "lightgreen"
		define lightgreen = color(144, 238, 144);

		/// "lightgray"
		define lightgrey = color(211, 211, 211);

		/// "lightpink"
		define lightpink = color(255, 182, 193);

		/// "lightsalmon"
		define lightsalmon = color(255, 160, 122);

		/// "lightseagreen"
		define lightseagreen = color(32, 178, 170);

		/// "lightskyblue"
		define lightskyblue = color(135, 206, 250);

		/// "lightslategray"
		define lightslategray = color(119, 136, 153);

		/// "lightsteelblue"
		define lightsteelblue = color(176, 196, 222);

		/// "lime"
		define lime = color(0, 255, 0);

		/// "limegreen"
		define limegreen = color(50, 205, 50);

		/// "linen"
		define linen = color(250, 240, 230);

		/// "magenta"
		define magenta = color(255, 0, 255);

		/// "maroon"
		define maroon = color(128, 0, 0);

		/// "mediumaquamarine"
		define mediumaquamarine = color(102, 205, 170);

		/// "mediumblue"
		define mediumblue = color(0, 0, 205);

		/// "mediumorchid"
		define mediumorchid = color(186, 85, 211);

		/// "mediumpurple"
		define mediumpurple = color(147, 112, 219);

		/// "mediumseagreen"
		define mediumseagreen = color(60, 179, 113);

		/// "mediumslateblue"
		define mediumslateblue = color(123, 104, 238);

		/// "mediumspringgreen"
		define mediumspringgreen = color(0, 250, 154);

		/// "mediumturquoise"
		define mediumturquoise = color(72, 209, 204);

		/// "mediumvioletred"
		define mediumvioletred = color(199, 21, 133);

		/// "midnightblue"
		define midnightblue = color(25, 25, 112);

		/// "mintcream"
		define mintcream = color(245, 255, 250);

		/// "mistyrose"
		define mistyrose = color(255, 228, 225);

		/// "moccasin"
		define moccasin = color(255, 228, 181);

		/// "navajowhite"
		define navajowhite = color(255, 222, 173);

		/// "navy"
		define navy = color(0, 0, 128);

		/// "oldlace"
		define oldlace = color(253, 245, 230);

		/// "olive"
		define olive = color(128, 128, 0);

		/// "olivedrab"
		define olivedrab = color(107, 142, 35);

		/// "orange"
		define orange = color(255, 127, 0);

		/// "orangered"
		define orangered = color(255, 69, 0);

		/// "orchid"
		define orchid = color(218, 112, 214);

		/// "palegoldenrod"
		define palegoldenrod = color(238, 232, 170);

		/// "palegreen"
		define palegreen = color(152, 251, 152);

		/// "paleturquoise"
		define paleturquoise = color(175, 238, 238);

		/// "palevioletred"
		define palevioletred = color(219, 112, 147);

		/// "papayawhip"
		define papayawhip = color(255, 239, 213);

		/// "peachpuff"
		define peachpuff = color(255, 218, 185);

		/// "peru"
		define peru = color(205, 133, 63);

		/// "pink"
		define pink = color(255, 192, 203);

		/// "plum"
		define plum = color(221, 160, 221);

		/// "powderblue"
		define powderblue = color(176, 224, 230);

		/// "purple"
		define purple = color(128, 0, 128);

		/// "red"
		define red = color(255, 0, 0);

		/// "rosybrown"
		define rosybrown = color(188, 143, 143);

		/// "royalblue"
		define royalblue = color(65, 105, 225);

		/// "saddlebrown"
		define saddlebrown = color(139, 69, 19);

		/// "salmon"
		define salmon = color(250, 128, 114);

		/// "sandybrown"
		define sandybrown = color(244, 164, 96);

		/// "seagreen"
		define seagreen = color(46, 139, 87);

		/// "seashell"
		define seashell = color(255, 245, 238);

		/// "sienna"
		define sienna = color(160, 82, 45);

		/// "silver"
		define silver = color(192, 192, 192);

		/// "skyblue"
		define skyblue = color(135, 206, 235);

		/// "slateblue"
		define slateblue = color(106, 90, 205);

		/// "slategray"
		define slategray = color(112, 128, 144);

		/// "snow"
		define snow = color(255, 250, 250);

		/// "springgreen"
		define springgreen = color(0, 255, 127);

		/// "steelblue"
		define steelblue = color(70, 130, 180);

		/// "tan"
		define tan = color(210, 180, 140);

		/// "teal"
		define teal = color(0, 128, 128);

		/// "thistle"
		define thistle = color(216, 191, 216);

		/// "tomato"
		define tomato = color(255, 99, 71);

		/// "turquoise"
		define turquoise = color(64, 224, 208);

		/// "violet"
		define violet = color(238, 130, 238);

		/// "wheat"
		define wheat = color(245, 222, 179);

		/// "white"
		define white = color(255, 255, 255);

		/// "whitesmoke"
		define whitesmoke = color(245, 245, 245);

		/// "yellow"
		define yellow = color(255, 255, 0);

		/// "yellowgreen"
		define yellowgreen = color(154, 205, 50);
	}
}