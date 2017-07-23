#include <getopt.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

static struct option long_opts[] = {
  {"count-ascii", 0, NULL, 'c'},
  {"skip-ascii", 0, NULL, 's'},
  {0, 0, 0, 0}
};

enum unicode_script {
  adlam = 0,
  ahom = 1,
  anatolian_hieroglyphs = 2,
  arabic = 3,
  armenian = 4,
  avestan = 5,
  balinese = 6,
  bamum = 7,
  bassa_vah = 8,
  batak = 9,
  bengali = 10,
  bhaiksuki = 11,
  bopomofo = 12,
  brahmi = 13,
  braille = 14,
  buginese = 15,
  buhid = 16,
  canadian_aboriginal = 17,
  carian = 18,
  caucasian_albanian = 19,
  chakma = 20,
  cham = 21,
  cherokee = 22,
  common = 23,
  coptic = 24,
  cuneiform = 25,
  cypriot = 26,
  cyrillic = 27,
  deseret = 28,
  devanagari = 29,
  duployan = 30,
  egyptian_hieroglyphs = 31,
  elbasan = 32,
  ethiopic = 33,
  georgian = 34,
  glagolitic = 35,
  gothic = 36,
  grantha = 37,
  greek = 38,
  gujarati = 39,
  gurmukhi = 40,
  han = 41,
  hangul = 42,
  hanunoo = 43,
  hatran = 44,
  hebrew = 45,
  hiragana = 46,
  imperial_aramaic = 47,
  inherited = 48,
  inscriptional_pahlavi = 49,
  inscriptional_parthian = 50,
  javanese = 51,
  kaithi = 52,
  kannada = 53,
  katakana = 54,
  kayah_li = 55,
  kharoshthi = 56,
  khmer = 57,
  khojki = 58,
  khudawadi = 59,
  lao = 60,
  latin = 61,
  lepcha = 62,
  limbu = 63,
  linear_a = 64,
  linear_b = 65,
  lisu = 66,
  lycian = 67,
  lydian = 68,
  mahajani = 69,
  malayalam = 70,
  mandaic = 71,
  manichaean = 72,
  marchen = 73,
  masaram_gondi = 74,
  meetei_mayek = 75,
  mende_kikakui = 76,
  meroitic_cursive = 77,
  meroitic_hieroglyphs = 78,
  miao = 79,
  modi = 80,
  mongolian = 81,
  mro = 82,
  multani = 83,
  myanmar = 84,
  nabataean = 85,
  new_tai_lue = 86,
  newa = 87,
  nko = 88,
  nushu = 89,
  ogham = 90,
  ol_chiki = 91,
  old_hungarian = 92,
  old_italic = 93,
  old_north_arabian = 94,
  old_permic = 95,
  old_persian = 96,
  old_south_arabian = 97,
  old_turkic = 98,
  oriya = 99,
  osage = 100,
  osmanya = 101,
  pahawh_hmong = 102,
  palmyrene = 103,
  pau_cin_hau = 104,
  phags_pa = 105,
  phoenician = 106,
  psalter_pahlavi = 107,
  rejang = 108,
  runic = 109,
  samaritan = 110,
  saurashtra = 111,
  sharada = 112,
  shavian = 113,
  siddham = 114,
  signwriting = 115,
  sinhala = 116,
  sora_sompeng = 117,
  soyombo = 118,
  sundanese = 119,
  syloti_nagri = 120,
  syriac = 121,
  tagalog = 122,
  tagbanwa = 123,
  tai_le = 124,
  tai_tham = 125,
  tai_viet = 126,
  takri = 127,
  tamil = 128,
  tangut = 129,
  telugu = 130,
  thaana = 131,
  thai = 132,
  tibetan = 133,
  tifinagh = 134,
  tirhuta = 135,
  ugaritic = 136,
  unknown = 137,
  vai = 138,
  warang_citi = 139,
  yi = 140,
  zanabazar_square = 141,
};

char *scripts[] = {
  "Adlam",
  "Ahom",
  "Anatolian_Hieroglyphs",
  "Arabic",
  "Armenian",
  "Avestan",
  "Balinese",
  "Bamum",
  "Bassa_Vah",
  "Batak",
  "Bengali",
  "Bhaiksuki",
  "Bopomofo",
  "Brahmi",
  "Braille",
  "Buginese",
  "Buhid",
  "Canadian_Aboriginal",
  "Carian",
  "Caucasian_Albanian",
  "Chakma",
  "Cham",
  "Cherokee",
  "Common",
  "Coptic",
  "Cuneiform",
  "Cypriot",
  "Cyrillic",
  "Deseret",
  "Devanagari",
  "Duployan",
  "Egyptian_Hieroglyphs",
  "Elbasan",
  "Ethiopic",
  "Georgian",
  "Glagolitic",
  "Gothic",
  "Grantha",
  "Greek",
  "Gujarati",
  "Gurmukhi",
  "Han",
  "Hangul",
  "Hanunoo",
  "Hatran",
  "Hebrew",
  "Hiragana",
  "Imperial_Aramaic",
  "Inherited",
  "Inscriptional_Pahlavi",
  "Inscriptional_Parthian",
  "Javanese",
  "Kaithi",
  "Kannada",
  "Katakana",
  "Kayah_Li",
  "Kharoshthi",
  "Khmer",
  "Khojki",
  "Khudawadi",
  "Lao",
  "Latin",
  "Lepcha",
  "Limbu",
  "Linear_A",
  "Linear_B",
  "Lisu",
  "Lycian",
  "Lydian",
  "Mahajani",
  "Malayalam",
  "Mandaic",
  "Manichaean",
  "Marchen",
  "Masaram_Gondi",
  "Meetei_Mayek",
  "Mende_Kikakui",
  "Meroitic_Cursive",
  "Meroitic_Hieroglyphs",
  "Miao",
  "Modi",
  "Mongolian",
  "Mro",
  "Multani",
  "Myanmar",
  "Nabataean",
  "New_Tai_Lue",
  "Newa",
  "Nko",
  "Nushu",
  "Ogham",
  "Ol_Chiki",
  "Old_Hungarian",
  "Old_Italic",
  "Old_North_Arabian",
  "Old_Permic",
  "Old_Persian",
  "Old_South_Arabian",
  "Old_Turkic",
  "Oriya",
  "Osage",
  "Osmanya",
  "Pahawh_Hmong",
  "Palmyrene",
  "Pau_Cin_Hau",
  "Phags_Pa",
  "Phoenician",
  "Psalter_Pahlavi",
  "Rejang",
  "Runic",
  "Samaritan",
  "Saurashtra",
  "Sharada",
  "Shavian",
  "Siddham",
  "SignWriting",
  "Sinhala",
  "Sora_Sompeng",
  "Soyombo",
  "Sundanese",
  "Syloti_Nagri",
  "Syriac",
  "Tagalog",
  "Tagbanwa",
  "Tai_Le",
  "Tai_Tham",
  "Tai_Viet",
  "Takri",
  "Tamil",
  "Tangut",
  "Telugu",
  "Thaana",
  "Thai",
  "Tibetan",
  "Tifinagh",
  "Tirhuta",
  "Ugaritic",
  "Unknown",
  "Vai",
  "Warang_Citi",
  "Yi",
  "Zanabazar_Square"
};

void
usage(int exit_status) {
  fprintf(stderr, "USAGE: utf8-script [--count-ascii | --skip-ascii]\n");
  exit(exit_status);
}

int
main(int argc, char **argv) {
  wchar_t ch;
  size_t counts[142];
  int flag, flag_count = 0;
  char *endptr;
  bool count_ascii = false;
  size_t ascii_cnt = 0;
  bool skip_ascii = false;

  while (true) {
    flag = getopt_long(argc, argv, "cs", long_opts, NULL);
    if (-1 == flag)
      break;
    switch(flag) {
    case 'c':
      count_ascii = true;
      flag_count += 1;
      break;
    case 's':
      skip_ascii = true;
      flag_count += 1;
      break;
    default:
      usage(1);
    }
  } 

  if ( argc - flag_count > 1)
    usage(1);

  int i;
  for (i = 0; i < 142; ++i) {
    counts[i] = 0;
  }

  setlocale(LC_ALL, "");

  while ((ch = getwchar()) != WEOF) {
    if (skip_ascii && ch >= 0 && ch < 128)
      continue;
    if (count_ascii && ch >= 0 && ch < 128) {
      ++ascii_cnt;
      continue;
    }
    if (ch < 128) {
      if (ch < 91) {
        if (ch < 65) {
          counts[common] += 1;
        } else {
          counts[latin] += 1;
        }
      } else {
        if (ch < 97) {
          counts[common] += 1;
        } else {
          if (ch < 123) {
            counts[latin] += 1;
          } else {
            counts[common] += 1;
          }
        }
      }
    } else {
      if (ch < 42183) {
        if (ch < 3757) {
          if (ch < 2766) {
            if (ch < 2143) {
              if (ch < 1417) {
                if (ch < 896) {
                  if (ch < 736) {
                    if (ch < 192) {
                      if (ch < 171) {
                        if (ch < 170) {
                          counts[common] += 1;
                        } else {
                          counts[latin] += 1;
                        }
                      } else {
                        if (ch < 186) {
                          counts[common] += 1;
                        } else {
                          if (ch < 187) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 247) {
                        if (ch < 215) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 216) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 248) {
                          counts[common] += 1;
                        } else {
                          if (ch < 697) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 884) {
                      if (ch < 748) {
                        if (ch < 741) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 746) {
                            counts[common] += 1;
                          } else {
                            counts[bopomofo] += 1;
                          }
                        }
                      } else {
                        if (ch < 768) {
                          counts[common] += 1;
                        } else {
                          if (ch < 880) {
                            counts[inherited] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 890) {
                        if (ch < 885) {
                          counts[common] += 1;
                        } else {
                          if (ch < 888) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 894) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 895) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 994) {
                    if (ch < 907) {
                      if (ch < 902) {
                        if (ch < 900) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 901) {
                            counts[greek] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 903) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 904) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 910) {
                        if (ch < 908) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 909) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 930) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 931) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1329) {
                      if (ch < 1157) {
                        if (ch < 1008) {
                          counts[coptic] += 1;
                        } else {
                          if (ch < 1024) {
                            counts[greek] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1159) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 1328) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1376) {
                        if (ch < 1367) {
                          counts[armenian] += 1;
                        } else {
                          if (ch < 1369) {
                            counts[unknown] += 1;
                          } else {
                            counts[armenian] += 1;
                          }
                        }
                      } else {
                        if (ch < 1377) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1416) {
                            counts[armenian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 1601) {
                  if (ch < 1536) {
                    if (ch < 1425) {
                      if (ch < 1419) {
                        if (ch < 1418) {
                          counts[common] += 1;
                        } else {
                          counts[armenian] += 1;
                        }
                      } else {
                        if (ch < 1421) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1424) {
                            counts[armenian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1515) {
                        if (ch < 1480) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 1488) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      } else {
                        if (ch < 1520) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 1525) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 1564) {
                      if (ch < 1548) {
                        if (ch < 1541) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1542) {
                            counts[common] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1549) {
                          counts[common] += 1;
                        } else {
                          if (ch < 1563) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1567) {
                        if (ch < 1565) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1566) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1568) {
                          counts[common] += 1;
                        } else {
                          if (ch < 1600) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 1872) {
                    if (ch < 1758) {
                      if (ch < 1648) {
                        if (ch < 1611) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1622) {
                            counts[inherited] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 1649) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 1757) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 1807) {
                        if (ch < 1792) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1806) {
                            counts[syriac] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 1867) {
                          counts[syriac] += 1;
                        } else {
                          if (ch < 1869) {
                            counts[unknown] += 1;
                          } else {
                            counts[syriac] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2094) {
                      if (ch < 1984) {
                        if (ch < 1920) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 1970) {
                            counts[thaana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2043) {
                          counts[nko] += 1;
                        } else {
                          if (ch < 2048) {
                            counts[unknown] += 1;
                          } else {
                            counts[samaritan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2112) {
                        if (ch < 2096) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2111) {
                            counts[samaritan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2140) {
                          counts[mandaic] += 1;
                        } else {
                          if (ch < 2142) {
                            counts[unknown] += 1;
                          } else {
                            counts[mandaic] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 2575) {
                if (ch < 2474) {
                  if (ch < 2385) {
                    if (ch < 2230) {
                      if (ch < 2155) {
                        if (ch < 2144) {
                          counts[unknown] += 1;
                        } else {
                          counts[syriac] += 1;
                        }
                      } else {
                        if (ch < 2208) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2229) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2274) {
                        if (ch < 2238) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 2260) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 2275) {
                          counts[common] += 1;
                        } else {
                          if (ch < 2304) {
                            counts[arabic] += 1;
                          } else {
                            counts[devanagari] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2437) {
                      if (ch < 2406) {
                        if (ch < 2387) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 2404) {
                            counts[devanagari] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 2432) {
                          counts[devanagari] += 1;
                        } else {
                          if (ch < 2436) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2449) {
                        if (ch < 2445) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2447) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2451) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2473) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2519) {
                    if (ch < 2492) {
                      if (ch < 2483) {
                        if (ch < 2481) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2482) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2486) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2490) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2505) {
                        if (ch < 2501) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2503) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2507) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2511) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2534) {
                      if (ch < 2526) {
                        if (ch < 2520) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2524) {
                            counts[unknown] += 1;
                          } else {
                            counts[bengali] += 1;
                          }
                        }
                      } else {
                        if (ch < 2527) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2532) {
                            counts[bengali] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2564) {
                        if (ch < 2558) {
                          counts[bengali] += 1;
                        } else {
                          if (ch < 2561) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      } else {
                        if (ch < 2565) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2571) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 2653) {
                  if (ch < 2618) {
                    if (ch < 2609) {
                      if (ch < 2579) {
                        if (ch < 2577) {
                          counts[gurmukhi] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2601) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2602) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2613) {
                        if (ch < 2610) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2612) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2615) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2616) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2633) {
                      if (ch < 2622) {
                        if (ch < 2620) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2621) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2627) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2631) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2641) {
                        if (ch < 2635) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2638) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2642) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2649) {
                            counts[unknown] += 1;
                          } else {
                            counts[gurmukhi] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2729) {
                    if (ch < 2692) {
                      if (ch < 2662) {
                        if (ch < 2654) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2655) {
                            counts[gurmukhi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2678) {
                          counts[gurmukhi] += 1;
                        } else {
                          if (ch < 2689) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2703) {
                        if (ch < 2693) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2702) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2706) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2707) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2746) {
                      if (ch < 2738) {
                        if (ch < 2730) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2737) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2740) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2741) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2759) {
                        if (ch < 2748) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2758) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 2762) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2763) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 3200) {
              if (ch < 2972) {
                if (ch < 2876) {
                  if (ch < 2821) {
                    if (ch < 2790) {
                      if (ch < 2769) {
                        if (ch < 2768) {
                          counts[unknown] += 1;
                        } else {
                          counts[gujarati] += 1;
                        }
                      } else {
                        if (ch < 2784) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2788) {
                            counts[gujarati] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2816) {
                        if (ch < 2802) {
                          counts[gujarati] += 1;
                        } else {
                          if (ch < 2809) {
                            counts[unknown] += 1;
                          } else {
                            counts[gujarati] += 1;
                          }
                        }
                      } else {
                        if (ch < 2817) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2820) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2858) {
                      if (ch < 2833) {
                        if (ch < 2829) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2831) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2835) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2857) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2868) {
                        if (ch < 2865) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2866) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2869) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2874) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 2918) {
                    if (ch < 2902) {
                      if (ch < 2889) {
                        if (ch < 2885) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2887) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2891) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2894) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2910) {
                        if (ch < 2904) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2908) {
                            counts[unknown] += 1;
                          } else {
                            counts[oriya] += 1;
                          }
                        }
                      } else {
                        if (ch < 2911) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2916) {
                            counts[oriya] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 2958) {
                      if (ch < 2948) {
                        if (ch < 2936) {
                          counts[oriya] += 1;
                        } else {
                          if (ch < 2946) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 2949) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2955) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2966) {
                        if (ch < 2961) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2962) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      } else {
                        if (ch < 2969) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2971) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 3076) {
                  if (ch < 3011) {
                    if (ch < 2981) {
                      if (ch < 2974) {
                        if (ch < 2973) {
                          counts[tamil] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 2976) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 2979) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 2990) {
                        if (ch < 2984) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 2987) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3002) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3006) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3025) {
                      if (ch < 3018) {
                        if (ch < 3014) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3017) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3022) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3024) {
                            counts[unknown] += 1;
                          } else {
                            counts[tamil] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3046) {
                        if (ch < 3031) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3032) {
                            counts[tamil] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3067) {
                          counts[tamil] += 1;
                        } else {
                          if (ch < 3072) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3145) {
                    if (ch < 3113) {
                      if (ch < 3086) {
                        if (ch < 3077) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3085) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3089) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3090) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3133) {
                        if (ch < 3114) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3130) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3141) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3142) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3163) {
                      if (ch < 3157) {
                        if (ch < 3146) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3150) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3159) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3160) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3174) {
                        if (ch < 3168) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3172) {
                            counts[telugu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3184) {
                          counts[telugu] += 1;
                        } else {
                          if (ch < 3192) {
                            counts[unknown] += 1;
                          } else {
                            counts[telugu] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 3479) {
                if (ch < 3300) {
                  if (ch < 3258) {
                    if (ch < 3217) {
                      if (ch < 3205) {
                        if (ch < 3204) {
                          counts[kannada] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3213) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3214) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3242) {
                        if (ch < 3218) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3241) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3252) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3253) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3278) {
                      if (ch < 3270) {
                        if (ch < 3260) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3269) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3273) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3274) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3294) {
                        if (ch < 3285) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3287) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3295) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3296) {
                            counts[unknown] += 1;
                          } else {
                            counts[kannada] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3397) {
                    if (ch < 3332) {
                      if (ch < 3313) {
                        if (ch < 3302) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3312) {
                            counts[kannada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3315) {
                          counts[kannada] += 1;
                        } else {
                          if (ch < 3328) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3342) {
                        if (ch < 3333) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3341) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3345) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3346) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3428) {
                      if (ch < 3402) {
                        if (ch < 3398) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3401) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3408) {
                          counts[malayalam] += 1;
                        } else {
                          if (ch < 3412) {
                            counts[unknown] += 1;
                          } else {
                            counts[malayalam] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3458) {
                        if (ch < 3430) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3456) {
                            counts[malayalam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3460) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3461) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 3648) {
                  if (ch < 3541) {
                    if (ch < 3518) {
                      if (ch < 3507) {
                        if (ch < 3482) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3506) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3516) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3517) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3530) {
                        if (ch < 3520) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3527) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3531) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3535) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3568) {
                      if (ch < 3544) {
                        if (ch < 3542) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3543) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3552) {
                          counts[sinhala] += 1;
                        } else {
                          if (ch < 3558) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3585) {
                        if (ch < 3570) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3573) {
                            counts[sinhala] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3643) {
                          counts[thai] += 1;
                        } else {
                          if (ch < 3647) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 3732) {
                    if (ch < 3719) {
                      if (ch < 3715) {
                        if (ch < 3676) {
                          counts[thai] += 1;
                        } else {
                          if (ch < 3713) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3716) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3717) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3723) {
                        if (ch < 3721) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3722) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3725) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3726) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3749) {
                      if (ch < 3744) {
                        if (ch < 3736) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3737) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3745) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3748) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3752) {
                        if (ch < 3750) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3751) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      } else {
                        if (ch < 3754) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3756) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (ch < 7467) {
            if (ch < 5972) {
              if (ch < 4698) {
                if (ch < 4045) {
                  if (ch < 3802) {
                    if (ch < 3781) {
                      if (ch < 3771) {
                        if (ch < 3770) {
                          counts[lao] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 3774) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3776) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3784) {
                        if (ch < 3782) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3783) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3790) {
                          counts[lao] += 1;
                        } else {
                          if (ch < 3792) {
                            counts[unknown] += 1;
                          } else {
                            counts[lao] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 3949) {
                      if (ch < 3840) {
                        if (ch < 3804) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3808) {
                            counts[lao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 3912) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 3913) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 3993) {
                        if (ch < 3953) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 3992) {
                            counts[tibetan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4029) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 4030) {
                            counts[unknown] += 1;
                          } else {
                            counts[tibetan] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 4304) {
                    if (ch < 4256) {
                      if (ch < 4057) {
                        if (ch < 4046) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4053) {
                            counts[tibetan] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 4059) {
                          counts[tibetan] += 1;
                        } else {
                          if (ch < 4096) {
                            counts[unknown] += 1;
                          } else {
                            counts[myanmar] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4296) {
                        if (ch < 4294) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 4295) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      } else {
                        if (ch < 4301) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4302) {
                            counts[georgian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4682) {
                      if (ch < 4352) {
                        if (ch < 4347) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 4348) {
                            counts[common] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      } else {
                        if (ch < 4608) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 4681) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4695) {
                        if (ch < 4686) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4688) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 4696) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4697) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 4955) {
                  if (ch < 4799) {
                    if (ch < 4750) {
                      if (ch < 4704) {
                        if (ch < 4702) {
                          counts[ethiopic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 4745) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4746) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4786) {
                        if (ch < 4752) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4785) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4790) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4792) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 4823) {
                      if (ch < 4802) {
                        if (ch < 4800) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4801) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4806) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4808) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 4882) {
                        if (ch < 4824) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4881) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 4886) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 4888) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 5792) {
                    if (ch < 5110) {
                      if (ch < 4992) {
                        if (ch < 4957) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 4989) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 5018) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 5024) {
                            counts[unknown] += 1;
                          } else {
                            counts[cherokee] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5120) {
                        if (ch < 5112) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5118) {
                            counts[cherokee] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 5760) {
                          counts[canadian_aboriginal] += 1;
                        } else {
                          if (ch < 5789) {
                            counts[ogham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 5902) {
                      if (ch < 5881) {
                        if (ch < 5867) {
                          counts[runic] += 1;
                        } else {
                          if (ch < 5870) {
                            counts[common] += 1;
                          } else {
                            counts[runic] += 1;
                          }
                        }
                      } else {
                        if (ch < 5888) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 5901) {
                            counts[tagalog] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 5941) {
                        if (ch < 5909) {
                          counts[tagalog] += 1;
                        } else {
                          if (ch < 5920) {
                            counts[unknown] += 1;
                          } else {
                            counts[hanunoo] += 1;
                          }
                        }
                      } else {
                        if (ch < 5943) {
                          counts[common] += 1;
                        } else {
                          if (ch < 5952) {
                            counts[unknown] += 1;
                          } else {
                            counts[buhid] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 6624) {
                if (ch < 6272) {
                  if (ch < 6128) {
                    if (ch < 6002) {
                      if (ch < 5997) {
                        if (ch < 5984) {
                          counts[unknown] += 1;
                        } else {
                          counts[tagbanwa] += 1;
                        }
                      } else {
                        if (ch < 5998) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6001) {
                            counts[tagbanwa] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6110) {
                        if (ch < 6004) {
                          counts[tagbanwa] += 1;
                        } else {
                          if (ch < 6016) {
                            counts[unknown] += 1;
                          } else {
                            counts[khmer] += 1;
                          }
                        }
                      } else {
                        if (ch < 6112) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6122) {
                            counts[khmer] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6150) {
                      if (ch < 6146) {
                        if (ch < 6138) {
                          counts[khmer] += 1;
                        } else {
                          if (ch < 6144) {
                            counts[unknown] += 1;
                          } else {
                            counts[mongolian] += 1;
                          }
                        }
                      } else {
                        if (ch < 6148) {
                          counts[common] += 1;
                        } else {
                          if (ch < 6149) {
                            counts[mongolian] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6170) {
                        if (ch < 6159) {
                          counts[mongolian] += 1;
                        } else {
                          if (ch < 6160) {
                            counts[unknown] += 1;
                          } else {
                            counts[mongolian] += 1;
                          }
                        }
                      } else {
                        if (ch < 6176) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6264) {
                            counts[mongolian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 6468) {
                    if (ch < 6432) {
                      if (ch < 6390) {
                        if (ch < 6315) {
                          counts[mongolian] += 1;
                        } else {
                          if (ch < 6320) {
                            counts[unknown] += 1;
                          } else {
                            counts[canadian_aboriginal] += 1;
                          }
                        }
                      } else {
                        if (ch < 6400) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6431) {
                            counts[limbu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6460) {
                        if (ch < 6444) {
                          counts[limbu] += 1;
                        } else {
                          if (ch < 6448) {
                            counts[unknown] += 1;
                          } else {
                            counts[limbu] += 1;
                          }
                        }
                      } else {
                        if (ch < 6464) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6465) {
                            counts[limbu] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6572) {
                      if (ch < 6512) {
                        if (ch < 6480) {
                          counts[limbu] += 1;
                        } else {
                          if (ch < 6510) {
                            counts[tai_le] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6517) {
                          counts[tai_le] += 1;
                        } else {
                          if (ch < 6528) {
                            counts[unknown] += 1;
                          } else {
                            counts[new_tai_lue] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6608) {
                        if (ch < 6576) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6602) {
                            counts[new_tai_lue] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6619) {
                          counts[new_tai_lue] += 1;
                        } else {
                          if (ch < 6622) {
                            counts[unknown] += 1;
                          } else {
                            counts[new_tai_lue] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 7168) {
                  if (ch < 6816) {
                    if (ch < 6752) {
                      if (ch < 6686) {
                        if (ch < 6656) {
                          counts[khmer] += 1;
                        } else {
                          if (ch < 6684) {
                            counts[buginese] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 6688) {
                          counts[buginese] += 1;
                        } else {
                          if (ch < 6751) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 6794) {
                        if (ch < 6781) {
                          counts[tai_tham] += 1;
                        } else {
                          if (ch < 6783) {
                            counts[unknown] += 1;
                          } else {
                            counts[tai_tham] += 1;
                          }
                        }
                      } else {
                        if (ch < 6800) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6810) {
                            counts[tai_tham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 6992) {
                      if (ch < 6847) {
                        if (ch < 6830) {
                          counts[tai_tham] += 1;
                        } else {
                          if (ch < 6832) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 6912) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 6988) {
                            counts[balinese] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7104) {
                        if (ch < 7037) {
                          counts[balinese] += 1;
                        } else {
                          if (ch < 7040) {
                            counts[unknown] += 1;
                          } else {
                            counts[sundanese] += 1;
                          }
                        }
                      } else {
                        if (ch < 7156) {
                          counts[batak] += 1;
                        } else {
                          if (ch < 7164) {
                            counts[unknown] += 1;
                          } else {
                            counts[batak] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 7380) {
                    if (ch < 7296) {
                      if (ch < 7242) {
                        if (ch < 7224) {
                          counts[lepcha] += 1;
                        } else {
                          if (ch < 7227) {
                            counts[unknown] += 1;
                          } else {
                            counts[lepcha] += 1;
                          }
                        }
                      } else {
                        if (ch < 7245) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7248) {
                            counts[lepcha] += 1;
                          } else {
                            counts[ol_chiki] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7368) {
                        if (ch < 7305) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 7360) {
                            counts[unknown] += 1;
                          } else {
                            counts[sundanese] += 1;
                          }
                        }
                      } else {
                        if (ch < 7376) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7379) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7412) {
                      if (ch < 7401) {
                        if (ch < 7393) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7394) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 7405) {
                          counts[common] += 1;
                        } else {
                          if (ch < 7406) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7418) {
                        if (ch < 7413) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7416) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 7424) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7462) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 11312) {
              if (ch < 8206) {
                if (ch < 8025) {
                  if (ch < 7675) {
                    if (ch < 7531) {
                      if (ch < 7517) {
                        if (ch < 7468) {
                          counts[cyrillic] += 1;
                        } else {
                          counts[latin] += 1;
                        }
                      } else {
                        if (ch < 7522) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 7526) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 7615) {
                        if (ch < 7544) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 7545) {
                            counts[cyrillic] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 7616) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 7674) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 7968) {
                      if (ch < 7958) {
                        if (ch < 7680) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 7936) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 7960) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 7966) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8014) {
                        if (ch < 8006) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8008) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8016) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8024) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 8134) {
                    if (ch < 8031) {
                      if (ch < 8028) {
                        if (ch < 8026) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8027) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8029) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8030) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8117) {
                        if (ch < 8062) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8064) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8118) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8133) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8178) {
                      if (ch < 8156) {
                        if (ch < 8148) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8150) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8157) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8176) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8191) {
                        if (ch < 8181) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 8182) {
                            counts[unknown] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      } else {
                        if (ch < 8192) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8204) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 8527) {
                  if (ch < 8352) {
                    if (ch < 8308) {
                      if (ch < 8294) {
                        if (ch < 8293) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 8305) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8306) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8335) {
                        if (ch < 8319) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8320) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 8336) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8349) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 8487) {
                      if (ch < 8433) {
                        if (ch < 8384) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8400) {
                            counts[unknown] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      } else {
                        if (ch < 8448) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 8486) {
                            counts[common] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 8498) {
                        if (ch < 8490) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8492) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 8499) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 8526) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11126) {
                    if (ch < 9280) {
                      if (ch < 8588) {
                        if (ch < 8544) {
                          counts[common] += 1;
                        } else {
                          if (ch < 8585) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 8592) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 9255) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 10240) {
                        if (ch < 9291) {
                          counts[common] += 1;
                        } else {
                          if (ch < 9312) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 10496) {
                          counts[braille] += 1;
                        } else {
                          if (ch < 11124) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11210) {
                      if (ch < 11194) {
                        if (ch < 11158) {
                          counts[common] += 1;
                        } else {
                          if (ch < 11160) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 11197) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11209) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11248) {
                        if (ch < 11219) {
                          counts[common] += 1;
                        } else {
                          if (ch < 11244) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 11264) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11311) {
                            counts[glagolitic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 12293) {
                if (ch < 11696) {
                  if (ch < 11566) {
                    if (ch < 11513) {
                      if (ch < 11360) {
                        if (ch < 11359) {
                          counts[glagolitic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 11392) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 11508) {
                            counts[coptic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11559) {
                        if (ch < 11520) {
                          counts[coptic] += 1;
                        } else {
                          if (ch < 11558) {
                            counts[georgian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 11560) {
                          counts[georgian] += 1;
                        } else {
                          if (ch < 11565) {
                            counts[unknown] += 1;
                          } else {
                            counts[georgian] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 11648) {
                      if (ch < 11631) {
                        if (ch < 11568) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11624) {
                            counts[tifinagh] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 11633) {
                          counts[tifinagh] += 1;
                        } else {
                          if (ch < 11647) {
                            counts[unknown] += 1;
                          } else {
                            counts[tifinagh] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11687) {
                        if (ch < 11671) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11680) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11688) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11695) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 11744) {
                    if (ch < 11720) {
                      if (ch < 11711) {
                        if (ch < 11703) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11704) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11712) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11719) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 11735) {
                        if (ch < 11727) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 11728) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 11736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 11743) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12020) {
                      if (ch < 11904) {
                        if (ch < 11776) {
                          counts[cyrillic] += 1;
                        } else {
                          if (ch < 11850) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 11930) {
                          counts[han] += 1;
                        } else {
                          if (ch < 11931) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12272) {
                        if (ch < 12032) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12246) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 12284) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12288) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 12687) {
                  if (ch < 12439) {
                    if (ch < 12334) {
                      if (ch < 12296) {
                        if (ch < 12294) {
                          counts[han] += 1;
                        } else {
                          if (ch < 12295) {
                            counts[common] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 12321) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12330) {
                            counts[han] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12348) {
                        if (ch < 12336) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 12344) {
                            counts[common] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 12352) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12353) {
                            counts[unknown] += 1;
                          } else {
                            counts[hiragana] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 12539) {
                      if (ch < 12445) {
                        if (ch < 12441) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12443) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 12448) {
                          counts[hiragana] += 1;
                        } else {
                          if (ch < 12449) {
                            counts[common] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12549) {
                        if (ch < 12541) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12544) {
                            counts[katakana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 12591) {
                          counts[bopomofo] += 1;
                        } else {
                          if (ch < 12593) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 13008) {
                    if (ch < 12784) {
                      if (ch < 12731) {
                        if (ch < 12688) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12704) {
                            counts[common] += 1;
                          } else {
                            counts[bopomofo] += 1;
                          }
                        }
                      } else {
                        if (ch < 12736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 12772) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 12832) {
                        if (ch < 12800) {
                          counts[katakana] += 1;
                        } else {
                          if (ch < 12831) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 12896) {
                          counts[common] += 1;
                        } else {
                          if (ch < 12927) {
                            counts[hangul] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 19904) {
                      if (ch < 13144) {
                        if (ch < 13055) {
                          counts[katakana] += 1;
                        } else {
                          if (ch < 13056) {
                            counts[unknown] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      } else {
                        if (ch < 13312) {
                          counts[common] += 1;
                        } else {
                          if (ch < 19894) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 40960) {
                        if (ch < 19968) {
                          counts[common] += 1;
                        } else {
                          if (ch < 40939) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 42125) {
                          counts[yi] += 1;
                        } else {
                          if (ch < 42128) {
                            counts[unknown] += 1;
                          } else {
                            counts[yi] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      } else {
        if (ch < 70502) {
          if (ch < 66300) {
            if (ch < 64318) {
              if (ch < 43600) {
                if (ch < 43214) {
                  if (ch < 42927) {
                    if (ch < 42656) {
                      if (ch < 42240) {
                        if (ch < 42192) {
                          counts[unknown] += 1;
                        } else {
                          counts[lisu] += 1;
                        }
                      } else {
                        if (ch < 42540) {
                          counts[vai] += 1;
                        } else {
                          if (ch < 42560) {
                            counts[unknown] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 42786) {
                        if (ch < 42744) {
                          counts[bamum] += 1;
                        } else {
                          if (ch < 42752) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 42888) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 42891) {
                            counts[common] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43056) {
                      if (ch < 42999) {
                        if (ch < 42928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 42936) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43008) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 43052) {
                            counts[syloti_nagri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43128) {
                        if (ch < 43066) {
                          counts[common] += 1;
                        } else {
                          if (ch < 43072) {
                            counts[unknown] += 1;
                          } else {
                            counts[phags_pa] += 1;
                          }
                        }
                      } else {
                        if (ch < 43136) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43206) {
                            counts[saurashtra] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 43392) {
                    if (ch < 43311) {
                      if (ch < 43262) {
                        if (ch < 43226) {
                          counts[saurashtra] += 1;
                        } else {
                          if (ch < 43232) {
                            counts[unknown] += 1;
                          } else {
                            counts[devanagari] += 1;
                          }
                        }
                      } else {
                        if (ch < 43264) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43310) {
                            counts[kayah_li] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43359) {
                        if (ch < 43312) {
                          counts[kayah_li] += 1;
                        } else {
                          if (ch < 43348) {
                            counts[rejang] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 43360) {
                          counts[rejang] += 1;
                        } else {
                          if (ch < 43389) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43488) {
                      if (ch < 43472) {
                        if (ch < 43470) {
                          counts[javanese] += 1;
                        } else {
                          if (ch < 43471) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 43482) {
                          counts[javanese] += 1;
                        } else {
                          if (ch < 43486) {
                            counts[unknown] += 1;
                          } else {
                            counts[javanese] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43575) {
                        if (ch < 43519) {
                          counts[myanmar] += 1;
                        } else {
                          if (ch < 43520) {
                            counts[unknown] += 1;
                          } else {
                            counts[cham] += 1;
                          }
                        }
                      } else {
                        if (ch < 43584) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43598) {
                            counts[cham] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 43878) {
                  if (ch < 43785) {
                    if (ch < 43715) {
                      if (ch < 43612) {
                        if (ch < 43610) {
                          counts[cham] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 43616) {
                          counts[cham] += 1;
                        } else {
                          if (ch < 43648) {
                            counts[myanmar] += 1;
                          } else {
                            counts[tai_viet] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43767) {
                        if (ch < 43739) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43744) {
                            counts[tai_viet] += 1;
                          } else {
                            counts[meetei_mayek] += 1;
                          }
                        }
                      } else {
                        if (ch < 43777) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43783) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 43816) {
                      if (ch < 43799) {
                        if (ch < 43791) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 43793) {
                            counts[unknown] += 1;
                          } else {
                            counts[ethiopic] += 1;
                          }
                        }
                      } else {
                        if (ch < 43808) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43815) {
                            counts[ethiopic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 43867) {
                        if (ch < 43823) {
                          counts[ethiopic] += 1;
                        } else {
                          if (ch < 43824) {
                            counts[unknown] += 1;
                          } else {
                            counts[latin] += 1;
                          }
                        }
                      } else {
                        if (ch < 43868) {
                          counts[common] += 1;
                        } else {
                          if (ch < 43877) {
                            counts[latin] += 1;
                          } else {
                            counts[greek] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 63744) {
                    if (ch < 44032) {
                      if (ch < 44014) {
                        if (ch < 43888) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 43968) {
                            counts[cherokee] += 1;
                          } else {
                            counts[meetei_mayek] += 1;
                          }
                        }
                      } else {
                        if (ch < 44016) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 44026) {
                            counts[meetei_mayek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 55239) {
                        if (ch < 55204) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 55216) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      } else {
                        if (ch < 55243) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 55292) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 64275) {
                      if (ch < 64218) {
                        if (ch < 64110) {
                          counts[han] += 1;
                        } else {
                          if (ch < 64112) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 64256) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64263) {
                            counts[latin] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64311) {
                        if (ch < 64280) {
                          counts[armenian] += 1;
                        } else {
                          if (ch < 64285) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      } else {
                        if (ch < 64312) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64317) {
                            counts[hebrew] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 65480) {
                if (ch < 65072) {
                  if (ch < 64832) {
                    if (ch < 64325) {
                      if (ch < 64320) {
                        if (ch < 64319) {
                          counts[hebrew] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 64322) {
                          counts[hebrew] += 1;
                        } else {
                          if (ch < 64323) {
                            counts[unknown] += 1;
                          } else {
                            counts[hebrew] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 64450) {
                        if (ch < 64326) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64336) {
                            counts[hebrew] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 64467) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64830) {
                            counts[arabic] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65022) {
                      if (ch < 64914) {
                        if (ch < 64848) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 64912) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 64968) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 65008) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65050) {
                        if (ch < 65024) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65040) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65056) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65070) {
                            counts[inherited] += 1;
                          } else {
                            counts[cyrillic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65281) {
                    if (ch < 65136) {
                      if (ch < 65127) {
                        if (ch < 65107) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65108) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65128) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65132) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65277) {
                        if (ch < 65141) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 65142) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 65279) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65280) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65392) {
                      if (ch < 65345) {
                        if (ch < 65313) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65339) {
                            counts[latin] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65371) {
                          counts[latin] += 1;
                        } else {
                          if (ch < 65382) {
                            counts[common] += 1;
                          } else {
                            counts[katakana] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65440) {
                        if (ch < 65393) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65438) {
                            counts[katakana] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65471) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 65474) {
                            counts[unknown] += 1;
                          } else {
                            counts[hangul] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 65616) {
                  if (ch < 65529) {
                    if (ch < 65498) {
                      if (ch < 65488) {
                        if (ch < 65482) {
                          counts[unknown] += 1;
                        } else {
                          counts[hangul] += 1;
                        }
                      } else {
                        if (ch < 65490) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65496) {
                            counts[hangul] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65511) {
                        if (ch < 65501) {
                          counts[hangul] += 1;
                        } else {
                          if (ch < 65504) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65512) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65519) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 65576) {
                      if (ch < 65548) {
                        if (ch < 65534) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65536) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65549) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65575) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65598) {
                        if (ch < 65595) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65596) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65599) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65614) {
                            counts[linear_b] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 65948) {
                    if (ch < 65799) {
                      if (ch < 65787) {
                        if (ch < 65630) {
                          counts[linear_b] += 1;
                        } else {
                          if (ch < 65664) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_b] += 1;
                          }
                        }
                      } else {
                        if (ch < 65792) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65795) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 65856) {
                        if (ch < 65844) {
                          counts[common] += 1;
                        } else {
                          if (ch < 65847) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 65935) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 65936) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 66176) {
                      if (ch < 66000) {
                        if (ch < 65952) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 65953) {
                            counts[greek] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66045) {
                          counts[common] += 1;
                        } else {
                          if (ch < 66046) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66257) {
                        if (ch < 66205) {
                          counts[lycian] += 1;
                        } else {
                          if (ch < 66208) {
                            counts[unknown] += 1;
                          } else {
                            counts[carian] += 1;
                          }
                        }
                      } else {
                        if (ch < 66272) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66273) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 68327) {
              if (ch < 67647) {
                if (ch < 66776) {
                  if (ch < 66464) {
                    if (ch < 66379) {
                      if (ch < 66340) {
                        if (ch < 66304) {
                          counts[unknown] += 1;
                        } else {
                          counts[old_italic] += 1;
                        }
                      } else {
                        if (ch < 66349) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66352) {
                            counts[old_italic] += 1;
                          } else {
                            counts[gothic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66432) {
                        if (ch < 66384) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66427) {
                            counts[old_permic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 66462) {
                          counts[ugaritic] += 1;
                        } else {
                          if (ch < 66463) {
                            counts[unknown] += 1;
                          } else {
                            counts[ugaritic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 66688) {
                      if (ch < 66518) {
                        if (ch < 66500) {
                          counts[old_persian] += 1;
                        } else {
                          if (ch < 66504) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_persian] += 1;
                          }
                        }
                      } else {
                        if (ch < 66560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66640) {
                            counts[deseret] += 1;
                          } else {
                            counts[shavian] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 66730) {
                        if (ch < 66718) {
                          counts[osmanya] += 1;
                        } else {
                          if (ch < 66720) {
                            counts[unknown] += 1;
                          } else {
                            counts[osmanya] += 1;
                          }
                        }
                      } else {
                        if (ch < 66736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66772) {
                            counts[osage] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 67424) {
                    if (ch < 66927) {
                      if (ch < 66856) {
                        if (ch < 66812) {
                          counts[osage] += 1;
                        } else {
                          if (ch < 66816) {
                            counts[unknown] += 1;
                          } else {
                            counts[elbasan] += 1;
                          }
                        }
                      } else {
                        if (ch < 66864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 66916) {
                            counts[caucasian_albanian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67383) {
                        if (ch < 66928) {
                          counts[caucasian_albanian] += 1;
                        } else {
                          if (ch < 67072) {
                            counts[unknown] += 1;
                          } else {
                            counts[linear_a] += 1;
                          }
                        }
                      } else {
                        if (ch < 67392) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67414) {
                            counts[linear_a] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67594) {
                      if (ch < 67590) {
                        if (ch < 67432) {
                          counts[linear_a] += 1;
                        } else {
                          if (ch < 67584) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      } else {
                        if (ch < 67592) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67593) {
                            counts[cypriot] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67641) {
                        if (ch < 67638) {
                          counts[cypriot] += 1;
                        } else {
                          if (ch < 67639) {
                            counts[unknown] += 1;
                          } else {
                            counts[cypriot] += 1;
                          }
                        }
                      } else {
                        if (ch < 67644) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67645) {
                            counts[cypriot] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 68024) {
                  if (ch < 67828) {
                    if (ch < 67712) {
                      if (ch < 67670) {
                        if (ch < 67648) {
                          counts[cypriot] += 1;
                        } else {
                          counts[imperial_aramaic] += 1;
                        }
                      } else {
                        if (ch < 67671) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67680) {
                            counts[imperial_aramaic] += 1;
                          } else {
                            counts[palmyrene] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67760) {
                        if (ch < 67743) {
                          counts[nabataean] += 1;
                        } else {
                          if (ch < 67751) {
                            counts[unknown] += 1;
                          } else {
                            counts[nabataean] += 1;
                          }
                        }
                      } else {
                        if (ch < 67808) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 67827) {
                            counts[hatran] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 67872) {
                      if (ch < 67840) {
                        if (ch < 67830) {
                          counts[hatran] += 1;
                        } else {
                          if (ch < 67835) {
                            counts[unknown] += 1;
                          } else {
                            counts[hatran] += 1;
                          }
                        }
                      } else {
                        if (ch < 67868) {
                          counts[phoenician] += 1;
                        } else {
                          if (ch < 67871) {
                            counts[unknown] += 1;
                          } else {
                            counts[phoenician] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 67904) {
                        if (ch < 67898) {
                          counts[lydian] += 1;
                        } else {
                          if (ch < 67903) {
                            counts[unknown] += 1;
                          } else {
                            counts[lydian] += 1;
                          }
                        }
                      } else {
                        if (ch < 67968) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68000) {
                            counts[meroitic_hieroglyphs] += 1;
                          } else {
                            counts[meroitic_cursive] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 68121) {
                    if (ch < 68101) {
                      if (ch < 68050) {
                        if (ch < 68028) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68048) {
                            counts[meroitic_cursive] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68096) {
                          counts[meroitic_cursive] += 1;
                        } else {
                          if (ch < 68100) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68116) {
                        if (ch < 68103) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68108) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      } else {
                        if (ch < 68117) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68120) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68176) {
                      if (ch < 68155) {
                        if (ch < 68148) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68152) {
                            counts[unknown] += 1;
                          } else {
                            counts[kharoshthi] += 1;
                          }
                        }
                      } else {
                        if (ch < 68159) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68168) {
                            counts[kharoshthi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68224) {
                        if (ch < 68185) {
                          counts[kharoshthi] += 1;
                        } else {
                          if (ch < 68192) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_south_arabian] += 1;
                          }
                        }
                      } else {
                        if (ch < 68256) {
                          counts[old_north_arabian] += 1;
                        } else {
                          if (ch < 68288) {
                            counts[unknown] += 1;
                          } else {
                            counts[manichaean] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 70096) {
                if (ch < 68851) {
                  if (ch < 68472) {
                    if (ch < 68409) {
                      if (ch < 68343) {
                        if (ch < 68331) {
                          counts[unknown] += 1;
                        } else {
                          counts[manichaean] += 1;
                        }
                      } else {
                        if (ch < 68352) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68406) {
                            counts[avestan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68440) {
                        if (ch < 68416) {
                          counts[avestan] += 1;
                        } else {
                          if (ch < 68438) {
                            counts[inscriptional_parthian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68448) {
                          counts[inscriptional_parthian] += 1;
                        } else {
                          if (ch < 68467) {
                            counts[inscriptional_pahlavi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 68528) {
                      if (ch < 68505) {
                        if (ch < 68480) {
                          counts[inscriptional_pahlavi] += 1;
                        } else {
                          if (ch < 68498) {
                            counts[psalter_pahlavi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68509) {
                          counts[psalter_pahlavi] += 1;
                        } else {
                          if (ch < 68521) {
                            counts[unknown] += 1;
                          } else {
                            counts[psalter_pahlavi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 68736) {
                        if (ch < 68608) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68681) {
                            counts[old_turkic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 68787) {
                          counts[old_hungarian] += 1;
                        } else {
                          if (ch < 68800) {
                            counts[unknown] += 1;
                          } else {
                            counts[old_hungarian] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 69840) {
                    if (ch < 69710) {
                      if (ch < 69216) {
                        if (ch < 68858) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 68864) {
                            counts[old_hungarian] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 69247) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 69632) {
                            counts[unknown] += 1;
                          } else {
                            counts[brahmi] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 69759) {
                        if (ch < 69714) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69744) {
                            counts[brahmi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 69760) {
                          counts[brahmi] += 1;
                        } else {
                          if (ch < 69826) {
                            counts[kaithi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 69942) {
                      if (ch < 69882) {
                        if (ch < 69865) {
                          counts[sora_sompeng] += 1;
                        } else {
                          if (ch < 69872) {
                            counts[unknown] += 1;
                          } else {
                            counts[sora_sompeng] += 1;
                          }
                        }
                      } else {
                        if (ch < 69888) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 69941) {
                            counts[chakma] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70007) {
                        if (ch < 69956) {
                          counts[chakma] += 1;
                        } else {
                          if (ch < 69968) {
                            counts[unknown] += 1;
                          } else {
                            counts[mahajani] += 1;
                          }
                        }
                      } else {
                        if (ch < 70016) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70094) {
                            counts[sharada] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 70405) {
                  if (ch < 70282) {
                    if (ch < 70163) {
                      if (ch < 70133) {
                        if (ch < 70112) {
                          counts[sharada] += 1;
                        } else {
                          if (ch < 70113) {
                            counts[unknown] += 1;
                          } else {
                            counts[sinhala] += 1;
                          }
                        }
                      } else {
                        if (ch < 70144) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70162) {
                            counts[khojki] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70279) {
                        if (ch < 70207) {
                          counts[khojki] += 1;
                        } else {
                          if (ch < 70272) {
                            counts[unknown] += 1;
                          } else {
                            counts[multani] += 1;
                          }
                        }
                      } else {
                        if (ch < 70280) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70281) {
                            counts[multani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70320) {
                      if (ch < 70302) {
                        if (ch < 70286) {
                          counts[multani] += 1;
                        } else {
                          if (ch < 70287) {
                            counts[unknown] += 1;
                          } else {
                            counts[multani] += 1;
                          }
                        }
                      } else {
                        if (ch < 70303) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70314) {
                            counts[multani] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70394) {
                        if (ch < 70379) {
                          counts[khudawadi] += 1;
                        } else {
                          if (ch < 70384) {
                            counts[unknown] += 1;
                          } else {
                            counts[khudawadi] += 1;
                          }
                        }
                      } else {
                        if (ch < 70400) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70404) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 70460) {
                    if (ch < 70442) {
                      if (ch < 70417) {
                        if (ch < 70413) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70415) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70419) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70441) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70452) {
                        if (ch < 70449) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70450) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70453) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70458) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 70480) {
                      if (ch < 70473) {
                        if (ch < 70469) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70471) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70475) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70478) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70488) {
                        if (ch < 70481) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70487) {
                            counts[unknown] += 1;
                          } else {
                            counts[grantha] += 1;
                          }
                        }
                      } else {
                        if (ch < 70493) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70500) {
                            counts[grantha] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        } else {
          if (ch < 120128) {
            if (ch < 92782) {
              if (ch < 72441) {
                if (ch < 71277) {
                  if (ch < 70856) {
                    if (ch < 70746) {
                      if (ch < 70512) {
                        if (ch < 70509) {
                          counts[grantha] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 70517) {
                          counts[grantha] += 1;
                        } else {
                          if (ch < 70656) {
                            counts[unknown] += 1;
                          } else {
                            counts[newa] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 70749) {
                        if (ch < 70747) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70748) {
                            counts[newa] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 70750) {
                          counts[newa] += 1;
                        } else {
                          if (ch < 70784) {
                            counts[unknown] += 1;
                          } else {
                            counts[tirhuta] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 71134) {
                      if (ch < 71040) {
                        if (ch < 70864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 70874) {
                            counts[tirhuta] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71094) {
                          counts[siddham] += 1;
                        } else {
                          if (ch < 71096) {
                            counts[unknown] += 1;
                          } else {
                            counts[siddham] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71248) {
                        if (ch < 71168) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71237) {
                            counts[modi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71258) {
                          counts[modi] += 1;
                        } else {
                          if (ch < 71264) {
                            counts[unknown] += 1;
                          } else {
                            counts[mongolian] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 71923) {
                    if (ch < 71450) {
                      if (ch < 71360) {
                        if (ch < 71296) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71352) {
                            counts[takri] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71370) {
                          counts[takri] += 1;
                        } else {
                          if (ch < 71424) {
                            counts[unknown] += 1;
                          } else {
                            counts[ahom] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 71472) {
                        if (ch < 71453) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71468) {
                            counts[ahom] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 71488) {
                          counts[ahom] += 1;
                        } else {
                          if (ch < 71840) {
                            counts[unknown] += 1;
                          } else {
                            counts[warang_citi] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 72324) {
                      if (ch < 72192) {
                        if (ch < 71935) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 71936) {
                            counts[warang_citi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 72264) {
                          counts[zanabazar_square] += 1;
                        } else {
                          if (ch < 72272) {
                            counts[unknown] += 1;
                          } else {
                            counts[soyombo] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 72350) {
                        if (ch < 72326) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72349) {
                            counts[soyombo] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 72355) {
                          counts[soyombo] += 1;
                        } else {
                          if (ch < 72384) {
                            counts[unknown] += 1;
                          } else {
                            counts[pau_cin_hau] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 73020) {
                  if (ch < 72850) {
                    if (ch < 72760) {
                      if (ch < 72713) {
                        if (ch < 72704) {
                          counts[unknown] += 1;
                        } else {
                          counts[bhaiksuki] += 1;
                        }
                      } else {
                        if (ch < 72714) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72759) {
                            counts[bhaiksuki] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 72813) {
                        if (ch < 72774) {
                          counts[bhaiksuki] += 1;
                        } else {
                          if (ch < 72784) {
                            counts[unknown] += 1;
                          } else {
                            counts[bhaiksuki] += 1;
                          }
                        }
                      } else {
                        if (ch < 72816) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72848) {
                            counts[marchen] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 72968) {
                      if (ch < 72887) {
                        if (ch < 72872) {
                          counts[marchen] += 1;
                        } else {
                          if (ch < 72873) {
                            counts[unknown] += 1;
                          } else {
                            counts[marchen] += 1;
                          }
                        }
                      } else {
                        if (ch < 72960) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 72967) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 73015) {
                        if (ch < 72970) {
                          counts[masaram_gondi] += 1;
                        } else {
                          if (ch < 72971) {
                            counts[unknown] += 1;
                          } else {
                            counts[masaram_gondi] += 1;
                          }
                        }
                      } else {
                        if (ch < 73018) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73019) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 74880) {
                    if (ch < 73728) {
                      if (ch < 73032) {
                        if (ch < 73022) {
                          counts[masaram_gondi] += 1;
                        } else {
                          if (ch < 73023) {
                            counts[unknown] += 1;
                          } else {
                            counts[masaram_gondi] += 1;
                          }
                        }
                      } else {
                        if (ch < 73040) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 73050) {
                            counts[masaram_gondi] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 74863) {
                        if (ch < 74650) {
                          counts[cuneiform] += 1;
                        } else {
                          if (ch < 74752) {
                            counts[unknown] += 1;
                          } else {
                            counts[cuneiform] += 1;
                          }
                        }
                      } else {
                        if (ch < 74864) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 74869) {
                            counts[cuneiform] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 92160) {
                      if (ch < 78895) {
                        if (ch < 75076) {
                          counts[cuneiform] += 1;
                        } else {
                          if (ch < 77824) {
                            counts[unknown] += 1;
                          } else {
                            counts[egyptian_hieroglyphs] += 1;
                          }
                        }
                      } else {
                        if (ch < 82944) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 83527) {
                            counts[anatolian_hieroglyphs] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 92767) {
                        if (ch < 92729) {
                          counts[bamum] += 1;
                        } else {
                          if (ch < 92736) {
                            counts[unknown] += 1;
                          } else {
                            counts[mro] += 1;
                          }
                        }
                      } else {
                        if (ch < 92768) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92778) {
                            counts[mro] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 119040) {
                if (ch < 94177) {
                  if (ch < 93026) {
                    if (ch < 92918) {
                      if (ch < 92880) {
                        if (ch < 92784) {
                          counts[mro] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 92910) {
                          counts[bassa_vah] += 1;
                        } else {
                          if (ch < 92912) {
                            counts[unknown] += 1;
                          } else {
                            counts[bassa_vah] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 93008) {
                        if (ch < 92928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 92998) {
                            counts[pahawh_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 93018) {
                          counts[pahawh_hmong] += 1;
                        } else {
                          if (ch < 93019) {
                            counts[unknown] += 1;
                          } else {
                            counts[pahawh_hmong] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 94021) {
                      if (ch < 93053) {
                        if (ch < 93027) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 93048) {
                            counts[pahawh_hmong] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 93072) {
                          counts[pahawh_hmong] += 1;
                        } else {
                          if (ch < 93952) {
                            counts[unknown] += 1;
                          } else {
                            counts[miao] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 94095) {
                        if (ch < 94032) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 94079) {
                            counts[miao] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 94112) {
                          counts[miao] += 1;
                        } else {
                          if (ch < 94176) {
                            counts[unknown] += 1;
                          } else {
                            counts[tangut] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 113771) {
                    if (ch < 110592) {
                      if (ch < 100333) {
                        if (ch < 94178) {
                          counts[nushu] += 1;
                        } else {
                          if (ch < 94208) {
                            counts[unknown] += 1;
                          } else {
                            counts[tangut] += 1;
                          }
                        }
                      } else {
                        if (ch < 100352) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 101107) {
                            counts[tangut] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 110960) {
                        if (ch < 110593) {
                          counts[katakana] += 1;
                        } else {
                          if (ch < 110879) {
                            counts[hiragana] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 111356) {
                          counts[nushu] += 1;
                        } else {
                          if (ch < 113664) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 113818) {
                      if (ch < 113792) {
                        if (ch < 113776) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 113789) {
                            counts[duployan] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 113801) {
                          counts[duployan] += 1;
                        } else {
                          if (ch < 113808) {
                            counts[unknown] += 1;
                          } else {
                            counts[duployan] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 113828) {
                        if (ch < 113820) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 113824) {
                            counts[duployan] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 118784) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119030) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 119970) {
                  if (ch < 119296) {
                    if (ch < 119171) {
                      if (ch < 119143) {
                        if (ch < 119079) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119081) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119146) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 119163) {
                            counts[common] += 1;
                          } else {
                            counts[inherited] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119210) {
                        if (ch < 119173) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119180) {
                            counts[inherited] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119214) {
                          counts[inherited] += 1;
                        } else {
                          if (ch < 119273) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 119808) {
                      if (ch < 119639) {
                        if (ch < 119366) {
                          counts[greek] += 1;
                        } else {
                          if (ch < 119552) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119648) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119666) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119965) {
                        if (ch < 119893) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119894) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119966) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119968) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 120005) {
                    if (ch < 119982) {
                      if (ch < 119975) {
                        if (ch < 119971) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119973) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119977) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 119981) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 119996) {
                        if (ch < 119994) {
                          counts[common] += 1;
                        } else {
                          if (ch < 119995) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 119997) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120004) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 120086) {
                      if (ch < 120075) {
                        if (ch < 120070) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120071) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 120077) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120085) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120122) {
                        if (ch < 120093) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120094) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 120123) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120127) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          } else {
            if (ch < 126602) {
              if (ch < 126505) {
                if (ch < 122915) {
                  if (ch < 120832) {
                    if (ch < 120145) {
                      if (ch < 120134) {
                        if (ch < 120133) {
                          counts[common] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 120135) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120138) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 120488) {
                        if (ch < 120146) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 120486) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 120780) {
                          counts[common] += 1;
                        } else {
                          if (ch < 120782) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 122880) {
                      if (ch < 121504) {
                        if (ch < 121484) {
                          counts[signwriting] += 1;
                        } else {
                          if (ch < 121499) {
                            counts[unknown] += 1;
                          } else {
                            counts[signwriting] += 1;
                          }
                        }
                      } else {
                        if (ch < 121505) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 121520) {
                            counts[signwriting] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 122905) {
                        if (ch < 122887) {
                          counts[glagolitic] += 1;
                        } else {
                          if (ch < 122888) {
                            counts[unknown] += 1;
                          } else {
                            counts[glagolitic] += 1;
                          }
                        }
                      } else {
                        if (ch < 122907) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 122914) {
                            counts[glagolitic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 125278) {
                    if (ch < 125127) {
                      if (ch < 122923) {
                        if (ch < 122917) {
                          counts[glagolitic] += 1;
                        } else {
                          if (ch < 122918) {
                            counts[unknown] += 1;
                          } else {
                            counts[glagolitic] += 1;
                          }
                        }
                      } else {
                        if (ch < 124928) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 125125) {
                            counts[mende_kikakui] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 125259) {
                        if (ch < 125143) {
                          counts[mende_kikakui] += 1;
                        } else {
                          if (ch < 125184) {
                            counts[unknown] += 1;
                          } else {
                            counts[adlam] += 1;
                          }
                        }
                      } else {
                        if (ch < 125264) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 125274) {
                            counts[adlam] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126497) {
                      if (ch < 126468) {
                        if (ch < 125280) {
                          counts[adlam] += 1;
                        } else {
                          if (ch < 126464) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126469) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126496) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126501) {
                        if (ch < 126499) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126500) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126503) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126504) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 126552) {
                  if (ch < 126536) {
                    if (ch < 126522) {
                      if (ch < 126516) {
                        if (ch < 126515) {
                          counts[arabic] += 1;
                        } else {
                          counts[unknown] += 1;
                        }
                      } else {
                        if (ch < 126520) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126521) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126530) {
                        if (ch < 126523) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126524) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126531) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126535) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126544) {
                      if (ch < 126539) {
                        if (ch < 126537) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126538) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126540) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126541) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126548) {
                        if (ch < 126545) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126547) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126549) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126551) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 126565) {
                    if (ch < 126558) {
                      if (ch < 126555) {
                        if (ch < 126553) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126554) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126556) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126557) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126561) {
                        if (ch < 126559) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126560) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126563) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126564) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 126584) {
                      if (ch < 126572) {
                        if (ch < 126567) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126571) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126579) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126580) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126590) {
                        if (ch < 126585) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126589) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      } else {
                        if (ch < 126591) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126592) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if (ch < 128752) {
                if (ch < 127232) {
                  if (ch < 126976) {
                    if (ch < 126629) {
                      if (ch < 126620) {
                        if (ch < 126603) {
                          counts[unknown] += 1;
                        } else {
                          counts[arabic] += 1;
                        }
                      } else {
                        if (ch < 126625) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126628) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 126652) {
                        if (ch < 126634) {
                          counts[arabic] += 1;
                        } else {
                          if (ch < 126635) {
                            counts[unknown] += 1;
                          } else {
                            counts[arabic] += 1;
                          }
                        }
                      } else {
                        if (ch < 126704) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 126706) {
                            counts[arabic] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127153) {
                      if (ch < 127124) {
                        if (ch < 127020) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127024) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127136) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127151) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127184) {
                        if (ch < 127168) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127169) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127185) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127222) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 127504) {
                    if (ch < 127344) {
                      if (ch < 127279) {
                        if (ch < 127245) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127248) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127280) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127340) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 127488) {
                        if (ch < 127405) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127462) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127489) {
                          counts[hiragana] += 1;
                        } else {
                          if (ch < 127491) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 127584) {
                      if (ch < 127561) {
                        if (ch < 127548) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127552) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 127568) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 127570) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 128725) {
                        if (ch < 127590) {
                          counts[common] += 1;
                        } else {
                          if (ch < 127744) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 128736) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 128749) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              } else {
                if (ch < 129408) {
                  if (ch < 129120) {
                    if (ch < 129024) {
                      if (ch < 128884) {
                        if (ch < 128761) {
                          counts[common] += 1;
                        } else {
                          if (ch < 128768) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 128896) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 128981) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 129096) {
                        if (ch < 129036) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129040) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129104) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129114) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 129296) {
                      if (ch < 129198) {
                        if (ch < 129160) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129168) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129280) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129292) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 129357) {
                        if (ch < 129343) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129344) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129360) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129388) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                } else {
                  if (ch < 178208) {
                    if (ch < 131072) {
                      if (ch < 129473) {
                        if (ch < 129432) {
                          counts[common] += 1;
                        } else {
                          if (ch < 129472) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 129488) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 129511) {
                            counts[common] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 177973) {
                        if (ch < 173783) {
                          counts[han] += 1;
                        } else {
                          if (ch < 173824) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 177984) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 178206) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  } else {
                    if (ch < 917505) {
                      if (ch < 191457) {
                        if (ch < 183970) {
                          counts[han] += 1;
                        } else {
                          if (ch < 183984) {
                            counts[unknown] += 1;
                          } else {
                            counts[han] += 1;
                          }
                        }
                      } else {
                        if (ch < 194560) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 195102) {
                            counts[han] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    } else {
                      if (ch < 917632) {
                        if (ch < 917506) {
                          counts[common] += 1;
                        } else {
                          if (ch < 917536) {
                            counts[unknown] += 1;
                          } else {
                            counts[common] += 1;
                          }
                        }
                      } else {
                        if (ch < 917760) {
                          counts[unknown] += 1;
                        } else {
                          if (ch < 918000) {
                            counts[inherited] += 1;
                          } else {
                            counts[unknown] += 1;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  if (count_ascii)
    printf("%lu\t%s\n", ascii_cnt, "ASCII");
  for (i = 0; i < 142; ++i) {
    if (counts[i] > 0) {
      printf("%lu\t%s\n", counts[i], scripts[i]);
    }
  }

  if (ferror(stdin)) {
    perror("error reading from standard input: ");
    return 1;
  }
  return 0;
}
