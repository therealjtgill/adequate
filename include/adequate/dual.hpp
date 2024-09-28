#ifndef DUAL_HEADER
#define DUAL_HEADER

#include <type_traits>

template <typename F>
struct dual
{
   static_assert(
      std::is_floating_point<F>::value,
      "Underlying dual type must be floating point"
   );

   F base[2];

   dual(void)
      : base{F{0}, F{0}}
   { }

   dual(const dual & that)
      : base{that.base[0], that.base[1]}
   { }

   dual & operator=(const dual & that)
   {
      if (this == &that)
      {
         return *this;
      }

      base[0] = that.base[0];
      base[1] = that.base[1];
   }

   F & operator[](int i)
   {
      return base[i];
   }

   const F & operator[](int i) const
   {
      return base[i];
   }

   dual operator+(F val) const
   {
      return dual{base[0] + val, base[1] + val};
   }

   dual operator-(F val) const
   {
      return dual{base[0] - val, base[1] - val};
   }

   dual operator*(F val) const
   {
      return dual{base[0] * val, base[1] * val};
   }

   dual operator/(F val) const
   {
      return dual{base[0] / val, base[1] / val};
   }

   dual & operator +=(F val)
   {
      base[0] += val;
      base[1] += val;
      return *this;
   }

   dual & operator -=(F val)
   {
      base[0] -= val;
      base[1] -= val;
      return *this;
   }

   dual & operator *=(F val)
   {
      base[0] *= val;
      base[1] *= val;
      return *this;
   }

   dual & operator /=(F val)
   {
      base[0] /= val;
      base[1] /= val;
      return *this;
   }

   dual operator+(const dual & that) const
   {
      return dual{base[0] + that.base[0], base[1] + that.base[1]};
   }

   dual operator-(const dual & that) const
   {
      return dual{base[0] - that.base[0], base[1] - that.base[1]};
   }

   dual operator*(const dual & that) const
   {
      return dual{
         base[0] * that.base[0], base[1] * that.base[0] + base[0] * that.base[1]
      };
   }

   dual operator/(const dual & that) const
   {
      return dual{
         base[0] / that.base[0],
         (base[1] * that.base[0] - base[0] * that.base[1]) / (that.base[0] * that.base[0])
      };
   }

   dual & operator+=(const dual & that)
   {
      base[0] += that.base[0];
      base[1] += that.base[1];
      return *this;
   }

   dual & operator-=(const dual & that)
   {
      base[0] -= that.base[0];
      base[1] -= that.base[1];
      return *this;
   }

   dual & operator*=(const dual & that)
   {
      base[0] *= that.base[0],
      base[1] = base[1] * that.base[0] + base[0] * that.base[1]
      return *this;
   }

   dual & operator/=(const dual & that)
   {
      base[0] = base[0] / that.base[0];
      base[1] = (base[1] * that.base[0] - base[0] * that.base[1]) / (that.base[0] * that.base[0]);
      return *this;
   }
};

#endif
