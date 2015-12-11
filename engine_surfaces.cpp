#include "stdafx.h"
#include "engine_surfaces.h"

#include "hookfunction.h"

#include <cstdlib>
#include <iostream>

uint32_t const unkn_array01[] = {
	0x2000, 0x1712, 0x187E, 0x1B37, 0x2000, 0x28BA, 0x3B21, 0x73FC,
	0x1712, 0x10A2, 0x11A8, 0x139F, 0x1712, 0x1D5D, 0x2AA1, 0x539F,
	0x187E, 0x11A8, 0x12BF, 0x14D4, 0x187E, 0x1F2C, 0x2D41, 0x58C5,
	0x1B37, 0x139F, 0x14D4, 0x1725, 0x1B37, 0x22A3, 0x3249, 0x62A3,
	0x2000, 0x1712, 0x187E, 0x1B37, 0x2000, 0x28BA, 0x3B21, 0x73FC,
	0x28BA, 0x1D5D, 0x1F2C, 0x22A3, 0x28BA, 0x33D6, 0x4B42, 0x939F,
	0x3B21, 0x2AA1, 0x2D41, 0x3249, 0x3B21, 0x4B42, 0x6D41,0x0D650,
	0x73FC, 0x539F, 0x58C5, 0x62A3, 0x73FC, 0x939F,0x0D650,0x1A463,
};

TextureParams *graphics_params = new TextureParams();
uint8_t static_buffer[65536];

/***************************** Low level methods ******************************/

void sub_5B2450(unsigned int mask_g, unsigned int mask_b, unsigned int mask_a, unsigned int mask_r)
{
/*
	char v4; // zf@1
	signed int v5; // esi@2
	signed int v6; // ecx@4
	signed int v7; // esi@5
	int v8; // edx@11
	signed int v9; // ecx@11
	int v10; // edx@15
	signed int v11; // ecx@15
	int v12; // edx@19
	signed int v13; // ecx@19
	signed int v14; // ecx@23
	int v15; // edi@23
	int v16; // edx@27
	signed int v17; // ecx@27
	signed int v18; // ecx@31
	int v19; // esi@31
	signed int v20; // eax@34
	int v21; // edx@34
	int v22; // eax@37
	signed int v23; // ecx@37
	int v24; // [sp+Ch] [bp-10h]@6
	int v25; // [sp+18h] [bp-4h]@19
	int v26; // [sp+14h] [bp-8h]@23
	int v27; // [sp+10h] [bp-Ch]@27

	v4 = dword_7982E4 == 0;
	if (!dword_7982E4)
	{
		v5 = 0;
		do
			byte_7981A8[v5++] = rand();
		while (v5 < 259);
		v6 = 0;
		do
		{
			v7 = 8;
			do
			{
				v24 = *(unsigned __int32 *)((char *)&unkn_array01[0] + v6);
				*(int *)((char *)&dword_7982F0[0] + v6) = ((unsigned __int64)(v24 << 19) >> 32 << 16)
					+ __MKCSHR__(v24 << 19, 16)
					+ ((unsigned int)(v24 << 19) >> 16);
				v6 += 4;
				--v7;
			} while (v7);
		} while (v6 < 256);
		v4 = dword_7982E4 == 0;
	}
	if (v4 || *(_QWORD *)&dword_7982D8 != *(_QWORD *)&mask_g)
	{
		v8 = 0;
		dword_7982D0 = mask_r;
		v9 = 0;
		do
		{
			if (mask_r & (1 << v9))
				++v8;
			++v9;
		} while (v9 < 32);
		v24 = v8;
		dword_7982B0 = v8;
		v10 = 0;
		v11 = 0;
		do
		{
			if (mask_g & (1 << v11))
				++v10;
			++v11;
		} while (v11 < 32);
		v25 = v10;
		dword_7982B4 = v10;
		v12 = 0;
		v13 = 0;
		do
		{
			if (mask_b & (1 << v13))
				++v12;
			++v13;
		} while (v13 < 32);
		v15 = 0;
		v26 = v12;
		dword_7982B8 = v12;
		v14 = 0;
		do
		{
			if (mask_a & (1 << v14))
				++v15;
			++v14;
		} while (v14 < 32);
		v16 = 0;
		dword_7982BC = v15;
		v17 = mask_r;
		v27 = 0;
		if (mask_r)
		{
			if (!(mask_r & 1))
			{
				do
				{
					v17 >>= 1;
					++v16;
				} while (!(v17 & 1));
				v27 = v16;
			}
		}
		v18 = mask_g;
		v19 = 0;
		dword_7982C0 = v16;
		if (mask_g)
		{
			if (!(mask_g & 1))
			{
				do
				{
					v18 >>= 1;
					++v19;
				} while (!(v18 & 1));
			}
		}
		v20 = mask_b;
		v21 = 0;
		dword_7982C4 = v19;
		if (mask_b)
		{
			if (!(mask_b & 1))
			{
				do
				{
					v20 >>= 1;
					++v21;
				} while (!(v20 & 1));
			}
		}
		v22 = 0;
		dword_7982C8 = v21;
		v23 = mask_a;
		if (mask_a)
		{
			if (!(mask_a & 1))
			{
				do
				{
					v23 >>= 1;
					++v22;
				} while (!(v23 & 1));
			}
		}
		dword_7AF0B0 = v19;
		dword_7AF0B4 = v21;
		dword_7982D4 = (-((unsigned int)(v25 + v15 + v26) > 0x10) & 0x10) + 16;
		dword_7AF090 = mask_r;
		dword_7982CC = v22;
		dword_7AF0B8 = v22;
		dword_7AF094 = (0xFF000000u << v25) & 0xFF000000;
		dword_7AF088 = 8 - v26;
		dword_7AF08C = 8 - v15;
		dword_7AF098 = (0xFF000000u << v26) & 0xFF000000;
		dword_7AF0BC = v27;
		dword_7AF080 = 8 - v24;
		dword_7AF09C = (0xFF000000u << v15) & 0xFF000000;
		dword_7AF084 = 8 - v25;
		dword_7AF0A0 = 255 >> (8 - v24);
		dword_7AF0A4 = 255 >> (8 - v25);
		dword_7AF0AC = 255 >> (8 - v26);
		dword_7AF0A8 = 255 >> (8 - v15);
		sub_5B21E0();
	}
	dword_7982E4 = 1;
*/
}

/*************************** TextureParams methods ***************************/

void TextureParams::set_color_params(unsigned int mask_r, unsigned int mask_g, unsigned int mask_b, unsigned int mask_a, int bpp)
{
	long i;
	uint32_t k;
	mask_r2 = mask_r;
	mask_r1 = mask_r;
	field_0 = 1;
	mask_g2 = mask_g;
	mask_b2 = mask_b;
	mask_a2 = mask_a;
	bpp4 = bpp;
	mask_g1 = mask_g;
	mask_b1 = mask_b;
	mask_a1 = mask_a;
	bpp1 = bpp;
	bytesPerPixel = bpp / 8;
	bpp3 = bpp;
	field_2D = mask_g;
	field_31 = mask_b;
	field_35 = mask_a;
	field_39 = mask_r;
	field_41 = 0;
	// Coputing bits count for a colour
	k = 0;
	for (i = 0; i < 31; i++)
	{
		if (mask_g < (1 << i))
			break;
		if ((mask_g & (1 << i)) != 0)
			k++;
	}
	bitspp_g = k;
	// Coputing bits count for a colour
	k = 0;
	for (i = 0; i < 31; i++)
	{
		if (mask_b < (1 << i))
			break;
		if ((mask_b & (1 << i)) != 0)
			k++;
	}
	bitspp_b = k;
	// Coputing bits count for a colour
	k = 0;
	for (i = 0; i < 31; i++)
	{
		if (mask_a < (1 << i))
			break;
		if ((mask_a & (1 << i)) != 0)
			k++;
	}
	bitspp_a = k;
	// Coputing bits count for a colour
	k = 0;
	for (i = 0; i < 31; i++)
	{
		if (mask_r < (1 << i))
			break;
		if ((mask_r & (1 << i)) != 0)
			k++;
	}
	bitspp_r = k;
	field_2C = 0;
}

/************************ CEngineSurfaceBase methods ************************/

CEngineSurfaceBase::CEngineSurfaceBase(uint32_t w, uint32_t h)
{
	width = w;
	height = h;
	graph_params = graphics_params;
	line_len = w * graphics_params->bytesPerPixel;
}

CEngineSurfaceBase::~CEngineSurfaceBase()
{}

void CEngineSurfaceBase::fill(unsigned short val)
{
	uint32_t i, k;
	unsigned short *ptr;
	uint8_t* buf = get_out_buffer();
	uint8_t* ln_ptr = buf;
	for (i = 0; i < height; i++)
	{
		ptr = (unsigned short *)ln_ptr;
		for (k = 0; k < width; k++)
		{
			*ptr = val;
			ptr++;
		}
		ln_ptr += 2 * line_len / 2;
	}
	func_1C(buf);
}

/********************* CEngineCompressedSurface methods *********************/

CEngineCompressedSurface::CEngineCompressedSurface(uint32_t w, uint32_t h, uint32_t len)
: CEngineSurfaceBase(w, h)
{
	data = nullptr;
	if (len > 0)
		data = (uint8_t*)malloc(len);
	datalen = len;
}

CEngineCompressedSurface::~CEngineCompressedSurface()
{
	free(data);
}

bool CEngineCompressedSurface::put_image(CEngineSurfaceBase *dst, int pos_x, int pos_y)
{
	uint8_t* obuf;
	uint8_t* ptr;
	TextureParams *gr_par;

	if (!dst->out_supported())
		return false;
	obuf = dst->get_out_buffer();
	gr_par = dst->graph_params;
	ptr = obuf + dst->line_len * pos_y + pos_x * gr_par->bytesPerPixel;
	sub_5B2450(gr_par->mask_g1, gr_par->mask_b1, gr_par->mask_a1, gr_par->mask_r1);
	//  sub_5B26F0(data, ptr, dst->line_len, width, height);
	dst->func_1C(obuf);
	return true;
}

uint32_t texture_compress(uint8_t* buf1, uint8_t* buf2, uint32_t w, uint32_t h, uint32_t line_len, uint32_t x, uint32_t y)
{
	//TODO - at .text:005A4730
	return 0;
}

bool CEngineCompressedSurface::get_image(CEngineSurfaceBase *src, int pos_x, int pos_y)
{
	uint8_t* obuf;
	if ((pos_x != 0) || (pos_y != 0)) // Position is not supported
		return false;
	if (!src->out_supported())
		return false;
	free(data);
	obuf = src->get_out_buffer();
	datalen = texture_compress(obuf, static_buffer, width, height, src->line_len, pos_x, 5);
	data = (uint8_t*)malloc(datalen);
	memcpy(data, static_buffer, datalen);
	src->func_1C(obuf);
	return true;
}

uint8_t* CEngineCompressedSurface::rawData(uint32_t *len)
{
	*len = datalen;
	return data;
}

/********************* OTHERS *********************/

/*
CEngineSurface *__thiscall read_texture_file(unkstruc6 *this, char *fname)
{
uint32_t idx;
uint32_t width, height, line_len;
CEngineSurfaceBase *esurf;
void *buf;
uint32_t buf_len;
idx = get_slot_for_texture_file(&field_434, fname);
if (idx < 0)
return nullptr;
fseek(texture_file, field_434.field_410[idx].field_0, 0);
width = -1;
height = -1;
line_len = -1;
read_from_file(&width, 4, 1, texture_file);
read_from_file(&height, 4, 1, texture_file);
read_from_file(&line_len, 4, 1, texture_file);
esurf = new CEngineCompressedSurface(width, height, line_len);
buf_len = 0;
buf = esurf->rawData(&buf_len);
read_from_file(buf, buf_len, 1, texture_file);
return esurf;
}
*/

namespace
{
struct Register
{
	Register()
	{
	}

} reg;
}