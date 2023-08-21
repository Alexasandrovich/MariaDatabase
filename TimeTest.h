//
//  M A R I A D B + +
//
//          Copyright The ViaDuck Project 2016 - 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef MARIADBCLIENTPP_TIMETEST_H
#define MARIADBCLIENTPP_TIMETEST_H

#include "SkeletonTest.h"

class TimeTest : public SkeletonTest {
   protected:
    virtual void CreateTestTable() override {
        // do nothing here
    }
};

#endif  // MARIADBCLIENTPP_TIMETEST_H
