#include "stdafx.h"
#include "hijacklib.h"

#include "hookfunction.h"

#include <cstddef>
#include <cstdint>
#include <algorithm>

HIJACKLIB_API void dummyfn()
{
}

struct UnknownZoomRel
{
	char dummy[3408];
	int32_t field_3408_minZoomLevel;
	int field_3412_maxZoomLevel;
	char dd[40];
	int field_3456_curZoomLevel;
	char de[14];
	unsigned char field_3474;
	char df[69];
	int field_3544;

	void zoomRel_4496E0(int a2)
	{
		if ((this->field_3474 & 8) || this->field_3544)
			return;

		// HACK
		static int i = 0;
		if (!i++)
			this->field_3412_maxZoomLevel *= 3;

		int minZoom = this->field_3408_minZoomLevel;
		int maxZoom = this->field_3412_maxZoomLevel - 1;
		int t = std::max(field_3456_curZoomLevel + a2, minZoom);
		field_3456_curZoomLevel = std::min(t, maxZoom);
	}
};
static_assert(offsetof(UnknownZoomRel, field_3544) == 3544, "");

namespace
{
struct Register
{
	Register()
	{
		replaceFn(0x4496E0, memFn2ptr(&UnknownZoomRel::zoomRel_4496E0));
	}

} reg;
}