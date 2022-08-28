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

TEST(SLCAN_Basic, HardwareVersion)
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
