// See License.txt

#include "Image.hpp"
#include <apcomp/utils/PNGEncoder.hpp>

namespace apcomp
{

void Image::Save(std::string name)
{
    PNGEncoder encoder;
    encoder.Encode(&m_pixels[0],
        m_bounds.m_max_x - m_bounds.m_min_x + 1,
        m_bounds.m_max_y - m_bounds.m_min_y + 1);
    encoder.Save(name);
}

} // namespace apcomp
