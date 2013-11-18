/***
  This file is part of PulseAudio.

  PulseAudio is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published
  by the Free Software Foundation; either version 2.1 of the License,
  or (at your option) any later version.

  PulseAudio is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with PulseAudio; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA.
***/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "core-format.h"

#include <pulse/def.h>

#include <pulsecore/macro.h>

int pa_format_info_to_sample_spec_fake(pa_format_info *f, pa_sample_spec *ss, pa_channel_map *map) {
    int rate;

    pa_assert(f);
    pa_assert(ss);

    /* Note: When we add support for non-IEC61937 encapsulated compressed
     * formats, this function should return a non-zero values for these. */

    ss->format = PA_SAMPLE_S16LE;
    ss->channels = 2;

    if (map)
        pa_channel_map_init_stereo(map);

    pa_return_val_if_fail(pa_format_info_get_prop_int(f, PA_PROP_FORMAT_RATE, &rate) == 0, -PA_ERR_INVALID);
    ss->rate = (uint32_t) rate;

    if (f->encoding == PA_ENCODING_EAC3_IEC61937)
        ss->rate *= 4;

    return 0;
}
