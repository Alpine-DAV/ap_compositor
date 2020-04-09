#ifndef APCOMP_PAYLOAD_COMPOSITOR_HPP
#define APCOMP_PAYLOAD_COMPOSITOR_HPP

#include <sstream>
#include <apcomp/apcomp_exports.h>
#include <apcomp/payload_image.hpp>

namespace apcomp
{

class APCOMP_API PayloadCompositor
{
public:
    PayloadCompositor();

    void ClearImages();

    void AddImage(PayloadImage &image);

    PayloadImage Composite();
protected:
    std::vector<PayloadImage>  m_images;
};

};

#endif


