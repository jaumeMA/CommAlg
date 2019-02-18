
namespace yame
{
namespace math
{

template<int P>
Zp<P> operator^(const Zp<P>& i_lhs, const Zp<P>& i_rhs)
{
    return Zp<P>(std::pow(i_lhs.get_raw(),i_rhs.get_raw()));
}

}
}
