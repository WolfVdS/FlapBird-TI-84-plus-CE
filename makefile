# ----------------------------
# Makefile Options
# ----------------------------

NAME = FlapBird
DESCRIPTION = ""
COMPRESSED = YES
ARCHIVED = NO

COMPRESS_MODE = zx0
PREFER_OS_CRT = YES
HAS_PRINTF = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
