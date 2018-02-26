//
// MIT License
//
// Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <gtest/gtest.h>

#include <iota/errors/illegal_state.hpp>
#include <iota/models/transfer.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Transfer, CtorDefault) {
  IOTA::Models::Transfer t;

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ "" });
  EXPECT_EQ(t.getValue(), 0);
  EXPECT_EQ(t.getMessage(), "");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "" });
}

TEST(Transfer, CtorShort) {
  IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "MSG");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "TAG" });

  EXPECT_EXCEPTION(
      IOTA::Models::Transfer invalidTransfer(ACCOUNT_1_ADDRESS_1_HASH, 1, "abc", "TAG"),
      IOTA::Errors::IllegalState, "message is not a valid trytes string")
}

TEST(Transfer, ConstGetters) {
  const IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "MSG");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "TAG" });
}

TEST(Transfer, AddressGetterAndSetter) {
  IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  t.setAddress(ACCOUNT_1_ADDRESS_2_HASH);

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_2_HASH });
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "MSG");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "TAG" });
}

TEST(Transfer, ValueGetterAndSetter) {
  IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  t.setValue(42);

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(t.getValue(), 42);
  EXPECT_EQ(t.getMessage(), "MSG");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "TAG" });
}

TEST(Transfer, MessageGetterAndSetter) {
  IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  t.setMessage("EDITED");

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "EDITED");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "TAG" });

  EXPECT_EXCEPTION(t.setMessage("abc"), IOTA::Errors::IllegalState,
                   "message is not a valid trytes string");
}

TEST(Transfer, TagGetterAndSetter) {
  IOTA::Models::Transfer t = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSG", "TAG" };

  t.setTag("EDITED");

  EXPECT_EQ(t.getAddress(), IOTA::Models::Address{ ACCOUNT_1_ADDRESS_1_HASH });
  EXPECT_EQ(t.getValue(), 1);
  EXPECT_EQ(t.getMessage(), "MSG");
  EXPECT_EQ(t.getTag(), IOTA::Models::Tag{ "EDITED" });
}

TEST(Transfer, IsValid) {
  IOTA::Models::Transfer t = { BUNDLE_1_TRX_1_ADDRESS, BUNDLE_1_TRX_1_VALUE, BUNDLE_1_TRX_1_TAG,
                               BUNDLE_1_TRX_1_TAG };

  EXPECT_TRUE(t.isValid());
}

TEST(Transfer, IsValidEmptyAddress) {
  IOTA::Models::Transfer t = { "", BUNDLE_1_TRX_1_VALUE, "MSG", BUNDLE_1_TRX_1_TAG };

  EXPECT_FALSE(t.isValid());
}

TEST(Transfer, EqAndDiffOperators) {
  IOTA::Models::Transfer t1 = { ACCOUNT_1_ADDRESS_1_HASH, 1, "MSGONE", "TAGONE" };
  IOTA::Models::Transfer t2 = { ACCOUNT_1_ADDRESS_2_HASH, 2, "MSGTWO", "TAGTWO" };

  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 != t2, true);

  t2.setAddress(ACCOUNT_1_ADDRESS_1_HASH);

  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 != t2, true);

  t2.setValue(1);

  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 != t2, true);

  t2.setMessage("MSGONE");

  EXPECT_EQ(t1 == t2, false);
  EXPECT_EQ(t1 != t2, true);

  t2.setTag("TAGONE");

  EXPECT_EQ(t1 == t2, true);
  EXPECT_EQ(t1 != t2, false);
}
