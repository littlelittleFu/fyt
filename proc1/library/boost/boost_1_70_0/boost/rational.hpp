//  Boost rational.hpp header file  ------------------------------------------//

//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

// boostinspect:nolicense (don't complain about the lack of a Boost license)
// (Paul Moore hasn't been in contact for years, so there's no way to change the
// license.)

//  See http://www.boost.org/libs/rational for documentation.

//  Credits:
//  Thanks to the boost mailing list in general for useful comments.
//  Particular contributions included:
//    Andrew D Jewell, for reminding me to take care to avoid overflow
//    Ed Brey, for many comments, including picking up on some dreadful typos
//    Stephen Silver contributed the test suite and comments on user-defined
//    IntType
//    Nickolay Mladenov, for the implementation of operator+=

//  Revision History
//  02 Sep 13  Remove unneeded forward declarations; tweak private helper
//             function (Daryle Walker)
//  30 Aug 13  Improve exception safety of "assign"; start modernizing I/O code
//             (Daryle Walker)
//  27 Aug 13  Add cross-version constructor template, plus some private helper
//             functions; add constructor to exception class to take custom
//             messages (Daryle Walker)
//  25 Aug 13  Add constexpr qualification wherever possible (Daryle Walker)
//  05 May 12  Reduced use of implicit gcd (Mario Lang)
//  05 Nov 06  Change rational_cast to not depend on division between different
//             types (Daryle Walker)
//  04 Nov 06  Off-load GCD and LCM to Boost.Integer; add some invariant checks;
//             add std::numeric_limits<> requirement to help GCD (Daryle Walker)
//  31 Oct 06  Recoded both operator< to use round-to-negative-infinity
//             divisions; the rational-value version now uses continued fraction
//             expansion to avoid overflows, for bug #798357 (Daryle Walker)
//  20 Oct 06  Fix operator bool_type for CW 8.3 (Joaqu¨ªn M L¨®pez Mu