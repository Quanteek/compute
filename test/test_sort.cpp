//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://kylelutz.github.com/compute for more information.
//---------------------------------------------------------------------------//

#define BOOST_TEST_MODULE TestSort
#include <boost/test/unit_test.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/sort.hpp>
#include <boost/compute/algorithm/is_sorted.hpp>
#include <boost/compute/container/vector.hpp>

#include "check_macros.hpp"
#include "context_setup.hpp"

namespace bc = boost::compute;

// test trivial sorting of zero and one element vectors
BOOST_AUTO_TEST_CASE(sort_int_0_and_1)
{
    boost::compute::vector<int> vec;
    BOOST_CHECK_EQUAL(vec.size(), size_t(0));
    BOOST_CHECK(boost::compute::is_sorted(vec.begin(), vec.end()) == true);
    boost::compute::sort(vec.begin(), vec.end());

    vec.push_back(11);
    BOOST_CHECK_EQUAL(vec.size(), size_t(1));
    BOOST_CHECK(boost::compute::is_sorted(vec.begin(), vec.end()) == true);
    boost::compute::sort(vec.begin(), vec.end());
}

// test sorting of two element int vectors
BOOST_AUTO_TEST_CASE(sort_int_2)
{
    int data[] = { 4, 2 };
    boost::compute::vector<int> vec(data, data + 2);

    // check that vec is unsorted
    BOOST_CHECK(boost::compute::is_sorted(vec.begin(), vec.end()) == false);

    // sort vec
    boost::compute::sort(vec.begin(), vec.end());

    // check that vec is sorted
    BOOST_CHECK(boost::compute::is_sorted(vec.begin(), vec.end()) == true);

    // sort already sorted vec and ensure it is still sorted
    boost::compute::sort(vec.begin(), vec.end());
    BOOST_CHECK(boost::compute::is_sorted(vec.begin(), vec.end()) == true);
}

BOOST_AUTO_TEST_CASE(sort_char_vector)
{
    using boost::compute::char_;

    char_ data[] = { 'c', 'a', '0', '7', 'B', 'F', '\0', '$' };
    boost::compute::vector<char_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(char_, 8, vector, ('\0', '$', '0', '7', 'B', 'F', 'a', 'c'));
}

BOOST_AUTO_TEST_CASE(sort_uchar_vector)
{
    using boost::compute::uchar_;

    uchar_ data[] = { 0x12, 0x00, 0xFF, 0xB4, 0x80, 0x32, 0x64, 0xA2 };
    boost::compute::vector<uchar_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(uchar_, 8, vector, (0x00, 0x12, 0x32, 0x64, 0x80, 0xA2, 0xB4, 0xFF));
}

BOOST_AUTO_TEST_CASE(sort_short_vector)
{
    using boost::compute::short_;

    short_ data[] = { -4, 152, -94, 963, 31002, -456, 0, -2113 };
    boost::compute::vector<short_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(short_, 8, vector, (-2113, -456, -94, -4, 0, 152, 963, 31002));
}

BOOST_AUTO_TEST_CASE(sort_ushort_vector)
{
    using boost::compute::ushort_;

    ushort_ data[] = { 4, 152, 94, 963, 63202, 34560, 0, 2113 };
    boost::compute::vector<ushort_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(ushort_, 8, vector, (0, 4, 94, 152, 963, 2113, 34560, 63202));
}

BOOST_AUTO_TEST_CASE(sort_int_vector)
{
    int data[] = { -4, 152, -5000, 963, 75321, -456, 0, 1112 };
    boost::compute::vector<int> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(int, 8, vector, (-5000, -456, -4, 0, 152, 963, 1112, 75321));
}

BOOST_AUTO_TEST_CASE(sort_uint_vector)
{
    using boost::compute::uint_;

    uint_ data[] = { 500, 1988, 123456, 562, 0, 4000000, 9852, 102030 };
    boost::compute::vector<uint_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(uint_, 8, vector, (0, 500, 562, 1988, 9852, 102030, 123456, 4000000));
}

BOOST_AUTO_TEST_CASE(sort_long_vector)
{
    using boost::compute::long_;

    long_ data[] = { 500, 1988, 123456, 562, 0, 4000000, 9852, 102030 };
    boost::compute::vector<long_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(long_, 8, vector, (0, 500, 562, 1988, 9852, 102030, 123456, 4000000));
}

BOOST_AUTO_TEST_CASE(sort_ulong_vector)
{
    using boost::compute::ulong_;

    ulong_ data[] = { 500, 1988, 123456, 562, 0, 4000000, 9852, 102030 };
    boost::compute::vector<ulong_> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(ulong_, 8, vector, (0, 500, 562, 1988, 9852, 102030, 123456, 4000000));
}

BOOST_AUTO_TEST_CASE(sort_float_vector)
{
    float data[] = { -6023.0f, 152.5f, -63.0f, 1234567.0f, 11.2f,
                     -5000.1f, 0.0f, 14.0f, -8.25f, -0.0f };
    boost::compute::vector<float> vector(data, data + 10);
    BOOST_CHECK_EQUAL(vector.size(), size_t(10));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(
        float, 10, vector,
        (-6023.0f, -5000.1f, -63.0f, -8.25f, -0.0f, 0.0f, 11.2f, 14.0f, 152.5f, 1234567.0f)
    );
}

BOOST_AUTO_TEST_CASE(sort_double_vector)
{
    if(!device.supports_extension("cl_khr_fp64")){
        std::cout << "skipping test: device does not support double" << std::endl;
        return;
    }

    double data[] = { -6023.0, 152.5, -63.0, 1234567.0, 11.2,
                     -5000.1, 0.0, 14.0, -8.25, -0.0 };
    boost::compute::vector<double> vector(data, data + 10);
    BOOST_CHECK_EQUAL(vector.size(), size_t(10));
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == false);

    boost::compute::sort(vector.begin(), vector.end());
    BOOST_CHECK(boost::compute::is_sorted(vector.begin(), vector.end()) == true);
    CHECK_RANGE_EQUAL(
        double, 10, vector,
        (-6023.0, -5000.1, -63.0, -8.25, -0.0, 0.0, 11.2, 14.0, 152.5, 1234567.0)
    );

}

BOOST_AUTO_TEST_CASE(reverse_sort_int_vector)
{
    int data[] = { -4, 152, -5000, 963, 75321, -456, 0, 1112 };
    boost::compute::vector<int> vector(data, data + 8);
    BOOST_CHECK_EQUAL(vector.size(), size_t(8));

    boost::compute::sort(vector.begin(), vector.end(), boost::compute::greater<int>());
    CHECK_RANGE_EQUAL(int, 8, vector, (75321, 1112, 963, 152, 0, -4, -456, -5000));
}

BOOST_AUTO_TEST_CASE(sort_vectors_by_length)
{
    using boost::compute::float2_;
    using boost::compute::lambda::_1;
    using boost::compute::lambda::_2;

    float data[] = { 1.0f, 0.2f,
                     1.3f, 1.0f,
                     6.7f, 0.0f,
                     5.2f, 3.4f,
                     1.4f, 1.4f };

    // create vector on device containing vectors
    boost::compute::vector<float2_> vector(
        reinterpret_cast<float2_ *>(data),
        reinterpret_cast<float2_ *>(data) + 5,
        queue
    );

    // sort vectors by length
    boost::compute::sort(
        vector.begin(),
        vector.end(),
        length(_1) < length(_2),
        queue
    );

    // copy sorted values back to host
    boost::compute::copy(
        vector.begin(),
        vector.end(),
        reinterpret_cast<float2_ *>(data),
        queue
    );

    // check values
    BOOST_CHECK_EQUAL(data[0], 1.0f);
    BOOST_CHECK_EQUAL(data[1], 0.2f);
    BOOST_CHECK_EQUAL(data[2], 1.3f);
    BOOST_CHECK_EQUAL(data[3], 1.0f);
    BOOST_CHECK_EQUAL(data[4], 1.4f);
    BOOST_CHECK_EQUAL(data[5], 1.4f);
    BOOST_CHECK_EQUAL(data[6], 5.2f);
    BOOST_CHECK_EQUAL(data[7], 3.4f);
    BOOST_CHECK_EQUAL(data[8], 6.7f);
    BOOST_CHECK_EQUAL(data[9], 0.0f);
}

BOOST_AUTO_TEST_CASE(sort_host_vector)
{
    int data[] = { 5, 2, 3, 6, 7, 4, 0, 1 };
    std::vector<int> vector(data, data + 8);
    boost::compute::sort(vector.begin(), vector.end(), queue);
    CHECK_RANGE_EQUAL(int, 8, vector, (0, 1, 2, 3, 4, 5, 6, 7));
}

BOOST_AUTO_TEST_SUITE_END()
