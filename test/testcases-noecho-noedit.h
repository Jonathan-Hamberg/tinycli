/*  _______ _____ _   ___     _______ _      _____
 * |__   __|_   _| \ | \ \   / / ____| |    |_   _|
 *    | |    | | |  \| |\ \_/ / |    | |      | |
 *    | |    | | | . ` | \   /| |    | |      | |
 *    | |   _| |_| |\  |  | | | |____| |____ _| |_
 *    |_|  |_____|_| \_|  |_|  \_____|______|_____|
 *
 * Author: Bryce Kellogg (bryce@kellogg.org)
 * Copyright: 2019 Bryce Kellogg
 * License: BSD 3-Clause
 */
testcase tests[] = {
    {   .testname = "Void Function",
        .inputStr = "v\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 1, },

    {   .testname = "Void Function (Bad Arg)",
        .inputStr = "v 12\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = TINYCLI_ERROR_NUMARGS, },

    {   .testname = "Int Function",
        .inputStr = "i 13\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {13},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2, },

    {   .testname = "Int Function (Hex)",
        .inputStr = "i 0x13\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0x13},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Int Function (Negative)",
        .inputStr = "i -13\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {-13},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Int Function (Positive)",
        .inputStr = "i +13\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {13},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Int Function (Bad Arg Double)",
        .inputStr = "i 1.5\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {1}, // TODO: throw error on bad conversion
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Int Function (Bad Arg String)",
        .inputStr = "i jim\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0}, // TODO: throw error on bad conversion
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Int Function (Bad Arg Long)",
        .inputStr = "i 4294967298\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {2}, // TODO: throw error on bad conversion
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 2,  },

    {   .testname = "Double Function",
        .inputStr = "d 1.3\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {1.3},
        .expectedResult = 3,  },

    {   .testname = "Int,Int Function",
        .inputStr = "ii 12 -5\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {12, -5},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 4,  },

    {   .testname = "Int,Double Function",
        .inputStr = "id 12 -0.123\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {12},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0, -0.123},
        .expectedResult = 5,  },

    {   .testname = "Double,Int Function",
        .inputStr = "di 123.0 12\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0,12},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {123.0},
        .expectedResult = 6,  },

    {   .testname = "Double,Double Function",
        .inputStr = "dd 123.0 0.12\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {123.0, 0.12},
        .expectedResult = 7,  },

    {   .testname = "String Function",
        .inputStr = "s helloworld\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {"helloworld"},
        .expectedArgsDouble = {0},
        .expectedResult = 8,  },

    {   .testname = "No Command",
        .inputStr = "\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {0},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = TINYCLI_ERROR_NOCALL,  },

    {   .testname = "Max Args",
        .inputStr = "iiiiiiiiii 1 2 3 4 5 6 7 8 9 10\r",
        .expectedEchoStr = "",
        .expectedArgsInt = {1,2,3,4,5,6,7,8,9,10},
        .expectedArgsStr = {""},
        .expectedArgsDouble = {0},
        .expectedResult = 0,  },
};

