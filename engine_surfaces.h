#pragma once

struct TextureParams
{
	 void set_color_params(unsigned int mask_r, unsigned int mask_g, unsigned int mask_b, unsigned int mask_a, int bpp);
  uint32_t field_0;
  uint32_t bpp1;
  uint32_t bytesPerPixel;
  uint32_t bitspp_g;
  uint32_t bitspp_b;
  uint32_t bitspp_a;
  uint32_t bitspp_r;
  uint32_t mask_g1;
  uint32_t mask_b1;
  uint32_t mask_a1;
  uint32_t mask_r1;
  uint8_t field_2C;
  uint32_t field_2D;
  uint32_t field_31;
  uint32_t field_35;
  uint32_t field_39;
  uint32_t bpp3;
  uint32_t field_41;
  uint32_t field_45;
  uint32_t field_49;
  uint32_t field_4D;
  uint32_t bpp4;
  uint32_t mask_g2;
  uint32_t mask_b2;
  uint32_t mask_a2;
  uint32_t mask_r2;
};
static_assert(sizeof(TextureParams) == 104, "");

struct CEngineSurfaceBase
{
	CEngineSurfaceBase(uint32_t w, uint32_t h);
	virtual ~CEngineSurfaceBase();
	virtual void fill(unsigned short val);
	virtual bool put_image(CEngineSurfaceBase *dst, int pos_x, int pos_y)
	{
		return false;
	}
	virtual bool get_image(CEngineSurfaceBase *src, int pos_x, int pos_y)
	{
		return false;
	}
	virtual int func_10() = 0;
	virtual bool out_supported() = 0;
	virtual uint8_t* get_out_buffer() { return nullptr; }
	virtual void func_1C(uint8_t* buf) {}
	virtual uint8_t* rawData(uint32_t *len) { return nullptr; }

	uint32_t width;
	uint32_t height;
	uint32_t line_len;
	TextureParams* graph_params;
};

struct CEngineCompressedSurface : CEngineSurfaceBase
{
	CEngineCompressedSurface(uint32_t w, uint32_t h, uint32_t len);
	~CEngineCompressedSurface() override;
	bool put_image(CEngineSurfaceBase *dst, int pos_x, int pos_y) override;
	bool get_image(CEngineSurfaceBase *src, int pos_x, int pos_y) override;
	int func_10() override
	{
		return 2;
	}

	bool out_supported() override
	{
		return false;
	}

	uint8_t* rawData(uint32_t* len) override;

	uint8_t* data;
	uint32_t datalen;
};

struct CEngineDDSurface : CEngineSurfaceBase
{
	CEngineDDSurface(uint32_t w, uint32_t h, uint32_t field_20, void* field_24, uint32_t field_28, uint32_t field_32)
		: CEngineSurfaceBase(w, h),
		  field_20(field_20),
		  field_24(field_24),
		  field_28(field_28),
		  field_32(field_32)
	{
	}

	~CEngineDDSurface() override
	{
		if (field_32)
			return;

//		if (field_20 & 1)
//			(*(void(__stdcall **)(int))(*(_DWORD *)this->field_28 + 8))(this->field_28);
//		result = (*(int(__stdcall **)(int))(*(_DWORD *)v1->field_24 + 8))(v1->field_24);

	}
	void fill(unsigned short val) override
	{}

	bool put_image(CEngineSurfaceBase* dst, int pos_x, int pos_y) override
	{
		return false;
	}

	bool get_image(CEngineSurfaceBase* src, int pos_x, int pos_y) override;

	int func_10() override
	{
		return 1;
	}

	bool out_supported() override
	{
		return true;
	}

	uint8_t* get_out_buffer() override;

	void func_1C(uint8_t* buf) override;

	uint8_t* rawData(uint32_t* /*len*/) override
	{
		return nullptr;
	}

	uint32_t field_20;
	void*    field_24;
	uint32_t field_28;
	uint32_t field_32;
};

/******************************************************************************/
extern TextureParams *graphics_params;
/******************************************************************************/
