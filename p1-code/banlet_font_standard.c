// Mon Sep 21 09:46:32 AM CDT 2020 : Updated to fix I to have .width = 5

#include "banlet.h"

glyph_t glyphs_standard[128] = {
  { .codepoint=0, .width = 6,
    .data = {
      "0XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=1, .width = 6,
    .data = {
      "1XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=2, .width = 6,
    .data = {
      "2XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=3, .width = 6,
    .data = {
      "3XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=4, .width = 6,
    .data = {
      "4XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=5, .width = 6,
    .data = {
      "5XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=6, .width = 6,
    .data = {
      "6XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=7, .width = 6,
    .data = {
      "7XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=8, .width = 6,
    .data = {
      "8XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=9, .width = 6,
    .data = {
      "9XXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=10, .width = 6,
    .data = {
      "10XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=11, .width = 6,
    .data = {
      "11XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=12, .width = 6,
    .data = {
      "12XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=13, .width = 6,
    .data = {
      "13XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=14, .width = 6,
    .data = {
      "14XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=15, .width = 6,
    .data = {
      "15XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=16, .width = 6,
    .data = {
      "16XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=17, .width = 6,
    .data = {
      "17XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=18, .width = 6,
    .data = {
      "18XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=19, .width = 6,
    .data = {
      "19XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=20, .width = 6,
    .data = {
      "20XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=21, .width = 6,
    .data = {
      "21XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=22, .width = 6,
    .data = {
      "22XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=23, .width = 6,
    .data = {
      "23XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=24, .width = 6,
    .data = {
      "24XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=25, .width = 6,
    .data = {
      "25XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=26, .width = 6,
    .data = {
      "26XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=27, .width = 6,
    .data = {
      "27XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=28, .width = 6,
    .data = {
      "28XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=29, .width = 6,
    .data = {
      "29XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=30, .width = 6,
    .data = {
      "30XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=31, .width = 6,
    .data = {
      "31XXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
  { .codepoint=32, .width = 2,
    .data = {
      "  ",
      "  ",
      "  ",
      "  ",
      "  ",
      "  ",
    }
  },
  { .codepoint=33, .width = 3,
    .data = {
      " _ ",
      "| |",
      "| |",
      "|_|",
      "(_)",
      "   ",
    }
  },
  { .codepoint=34, .width = 5,
    .data = {
      " _ _ ",
      "( | )",
      " V V ",
      "     ",
      "     ",
      "     ",
    }
  },
  { .codepoint=35, .width = 10,
    .data = {
      "   _  _   ",
      " _| || |_ ",
      "|_  ..  _|",
      "|_      _|",
      "  |_||_|  ",
      "          ",
    }
  },
  { .codepoint=36, .width = 5,
    .data = {
      "  _  ",
      " | | ",
      "/ __)",
      "\\__ \\",
      "(   /",
      " |_| ",
    }
  },
  { .codepoint=37, .width = 6,
    .data = {
      " _  __",
      "(_)/ /",
      "  / / ",
      " / /_ ",
      "/_/(_)",
      "      ",
    }
  },
  { .codepoint=38, .width = 8,
    .data = {
      "  ___   ",
      " ( _ )  ",
      " / _ \\/\\",
      "| (_>  <",
      " \\___/\\/",
      "        ",
    }
  },
  { .codepoint=39, .width = 3,
    .data = {
      " _ ",
      "( )",
      "|/ ",
      "   ",
      "   ",
      "   ",
    }
  },
  { .codepoint=40, .width = 4,
    .data = {
      "  __",
      " / /",
      "| | ",
      "| | ",
      "| | ",
      " \\_\\",
    }
  },
  { .codepoint=41, .width = 4,
    .data = {
      "__  ",
      "\\ \\ ",
      " | |",
      " | |",
      " | |",
      "/_/ ",
    }
  },
  { .codepoint=42, .width = 6,
    .data = {
      "      ",
      "__/\\__",
      "\\    /",
      "/_  _\\",
      "  \\/  ",
      "      ",
    }
  },
  { .codepoint=43, .width = 7,
    .data = {
      "       ",
      "   _   ",
      " _| |_ ",
      "|_   _|",
      "  |_|  ",
      "       ",
    }
  },
  { .codepoint=44, .width = 3,
    .data = {
      "   ",
      "   ",
      "   ",
      " _ ",
      "( )",
      "|/ ",
    }
  },
  { .codepoint=45, .width = 7,
    .data = {
      "       ",
      "       ",
      " _____ ",
      "|_____|",
      "       ",
      "       ",
    }
  },
  { .codepoint=46, .width = 3,
    .data = {
      "   ",
      "   ",
      "   ",
      " _ ",
      "(_)",
      "   ",
    }
  },
  { .codepoint=47, .width = 6,
    .data = {
      "    __",
      "   / /",
      "  / / ",
      " / /  ",
      "/_/   ",
      "      ",
    }
  },
  { .codepoint=48, .width = 7,
    .data = {
      "  ___  ",
      " / _ \\ ",
      "| | | |",
      "| |_| |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=49, .width = 3,
    .data = {
      " _ ",
      "/ |",
      "| |",
      "| |",
      "|_|",
      "   ",
    }
  },
  { .codepoint=50, .width = 7,
    .data = {
      " ____  ",
      "|___ \\ ",
      "  __) |",
      " / __/ ",
      "|_____|",
      "       ",
    }
  },
  { .codepoint=51, .width = 7,
    .data = {
      " _____ ",
      "|___ / ",
      "  |_ \\ ",
      " ___) |",
      "|____/ ",
      "       ",
    }
  },
  { .codepoint=52, .width = 8,
    .data = {
      " _  _   ",
      "| || |  ",
      "| || |_ ",
      "|__   _|",
      "   |_|  ",
      "        ",
    }
  },
  { .codepoint=53, .width = 7,
    .data = {
      " ____  ",
      "| ___| ",
      "|___ \\ ",
      " ___) |",
      "|____/ ",
      "       ",
    }
  },
  { .codepoint=54, .width = 7,
    .data = {
      "  __   ",
      " / /_  ",
      "| '_ \\ ",
      "| (_) |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=55, .width = 7,
    .data = {
      " _____ ",
      "|___  |",
      "   / / ",
      "  / /  ",
      " /_/   ",
      "       ",
    }
  },
  { .codepoint=56, .width = 7,
    .data = {
      "  ___  ",
      " ( _ ) ",
      " / _ \\ ",
      "| (_) |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=57, .width = 7,
    .data = {
      "  ___  ",
      " / _ \\ ",
      "| (_) |",
      " \\__, |",
      "   /_/ ",
      "       ",
    }
  },
  { .codepoint=58, .width = 3,
    .data = {
      "   ",
      " _ ",
      "(_)",
      " _ ",
      "(_)",
      "   ",
    }
  },
  { .codepoint=59, .width = 3,
    .data = {
      "   ",
      " _ ",
      "(_)",
      " _ ",
      "( )",
      "|/ ",
    }
  },
  { .codepoint=60, .width = 4,
    .data = {
      "  __",
      " / /",
      "/ / ",
      "\\ \\ ",
      " \\_\\",
      "    ",
    }
  },
  { .codepoint=61, .width = 7,
    .data = {
      "       ",
      " _____ ",
      "|_____|",
      "|_____|",
      "       ",
      "       ",
    }
  },
  { .codepoint=62, .width = 4,
    .data = {
      "__  ",
      "\\ \\ ",
      " \\ \\",
      " / /",
      "/_/ ",
      "    ",
    }
  },
  { .codepoint=63, .width = 5,
    .data = {
      " ___ ",
      "|__ \\",
      "  / /",
      " |_| ",
      " (_) ",
      "     ",
    }
  },
  { .codepoint=64, .width = 9,
    .data = {
      "   ____  ",
      "  / __ \\ ",
      " / / _` |",
      "| | (_| |",
      " \\ \\__,_|",
      "  \\____/ ",
    }
  },
  { .codepoint=65, .width = 9,
    .data = {
      "    _    ",
      "   / \\   ",
      "  / _ \\  ",
      " / ___ \\ ",
      "/_/   \\_\\",
      "         ",
    }
  },
  { .codepoint=66, .width = 7,
    .data = {
      " ____  ",
      "| __ ) ",
      "|  _ \\ ",
      "| |_) |",
      "|____/ ",
      "       ",
    }
  },
  { .codepoint=67, .width = 7,
    .data = {
      "  ____ ",
      " / ___|",
      "| |    ",
      "| |___ ",
      " \\____|",
      "       ",
    }
  },
  { .codepoint=68, .width = 7,
    .data = {
      " ____  ",
      "|  _ \\ ",
      "| | | |",
      "| |_| |",
      "|____/ ",
      "       ",
    }
  },
  { .codepoint=69, .width = 7,
    .data = {
      " _____ ",
      "| ____|",
      "|  _|  ",
      "| |___ ",
      "|_____|",
      "       ",
    }
  },
  { .codepoint=70, .width = 7,
    .data = {
      " _____ ",
      "|  ___|",
      "| |_   ",
      "|  _|  ",
      "|_|    ",
      "       ",
    }
  },
  { .codepoint=71, .width = 7,
    .data = {
      "  ____ ",
      " / ___|",
      "| |  _ ",
      "| |_| |",
      " \\____|",
      "       ",
    }
  },
  { .codepoint=72, .width = 7,
    .data = {
      " _   _ ",
      "| | | |",
      "| |_| |",
      "|  _  |",
      "|_| |_|",
      "       ",
    }
  },
  { .codepoint=73, .width = 5,
    .data = {
      " ___ ",
      "|_ _|",
      " | | ",
      " | | ",
      "|___|",
      "     ",
    }
  },
  { .codepoint=74, .width = 7,
    .data = {
      "     _ ",
      "    | |",
      " _  | |",
      "| |_| |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=75, .width = 6,
    .data = {
      " _  __",
      "| |/ /",
      "| ' / ",
      "| . \\ ",
      "|_|\\_\\",
      "      ",
    }
  },
  { .codepoint=76, .width = 7,
    .data = {
      " _     ",
      "| |    ",
      "| |    ",
      "| |___ ",
      "|_____|",
      "       ",
    }
  },
  { .codepoint=77, .width = 8,
    .data = {
      " __  __ ",
      "|  \\/  |",
      "| |\\/| |",
      "| |  | |",
      "|_|  |_|",
      "        ",
    }
  },
  { .codepoint=78, .width = 7,
    .data = {
      " _   _ ",
      "| \\ | |",
      "|  \\| |",
      "| |\\  |",
      "|_| \\_|",
      "       ",
    }
  },
  { .codepoint=79, .width = 7,
    .data = {
      "  ___  ",
      " / _ \\ ",
      "| | | |",
      "| |_| |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=80, .width = 7,
    .data = {
      " ____  ",
      "|  _ \\ ",
      "| |_) |",
      "|  __/ ",
      "|_|    ",
      "       ",
    }
  },
  { .codepoint=81, .width = 7,
    .data = {
      "  ___  ",
      " / _ \\ ",
      "| | | |",
      "| |_| |",
      " \\__\\_\\",
      "       ",
    }
  },
  { .codepoint=82, .width = 7,
    .data = {
      " ____  ",
      "|  _ \\ ",
      "| |_) |",
      "|  _ < ",
      "|_| \\_\\",
      "       ",
    }
  },
  { .codepoint=83, .width = 7,
    .data = {
      " ____  ",
      "/ ___| ",
      "\\___ \\ ",
      " ___) |",
      "|____/ ",
      "       ",
    }
  },
  { .codepoint=84, .width = 7,
    .data = {
      " _____ ",
      "|_   _|",
      "  | |  ",
      "  | |  ",
      "  |_|  ",
      "       ",
    }
  },
  { .codepoint=85, .width = 7,
    .data = {
      " _   _ ",
      "| | | |",
      "| | | |",
      "| |_| |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=86, .width = 9,
    .data = {
      "__     __",
      "\\ \\   / /",
      " \\ \\ / / ",
      "  \\ V /  ",
      "   \\_/   ",
      "         ",
    }
  },
  { .codepoint=87, .width = 12,
    .data = {
      "__        __",
      "\\ \\      / /",
      " \\ \\ /\\ / / ",
      "  \\ V  V /  ",
      "   \\_/\\_/   ",
      "            ",
    }
  },
  { .codepoint=88, .width = 6,
    .data = {
      "__  __",
      "\\ \\/ /",
      " \\  / ",
      " /  \\ ",
      "/_/\\_\\",
      "      ",
    }
  },
  { .codepoint=89, .width = 7,
    .data = {
      "__   __",
      "\\ \\ / /",
      " \\ V / ",
      "  | |  ",
      "  |_|  ",
      "       ",
    }
  },
  { .codepoint=90, .width = 6,
    .data = {
      " _____",
      "|__  /",
      "  / / ",
      " / /_ ",
      "/____|",
      "      ",
    }
  },
  { .codepoint=91, .width = 4,
    .data = {
      " __ ",
      "| _|",
      "| | ",
      "| | ",
      "| | ",
      "|__|",
    }
  },
  { .codepoint=92, .width = 6,
    .data = {
      "__    ",
      "\\ \\   ",
      " \\ \\  ",
      "  \\ \\ ",
      "   \\_\\",
      "      ",
    }
  },
  { .codepoint=93, .width = 4,
    .data = {
      " __ ",
      "|_ |",
      " | |",
      " | |",
      " | |",
      "|__|",
    }
  },
  { .codepoint=94, .width = 5,
    .data = {
      " /\\ ",
      "|/\\|",
      "    ",
      "    ",
      "    ",
      "    ",
    }
  },
  { .codepoint=95, .width = 7,
    .data = {
      "       ",
      "       ",
      "       ",
      "       ",
      " _____ ",
      "|_____|",
    }
  },
  { .codepoint=96, .width = 3,
    .data = {
      " _ ",
      "( )",
      " \\|",
      "   ",
      "   ",
      "   ",
    }
  },
  { .codepoint=97, .width = 7,
    .data = {
      "       ",
      "  __ _ ",
      " / _` |",
      "| (_| |",
      " \\__,_|",
      "       ",
    }
  },
  { .codepoint=98, .width = 7,
    .data = {
      " _     ",
      "| |__  ",
      "| '_ \\ ",
      "| |_) |",
      "|_.__/ ",
      "       ",
    }
  },
  { .codepoint=99, .width = 6,
    .data = {
      "      ",
      "  ___ ",
      " / __|",
      "| (__ ",
      " \\___|",
      "      ",
    }
  },
  { .codepoint=100, .width = 7,
    .data = {
      "     _ ",
      "  __| |",
      " / _` |",
      "| (_| |",
      " \\__,_|",
      "       ",
    }
  },
  { .codepoint=101, .width = 6,
    .data = {
      "      ",
      "  ___ ",
      " / _ \\",
      "|  __/",
      " \\___|",
      "      ",
    }
  },
  { .codepoint=102, .width = 5,
    .data = {
      "  __ ",
      " / _|",
      "| |_ ",
      "|  _|",
      "|_|  ",
      "     ",
    }
  },
  { .codepoint=103, .width = 7,
    .data = {
      "       ",
      "  __ _ ",
      " / _` |",
      "| (_| |",
      " \\__, |",
      " |___/ ",
    }
  },
  { .codepoint=104, .width = 7,
    .data = {
      " _     ",
      "| |__  ",
      "| '_ \\ ",
      "| | | |",
      "|_| |_|",
      "       ",
    }
  },
  { .codepoint=105, .width = 3,
    .data = {
      " _ ",
      "(_)",
      "| |",
      "| |",
      "|_|",
      "   ",
    }
  },
  { .codepoint=106, .width = 5,
    .data = {
      "   _ ",
      "  (_)",
      "  | |",
      "  | |",
      " _/ |",
      "|__/ ",
    }
  },
  { .codepoint=107, .width = 6,
    .data = {
      " _    ",
      "| | __",
      "| |/ /",
      "|   < ",
      "|_|\\_\\",
      "      ",
    }
  },
  { .codepoint=108, .width = 3,
    .data = {
      " _ ",
      "| |",
      "| |",
      "| |",
      "|_|",
      "   ",
    }
  },
  { .codepoint=109, .width = 11,
    .data = {
      "           ",
      " _ __ ___  ",
      "| '_ ` _ \\ ",
      "| | | | | |",
      "|_| |_| |_|",
      "           ",
    }
  },
  { .codepoint=110, .width = 7,
    .data = {
      "       ",
      " _ __  ",
      "| '_ \\ ",
      "| | | |",
      "|_| |_|",
      "       ",
    }
  },
  { .codepoint=111, .width = 7,
    .data = {
      "       ",
      "  ___  ",
      " / _ \\ ",
      "| (_) |",
      " \\___/ ",
      "       ",
    }
  },
  { .codepoint=112, .width = 7,
    .data = {
      "       ",
      " _ __  ",
      "| '_ \\ ",
      "| |_) |",
      "| .__/ ",
      "|_|    ",
    }
  },
  { .codepoint=113, .width = 7,
    .data = {
      "       ",
      "  __ _ ",
      " / _` |",
      "| (_| |",
      " \\__, |",
      "    |_|",
    }
  },
  { .codepoint=114, .width = 6,
    .data = {
      "      ",
      " _ __ ",
      "| '__|",
      "| |   ",
      "|_|   ",
      "      ",
    }
  },
  { .codepoint=115, .width = 5,
    .data = {
      "     ",
      " ___ ",
      "/ __|",
      "\\__ \\",
      "|___/",
      "     ",
    }
  },
  { .codepoint=116, .width = 5,
    .data = {
      " _   ",
      "| |_ ",
      "| __|",
      "| |_ ",
      " \\__|",
      "     ",
    }
  },
  { .codepoint=117, .width = 7,
    .data = {
      "       ",
      " _   _ ",
      "| | | |",
      "| |_| |",
      " \\__,_|",
      "       ",
    }
  },
  { .codepoint=118, .width = 7,
    .data = {
      "       ",
      "__   __",
      "\\ \\ / /",
      " \\ V / ",
      "  \\_/  ",
      "       ",
    }
  },
  { .codepoint=119, .width = 10,
    .data = {
      "          ",
      "__      __",
      "\\ \\ /\\ / /",
      " \\ V  V / ",
      "  \\_/\\_/  ",
      "          ",
    }
  },
  { .codepoint=120, .width = 6,
    .data = {
      "      ",
      "__  __",
      "\\ \\/ /",
      " >  < ",
      "/_/\\_\\",
      "      ",
    }
  },
  { .codepoint=121, .width = 7,
    .data = {
      "       ",
      " _   _ ",
      "| | | |",
      "| |_| |",
      " \\__, |",
      " |___/ ",
    }
  },
  { .codepoint=122, .width = 5,
    .data = {
      "     ",
      " ____",
      "|_  /",
      " / / ",
      "/___|",
      "     ",
    }
  },
  { .codepoint=123, .width = 5,
    .data = {
      "   __",
      "  / /",
      " | | ",
      "< <  ",
      " | | ",
      "  \\_\\",
    }
  },
  { .codepoint=124, .width = 3,
    .data = {
      " _ ",
      "| |",
      "| |",
      "| |",
      "| |",
      "|_|",
    }
  },
  { .codepoint=125, .width = 5,
    .data = {
      "__   ",
      "\\ \\  ",
      " | | ",
      "  > >",
      " | | ",
      "/_/  ",
    }
  },
  { .codepoint=126, .width = 5,
    .data = {
      " /\\/|",
      "|/\\/ ",
      "     ",
      "     ",
      "     ",
      "     ",
    }
  },
  { .codepoint=127, .width = 6,
    .data = {
      "127XXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
      "XXXXXX",
    }
  },
};

font_t font_standard = {
  .height = 6,
  .glyphs = glyphs_standard,
};
