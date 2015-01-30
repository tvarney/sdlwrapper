
#ifndef SDLWRAP_COLOR_HPP
#define SDLWRAP_COLOR_HPP

#include <limits>
#include <type_traits>

namespace sdl {
    // If you want to use something other than a built-in (for whatever reason)
    // it is necessary to create a ColorTypeTraits specialization for that
    // type, otherwise (min()==max()==0) and the color will be stuck at black.
    // This should work for both integral and floating point scalars.
    template <typename scalar>
    struct ColorTypeTraits {
        static constexpr scalar max() {
            return (std::is_integral<scalar>::value ?
                    std::numeric_limits<scalar>::max() :
                    scalar(1));
        }
        static constexpr scalar min() {
            return (std::is_signed<scalar>::value ?
                    scalar(0) :
                    std::numeric_limits<scalar>::min());
        }
        template <typename other>
        static constexpr scalar convert(const other &v) {
            return (std::is_integral<scalar>::value ?
                    /* This is an integral type */
                    ((ColorTypeTraits<other>::max() > max() ?
                      /* Converting to a wider type (e.g. 8->16) */
                      v * (ColorTypeTraits<other>::max() / max()) :
                      /* Converting to a narrower type (e.g. 16 -> 8) */
                      v * (max() / ColorTypeTraits<other>::max()))) :
                    /* This is a floating point type */
                    (std::is_integral<other>::value ?
                     /* The other isn't a floating point, so multiply it by
                        the inverse of it's max as this type */
                     v*(1/scalar(ColorTypeTraits<other>::max())) :
                     /* Both are floating point, just let hardware cast it */
                     scalar(v)));
        }
        static constexpr scalar truncate(const scalar &v) {
            return (v > max() ? max() : v);
        }
    };
    
    template <typename scalar>
    struct Color {
        Color() :
            r(ColorTypeTraits<scalar>::min()),
            g(ColorTypeTraits<scalar>::min()),
            b(ColorTypeTraits<scalar>::min()),
            a(ColorTypeTraits<scalar>::max())
        { }
        Color(const scalar &r, const scalar &g, const scalar &b,
              const scalar &a = ColorTypeTraits<scalar>::max()) :
            r(r), g(g), b(b), a(a)
        { }
        Color(const Color<scalar> &source) :
            r(source.r), g(source.g), b(source.b), a(source.a)
        { }
        template <typename other>
        Color(const Color<other> &source) :
            r(ColorTypeTraits<scalar>::convert(source.r)),
            g(ColorTypeTraits<scalar>::convert(source.g)),
            b(ColorTypeTraits<scalar>::convert(source.b)),
            a(ColorTypeTraits<scalar>::convert(source.a))
        { }
        ~Color() { }
        
        // This is only really useful if the type is a floating point, which
        // can have values over the maximum defined by the ColorTypeTraits.
        void truncate() {
            r = ColorTypeTraits<scalar>::truncate(r);
            g = ColorTypeTraits<scalar>::truncate(g);
            b = ColorTypeTraits<scalar>::truncate(b);
            a = ColorTypeTraits<scalar>::truncate(a);
        }
        
        scalar r, g, b, a;
    };
}

#endif
