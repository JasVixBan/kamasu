#ifndef RESOPHONIC_KAMASU_BOOST_PROTO_TAGS_FWD_HPP_INCLUDED
#define RESOPHONIC_KAMASU_BOOST_PROTO_TAGS_FWD_HPP_INCLUDED

namespace boost
{
  namespace proto
  {
    namespace tag
    {
        struct terminal{ };
        struct unary_plus{ };
        struct negate{ };
        struct dereference{ };
        struct complement{ };
        struct address_of{ };
        struct logical_not{ };
        struct pre_inc{ };
        struct pre_dec{ };
        struct post_inc{ };
        struct post_dec{ };

        struct shift_left{ };
        struct shift_right{ };
        struct multiplies{ };
        struct divides{ };
        struct modulus{ };
        struct plus{ };
        struct minus{ };
        struct less{ };
        struct greater{ };
        struct less_equal{ };
        struct greater_equal{ };
        struct equal_to{ };
        struct not_equal_to{ };
        struct logical_or{ };
        struct logical_and{ };
        struct bitwise_and{ };
        struct bitwise_or{ };
        struct bitwise_xor{ };
        struct comma{ };
        struct mem_ptr{ };

        struct assign{ };
        struct shift_left_assign{ };
        struct shift_right_assign{ };
        struct multiplies_assign{ };
        struct divides_assign{ };
        struct modulus_assign{ };
        struct plus_assign{ };
        struct minus_assign{ };
        struct bitwise_and_assign{ };
        struct bitwise_or_assign{ };
        struct bitwise_xor_assign{ };
        struct subscript{ };
        struct member{ };
        struct if_else_{ };
        struct function{ };

        // Fusion tags
        struct proto_expr{ };
        struct proto_expr_iterator{ };
        struct proto_flat_view{ };
    }
  }
}

#endif
