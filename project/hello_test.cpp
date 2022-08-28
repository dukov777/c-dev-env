#include <gtest/gtest.h>
#include "../project/slcan/slcan.h"

#define SLCAN_OK "\r"
#define SLCAN_ERROR "\a"

TEST(SLCAN_Basic, BoudRateS0)
{
  char line[32];
  strcpy(line, "S0\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);
}

TEST(SLCAN_Basic, BoudRateS8)
{
  char line[32];
  strcpy(line, "S8\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);
}

TEST(SLCAN_Basic, OpenClose)
{
  char line[32];
  strcpy(line, "O\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "C\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);
}

TEST(SLCAN_Basic, SetsAcceptanceCodeRegister)
{
  // Mxxxxxxxx[CR]
  // receive all frames.
  char line[32];
  strcpy(line, "M00000000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "M00000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "M0000000R\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "M000R0000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
  strcpy(line, "M\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
}

TEST(SLCAN_Basic, SetsAcceptanceMaskRegister)
{
  // mxxxxxxxx[CR]
  // receive all frames.
  char line[32];
  strcpy(line, "m00000000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "m00000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "m0000000R\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "m000R0000\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
  strcpy(line, "m\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
}

TEST(SLCAN_Basic, setup_with_btr0_btr1)
{
  // mxxxxxxxx[CR]
  // receive all frames.
  char line[32];
  strcpy(line, "s1122\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "s112\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "s112R\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "s1R22\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
  strcpy(line, "s\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
}

TEST(SLCAN_Basic, transmit_standard_can_frame)
{
  // tiiildd...[CR]
  char line[32];
  strcpy(line, "t11281122334455667788\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "t112111\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "t112411223344\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "t112811223344\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "t11211\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_ERROR, line);
}

TEST(SLCAN_Basic, transmit_extended_can_frame)
{
  // tiiildd...[CR]
  char line[32];
  strcpy(line, "T00cceedd2aabb\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "T00cceedd8aabbccddeeff0011\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "T00cceedd8aabbccddeeff0011\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_OK, line);

  strcpy(line, "T00cceedd9aabbccddeeff0011\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_ERROR, line);

  strcpy(line, "T00cceedd8aabbccddeeff001122\r");
  slcan_decode_line(line);
  EXPECT_STREQ(SLCAN_ERROR, line);
}

TEST(SLCAN_Basic, HardwareVersion)
{
  char line[32];
  strcpy(line, "V\r");
  slcan_decode_line(line);

  EXPECT_STREQ("SLCAN\r", line);
}

TEST(SLCAN_Basic, ClearBusError)
{
  char line[32];
  strcpy(line, "V\r");
  slcan_decode_line(line);

  EXPECT_STREQ("SLCAN\r", line);
}

TEST(SLCAN_Basic, NoSuchCommand)
{
  char line[32];
  strcpy(line, "Samo levsky\r");
  slcan_decode_line(line);

  EXPECT_STREQ(SLCAN_ERROR, line);
}
