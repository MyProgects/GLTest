#pragma once

#include "Savepng.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
/*
	�� C ����ʵ���˵ݹ���ݣ�recursive backtracker���㷨

	����

	�����Թ�����ָ���κ�һ�㵽��һ�㶼���ҽ���һ��·����Ҳ����û��ѭ����
	������ݹ�����㷨����ƫ�ģ�biased���Թ������㷨��ʱ��Ϳռ临�Ӷȶ���O(n)
*/


#define C(x, y) (img + ((y) * 6 + 3) * a + (x) * 6 + 3)
#define W(o) c = C(x, y) + o; c[0] = 255; c[1] = c[2] = d % 512 < 256 ? d % 512 : 511 - d % 512
#define V(x, y) (x) >= 0 && (x) < w && (y) >= 0 && (y) < h && !*C(x, y) && m(x, y)

static const int w = 256, h = 256, a = w * 2 + 1, b = h * 2 + 1;
static unsigned char img[a * b * 3], *c = img;

//static const int w = 128, h = 128, a = w * 2 + 1, b = h * 2 + 1;

int m(int x, int y) {
	float u = 2.4f * x / w - 1.2f, v = -2.4f * y / h + 1.3f, w = u * u + v * v - 1;
	return w * w * w - u * u * v * v * v < 0;
}

void f(int x, int y, int d) {
	W(0);
	//int j = 8;
	for (int j = rand() % 24 * 4, i = 0; i < 4; i++)
		switch ("ABCDABDCACBDACDBADBCADCBBACDBADCBCADBCDABDACBDCACABDCADBCBADCBDACDABCDBADABCDACBDBACDBCADCABDCBA"[i + j]) {
		case 'A': if (V(x - 1, y)) { W(-3); f(x - 1, y, d + 1); } break;
		case 'B': if (V(x + 1, y)) { W(3); f(x + 1, y, d + 1); } break;
		case 'C': if (V(x, y - 1)) { W(a * -3); f(x, y - 1, d + 1); } break;
		case 'D': if (V(x, y + 1)) { W(a * 3); f(x, y + 1, d + 1); } break;
		}
}

/*
int main() {
	f(w / 2, h / 2, 0);
	svpng(fopen("heart.png", "w"), a, b, img, 0);
}*/

void test_rgb(void) {
	unsigned char rgb[256 * 256 * 3], *p = rgb;
	unsigned x, y;
	FILE *fp = fopen("rgb.png", "wb");
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			*p++ = (unsigned char)x;    /* R */
			*p++ = (unsigned char)y;    /* G */
			*p++ = 128;                 /* B */
		}
	svpng(fp, 256, 256, rgb, 0);
	fclose(fp);
}